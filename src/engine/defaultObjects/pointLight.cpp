#include <engine\defaultObjects\pointLight.hpp>
#include <engine\components\lightComponent\pointLightComponent.hpp>

PointLight::PointLight(uint16_t UID) : GameObject(UID) {
	init();
}

PointLight::PointLight(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void PointLight::init() {
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

	PointLightComponent* pointLightComponent = addComponent<PointLightComponent>(ComponentType::LIGHT_COMPONENT);
	pointLightComponent->setColor(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

	SphereComponent* renderComponent = addComponent<SphereComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setShader(Engine::instance()->getSystem<RenderSystem>()->getShader(GenericShaderType::LIGHT));
	renderComponent->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}
