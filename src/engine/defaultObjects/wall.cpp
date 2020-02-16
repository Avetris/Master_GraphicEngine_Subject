#include <engine\defaultObjects\wall.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>

Wall::Wall(uint16_t UID) : GameObject(UID) {
	init();
}

Wall::Wall(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Wall::init() {
	RenderComponent* renderComponent = addComponent<CubeComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setColor(glm::vec3(0.8f, 0.8f, 0.8f));
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}
