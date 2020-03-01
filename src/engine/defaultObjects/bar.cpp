#include <engine\defaultObjects\bar.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>
#include <engine\components\physicComponent.hpp>
#include <engine\managers\gameObjectManager.hpp>

#include <iostream>

Bar::Bar(uint16_t UID) : Cube(UID) {
	init();
}

Bar::Bar(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : Cube(UID, position, rotation, scale, angle) {
	init();
}

void Bar::onUpdateInput(float dt) {
	bool launchBall = false;
	glm::vec3 direction(0.0f);
	if (InputComponent::isKeyPressed(GPU::KeyId::LEFT)) {
		direction.x -= 1.0f;
	}
	if (InputComponent::isKeyPressed(GPU::KeyId::RIGHT)) {
		direction.x += 1.0f;
	}
	if (InputComponent::isKeyPressed(GPU::KeyId::SPACE)) {
		launchBall = true;
	}
	PhysicComponent* physic = getComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	physic->setVelocity(direction, physic->getVelocity());
	if (_ball) {
 		PhysicComponent* ph = _ball->getComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
		if (launchBall && !_ball->isLaunched()) {
			ph->setVelocity(glm::vec3(1.0f, 1.0f, 0.0f), 0.2f);
			_ball->setLaunched(true);
		}
		else if(!_ball->isLaunched()) {
			ph->setVelocity(direction, physic->getVelocity());
		}
	}
}

void Bar::setBall(Ball* ball)
{
	_ball = ball;
}

void Bar::init() {
	Cube::init();
	setTag(TAG());
	PhysicComponent* physicComponent = addComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	physicComponent->setCollider(ColliderType::BOX);
	physicComponent->setRigid(true);
	physicComponent->setVelocity(glm::vec3(0.0f), 0.3f);
	addComponent<InputComponent>(ComponentType::INPUT_COMPONENT);
}

void Bar::reset()
{
	PhysicComponent* physicComponent = getComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	if (physicComponent) {
		physicComponent->setVelocity(glm::vec3(0.0f), 0.3f);
	}
	resetPosition();
	_ball->reset();
}
