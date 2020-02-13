#include <engine\defaultObjects\sphere.hpp>
#include <engine\components\graphicComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\renderComponent\sphereComponent.hpp>

Sphere::Sphere(uint16_t UID) : GameObject(UID) {
	addComponent<SphereComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}

Sphere::Sphere(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : GameObject(UID, position, rotation, scale) {
	addComponent<SphereComponent>(GEOMETRY_COMPONENT);
	addComponent<GraphicComponent>(GRAPHIC_COMPONENT);
	addComponent<TransformComponent>(TRANSFORM_COMPONENT);
}