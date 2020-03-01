#include <engine\defaultObjects\bricks\brick.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\renderComponent\quadComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\gameManager.hpp>

Brick::Brick(uint16_t UID, uint8_t hitNeccesaries) : GameObject(UID), _hitNeccesaries(hitNeccesaries) {
	init();
}

Brick::Brick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle, uint8_t hitNeccesaries) : GameObject(UID, position, rotation, scale, angle), _hitNeccesaries(hitNeccesaries) {
	init();
}

void Brick::hit()
{
	_hitNeccesaries--;
	checkHitStatus();
	if (_hitNeccesaries <= 0) {
		actionOnBreak();
		GameObjectManager::instance()->deleteGameObject(_UID);
		GameManager::instance()->hit(_scoreGiven);
	}
}

void Brick::actionOnBreak() const
{
}

void Brick::init() {
	setTag(TAG());
	_scoreGiven = _hitNeccesaries * 3;
	RenderComponent* renderComponent = addComponent<CubeComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setColor(glm::vec3(0.5f, 0.5f, 0.5f));
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
	PhysicComponent* physicComponent = addComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	physicComponent->setCollider(ColliderType::BOX);
}
