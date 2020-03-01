#include <engine/defaultObjects/ui/lifesUIObject.hpp>


LifesUIObject::LifesUIObject(uint16_t UID) : UITextObject(UID) {
	init();
}

LifesUIObject::LifesUIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : UITextObject(UID, position, rotation, scale, angle) {
	init();
}

void LifesUIObject::setLifes(int lifes)
{
	setText("LIFES " + std::to_string(lifes));
}

void LifesUIObject::init() {
	UITextObject::init();
	setTag("lifesUI");
	setPosition(glm::vec2(0.25f, 1.0f));
	setFontSize(0.04f);
	setLifes(3);
}