#ifndef __LIFES_UI_OBJECT_H__
#define __LIFES_UI_OBJECT_H__

#include <cstdint>
#include "uiTextObject.hpp"

class LifesUIObject : public UITextObject {
public:
    LifesUIObject(uint16_t UID);
    LifesUIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

    void setLifes(int lifes);

    void init();
};
#endif
