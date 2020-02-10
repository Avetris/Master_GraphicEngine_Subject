#include "engine/components/transformComponent.hpp"
#include <engine\gameObject.hpp>
#include <engine\handle\handleManager.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine\systems\transformSystem.hpp>
#include <engine\systems\graphicSystem.hpp>


TransformComponent::TransformComponent(uint16_t UID, Handle* gameObject) :Component(UID, gameObject) {}

void TransformComponent::init()
{
}

void TransformComponent::update(float dt)
{
}

TransformComponent::~TransformComponent()
{
	TransformSystem::instance()->removeComponent(this);
	GameObject* gameObject;
	HandleManager::instance()->GetAs(_gameObject, gameObject);
	gameObject->removeComponent(GRAPHIC_COMPONENT);
}

void TransformComponent::move(glm::vec3 direction, bool add)
{
	GameObject* object;
	HandleManager::instance()->GetAs(_gameObject, object);
	if (object != nullptr) {
		if (add) {
			object->setPosition(object->getPosition() + direction);
		}
		else {
			object->setPosition(direction);
		}
		_modelToUpdate = true;
	}
}

void TransformComponent::scale(glm::vec3 scale, bool add)
{
	GameObject* object;
	HandleManager::instance()->GetAs(_gameObject, object);
	if (object != nullptr) {
		if (add) {
			object->setScale(object->getScale() + scale);
		}
		else {
			object->setScale(scale);
		}
		_modelToUpdate = true;
	}
}

void TransformComponent::rotate(float angle, glm::vec3 axis, bool add)
{
	GameObject* object;
	HandleManager::instance()->GetAs(_gameObject, object);
	if (object != nullptr) {
		if (add) {
			// TODO --> This is incorrect!
			object->setRotation(angle + angle, object->getRotation() + axis);
		}
		else {
			object->setRotation(angle, axis);
		}
		_modelToUpdate = true;
	}
}

bool TransformComponent::modelNeedsToUpdate() const
{
	return _modelToUpdate;
}

void TransformComponent::updateModel(glm::mat4 parentModel)
{
	GameObject* object;
	HandleManager::instance()->GetAs(_gameObject, object);

	_model = glm::mat4(1.0f);
	_model = glm::translate(_model, object->getPosition());
	_model = glm::rotate(_model, object->getRotationAngle(), object->getRotation());
	_model = glm::scale(_model, object->getScale());
	_model = parentModel * _model;
	_normalMat = glm::inverse(glm::transpose(glm::mat3(_model)));

	std::vector<Handle*> children = object->getChildren();
	GameObject* child;
	for (auto it = children.begin(); it < children.end(); it++) {
		HandleManager::instance()->GetAs(*it, child);
		/*TransformComponent* com = child->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
		if (com != nullptr) {
			com->updateModel(_model);
		}*/
	}
	_modelToUpdate = false;
	GraphicSystem::instance()->positionRefresh();
}