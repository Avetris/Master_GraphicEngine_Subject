#include <engine\defaultObjects\cube.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>

Cube::Cube(uint16_t UID) : GameObject(UID) {
	init();
}

Cube::Cube(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Cube::init() {
	RenderComponent* renderComponent = addComponent<CubeComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setMaterial(MaterialManager::instance()->getMaterial("../assets/textures/bricks_albedo.png", "../assets/textures/bricks_specular.png", "", 32));
	renderComponent->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}
