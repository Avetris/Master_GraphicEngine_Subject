#include <engine\defaultObjects\bricks\brick.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\renderComponent\quadComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>

Brick::Brick(uint16_t UID) : GameObject(UID) {
	init();
}

Brick::Brick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Brick::init() {
	RenderComponent* renderComponent = addComponent<CubeComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setColor(glm::vec3(0.5f, 0.5f, 0.5f));
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}
