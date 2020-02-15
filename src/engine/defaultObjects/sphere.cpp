#include <engine\defaultObjects\sphere.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\renderComponent\sphereComponent.hpp>

Sphere::Sphere(uint16_t UID) : GameObject(UID) {
	init();
}

Sphere::Sphere(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Sphere::init() {
	addComponent<SphereComponent>(ComponentType::RENDER_COMPONENT);
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}