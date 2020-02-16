#include <engine\defaultObjects\spotLight.hpp>
#include <engine\components\lightComponent\spotLightComponent.hpp>

SpotLight::SpotLight(uint16_t UID) : GameObject(UID) {
	init();
}

SpotLight::SpotLight(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void SpotLight::init() {
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
	SpotLightComponent* spotLightComponent = addComponent<SpotLightComponent>(ComponentType::LIGHT_COMPONENT);
	spotLightComponent->setColor(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
	SphereComponent* renderComponent = addComponent<SphereComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setShader(Engine::instance()->getSystem<RenderSystem>()->getShader(GenericShaderType::LIGHT));
	renderComponent->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}