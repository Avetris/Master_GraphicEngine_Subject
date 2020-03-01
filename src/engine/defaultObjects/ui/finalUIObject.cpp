#include <engine/defaultObjects/ui/finalUIObject.hpp>


FinalUIObject::FinalUIObject(uint16_t UID) : UITextObject(UID) {
	init();
}

FinalUIObject::FinalUIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : UITextObject(UID, position, rotation, scale, angle) {
	init();
}

void FinalUIObject::showFinal(bool win)
{
	if (win) {
		setText("YOU HAVE PASS THE LEVEL. CLICK ON 'R' TO PLAY AGAIN");
	}
	else {
		setText("YOU HAVE LOST THE LEVEL. CLICK ON 'R' TO PLAY AGAIN");
	}
	enableComponent(ComponentType::RENDER_COMPONENT, true);
}

void FinalUIObject::hideFinal()
{
	enableComponent(ComponentType::RENDER_COMPONENT, false);
}

void FinalUIObject::init() {
	UITextObject::init();
	setTag("finalUI");
	setPosition(glm::vec2(-0.5, 0.5));
	hideFinal();
}