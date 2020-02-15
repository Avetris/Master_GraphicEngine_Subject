#include <engine\defaultObjects\quad.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\renderComponent\quadComponent.hpp>

Quad::Quad(uint16_t UID) : GameObject(UID) {
	init();
}

Quad::Quad(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Quad::init() {
	addComponent<QuadComponent>(ComponentType::RENDER_COMPONENT);
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}