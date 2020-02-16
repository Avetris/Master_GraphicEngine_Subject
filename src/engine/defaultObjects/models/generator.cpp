#include <engine\defaultObjects\models\generator.hpp>
#include <engine\components\renderComponent\modelComponent.hpp>
#include <engine\components\transformComponent.hpp>

Generator::Generator(uint16_t UID) : GameObject(UID) {
	init();
}

Generator::Generator(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Generator::init() {
	ModelComponent* modelComponent = addComponent<ModelComponent>(ComponentType::RENDER_COMPONENT);
	modelComponent->setInitialParameters("../assets/models/generator/generator.obj");
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

}
