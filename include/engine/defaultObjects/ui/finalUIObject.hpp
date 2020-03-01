#ifndef __FINAL_UI_OBJECT_H__
#define __FINAL_UI_OBJECT_H__

#include <cstdint>
#include "uiTextObject.hpp"

class FinalUIObject : public UITextObject {
public:
    FinalUIObject(uint16_t UID);
    FinalUIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

    void showFinal(bool win);
    void hideFinal();

    void init();
};
#endif
