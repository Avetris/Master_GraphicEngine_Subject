#include <engine/defaultObjects/ui/scoreUIObject.hpp>


ScoreUIObject::ScoreUIObject(uint16_t UID) : UITextObject(UID) {
	init();
}

ScoreUIObject::ScoreUIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : UITextObject(UID, position, rotation, scale, angle) {
	init();
}

void ScoreUIObject::setScore(int score)
{
	setText("SCORE " + std::to_string(score) );
}

void ScoreUIObject::init() {
	UITextObject::init();
	setTag("scoreUI");
	setPosition(glm::vec2(-0.75, 1.0f));
	setFontSize(0.04f);
	setScore(0);
}