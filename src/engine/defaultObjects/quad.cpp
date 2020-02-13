#include <engine\defaultObjects\quad.hpp>
#include <engine\components\graphicComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\renderComponent\quadComponent.hpp>

Quad::Quad(uint16_t UID) : GameObject(UID) {
	addComponent<QuadComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}

Quad::Quad(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : GameObject(UID, position, rotation, scale) {
	addComponent<QuadComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}