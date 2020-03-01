#include <engine\defaultObjects\directionalLight.hpp>
#include <engine\components\lightComponent\directionalLightComponent.hpp>

DirectionalLight::DirectionalLight(uint16_t UID) : GameObject(UID) {
	init();
}

DirectionalLight::DirectionalLight(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void DirectionalLight::init() {
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
	DirectionalLightComponent* directionalLightComponent = addComponent<DirectionalLightComponent>(ComponentType::LIGHT_COMPONENT);
	directionalLightComponent->setColor(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
	directionalLightComponent->setDirection(glm::vec3(0.1f, 0.1f, 0.1f));
}