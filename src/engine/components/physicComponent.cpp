#include "engine/components/physicComponent.hpp"
#include "engine/components/physicComponent/boxColliderComponent.hpp"
#include "engine/components/physicComponent/circleColliderComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <engine\engine.hpp>
#include <engine\gameObject.hpp>


PhysicComponent::PhysicComponent(uint16_t UID, GameObject* gameObject) :Component(UID, gameObject) {}

void PhysicComponent::init()
{
}

void PhysicComponent::update(float dt)
{
	// TODO do it with 3D
	glm::vec2 force1 = { 0, _useGravity ? _mass * -9.81 : 0 };
	glm::vec2 force2 = _forceDirection * (_mass * _force);

	glm::vec2 forceResult = force1 + force2;

	glm::vec2 acceleration = forceResult / _mass;
	
	_velocityDirection.x += acceleration.x * dt;
	_velocityDirection.y += acceleration.y * dt;
}



PhysicComponent::~PhysicComponent()
{
	_gameObject->removeComponent(ComponentType::PHYSIC_COMPONENT);
	Engine::instance()->getSystem<TransformSystem>()->removeComponent(static_cast<Component*>(this));
}

void PhysicComponent::applyVelocity() const
{
	if (getVelocityWithDirection() != glm::vec3(0.0f)) {
		TransformComponent* transformComponent = _gameObject->getComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		if (transformComponent) {
			transformComponent->move(getVelocityWithDirection(), true);
		}
	}
}

void PhysicComponent::setVelocity(glm::vec3 direction, float velocity)
{
	_velocityDirection = direction;
	_velocity = velocity;
}

float PhysicComponent::getVelocity() const
{
	return _velocity;
}

glm::vec3 PhysicComponent::getVelocityWithDirection() const
{
	return _velocityDirection * _velocity;
}

glm::vec3 PhysicComponent::getVelocityDirection() const
{
	return _velocityDirection;
}

bool PhysicComponent::isRigid() const
{
	return _rigid;
}

void PhysicComponent::setRigid(bool rigid)
{
	_rigid = rigid;
}

void PhysicComponent::addForce(glm::vec3 direction, float force)
{
	_forceDirection = direction;
	_force = force;
}

void PhysicComponent::setCollider(ColliderType colliderType, glm::vec3 positionMove, bool zEnabled)
{
	switch (colliderType) {
		case ColliderType::BOX:
			_colliderComponent = std::make_unique<BoxColliderComponent>(_gameObject, positionMove, zEnabled, _gameObject->getScale());
			break;
		case ColliderType::CIRCLE:
			_colliderComponent = std::make_unique<CircleColliderComponent>(_gameObject, positionMove, zEnabled, glm::max(_gameObject->getScale().x, _gameObject->getScale().y));
			break;
	}
}

ColliderComponent* PhysicComponent::getCollider() const
{
	return _colliderComponent != nullptr ? _colliderComponent.get() : nullptr;
}

void PhysicComponent::checkCollisions(PhysicComponent* physicComponent)
{
	ColliderComponent* otherCollider = physicComponent->getCollider();
	if (otherCollider) {
		std::vector<glm::vec3> normals = _colliderComponent->detectCollision(otherCollider, getVelocityWithDirection(), physicComponent->getVelocityWithDirection());
		if (normals.size() > 0) {
			calculateReflecVelocity(normals.at(0));
			physicComponent->calculateReflecVelocity(normals.at(0));
			physicComponent->_gameObject->onCollision(_gameObject);
			if(_gameObject && physicComponent->_gameObject)
				_gameObject->onCollision(physicComponent->_gameObject);
		}
	}
}

void PhysicComponent::calculateReflecVelocity(glm::vec3 normal)
{
	if (!_rigid) {
		_velocityDirection = (_colliderComponent->isPassable() ? 0.0f : 1.0f) * (-2.0f * glm::dot(_velocityDirection, normal) * normal + _velocityDirection);
		_velocityDirection = glm::normalize(_velocityDirection);
	}
	else if (normal == glm::vec3(0.0f)) {

		_velocityDirection = glm::vec3(0.0f);
	}
}
