#include <engine\defaultObjects\cube.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\graphicComponent.hpp>
#include <engine\components\transformComponent.hpp>

Cube::Cube(uint16_t UID) : GameObject(UID) {
	addComponent<CubeComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}

Cube::Cube(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : GameObject(UID, position, rotation, scale) {
	addComponent<CubeComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}
