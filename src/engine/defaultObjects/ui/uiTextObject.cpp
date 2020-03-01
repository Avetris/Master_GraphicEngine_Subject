#include <engine/defaultObjects/ui/uiTextObject.hpp>
#include <engine\components\renderComponent\uiTextComponent.hpp>


UITextObject::UITextObject(uint16_t UID) : GameObject(UID) {
	init();
}

UITextObject::UITextObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void UITextObject::init() {
	UITextComponent* renderComponent = addComponent<UITextComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
}

void UITextObject::setText(std::string text)
{
	UITextComponent* renderComponent = getComponent<UITextComponent>(ComponentType::RENDER_COMPONENT);
	if(renderComponent)
		renderComponent->setText(text);
}

void UITextObject::setColor(glm::vec3 color)
{
	UITextComponent* renderComponent = getComponent<UITextComponent>(ComponentType::RENDER_COMPONENT);
	if (renderComponent)
		renderComponent->setColor(color);
}

void UITextObject::setPosition(glm::vec2 position)
{
	UITextComponent* renderComponent = getComponent<UITextComponent>(ComponentType::RENDER_COMPONENT);
	if (renderComponent)
		renderComponent->setPositon(position);
}

void UITextObject::setFontSize(float size)
{
	UITextComponent* renderComponent = getComponent<UITextComponent>(ComponentType::RENDER_COMPONENT);
	if (renderComponent)
		renderComponent->setFontSize(size);
}
