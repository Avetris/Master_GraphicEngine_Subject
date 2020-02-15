#include <engine\defaultObjects\teapot.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\renderComponent\teapotComponent.hpp>

Teapot::Teapot(uint16_t UID) : GameObject(UID) {
	init();
}

Teapot::Teapot(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Teapot::init() {
	addComponent<TeapotComponent>(ComponentType::RENDER_COMPONENT);
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}