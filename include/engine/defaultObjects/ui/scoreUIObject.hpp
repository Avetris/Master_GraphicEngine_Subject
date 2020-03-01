#ifndef __SCORE_UI_OBJECT_H__
#define __SCORE_UI_OBJECT_H__

#include <cstdint>
#include "uiTextObject.hpp"

class ScoreUIObject : public UITextObject {
    public:
        ScoreUIObject(uint16_t UID);
        ScoreUIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void setScore(int score);

        void init();
};
#endif
