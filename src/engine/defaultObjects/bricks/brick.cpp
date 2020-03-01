#include <engine\defaultObjects\bricks\brick.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\renderComponent\quadComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>
#include <engine\managers\gameObjectManager.hpp>

Brick::Brick(uint16_t UID) : GameObject(UID) {
	init();
}

Brick::Brick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Brick::hit()
{
	_hitNeccesaries--;
	if (_hitNeccesaries <= 0) {
		actionOnBreak();
		if (GameObjectManager::instance()->getGameObjectNumberByTag(_tag) <= 1) {

		}
		GameObjectManager::instance()->deleteGameObject(_UID);
	}
}

void Brick::actionOnBreak() const
{
}

void Brick::init() {
	setTag("brick");
	RenderComponent* renderComponent = addComponent<CubeComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setColor(glm::vec3(0.5f, 0.5f, 0.5f));
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
	PhysicComponent* physicComponent = addComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	physicComponent->setCollider(ColliderType::BOX);

}
