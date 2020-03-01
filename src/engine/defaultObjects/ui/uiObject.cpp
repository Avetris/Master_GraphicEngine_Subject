#include <engine\defaultObjects\quad.hpp>
#include <engine\components\renderComponent\quadComponent.hpp>
#include <engine/defaultObjects/ui/uiObject.hpp>
#include <engine\components\renderComponent\uiTextComponent.hpp>


UIObject::UIObject(uint16_t UID) : GameObject(UID) {
	init();
}

UIObject::UIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void UIObject::init() {
	UITextComponent* renderComponent = addComponent<UITextComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setText("ABC");
	renderComponent->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
	setTag("uiObject");
}