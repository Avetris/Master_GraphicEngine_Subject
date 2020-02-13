#include <engine\defaultObjects\teapot.hpp>
#include <engine\components\graphicComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\renderComponent\teapotComponent.hpp>

Teapot::Teapot(uint16_t UID) : GameObject(UID) {
	addComponent<TeapotComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}

Teapot::Teapot(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : GameObject(UID, position, rotation, scale) {
	addComponent<TeapotComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}