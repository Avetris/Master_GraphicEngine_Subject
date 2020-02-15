#include <engine\defaultObjects\cube.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>

Cube::Cube(uint16_t UID) : GameObject(UID) {
	init();
}

Cube::Cube(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Cube::init() {
	addComponent<CubeComponent>(ComponentType::RENDER_COMPONENT);
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}
