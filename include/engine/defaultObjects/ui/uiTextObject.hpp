#ifndef __UI_TEXT_OBJECT_H__
#define __UI_TEXT_OBJECT_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class UITextObject : public GameObject {
    public:
        UITextObject(uint16_t UID);
        UITextObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void setText(std::string text);
        void setColor(glm::vec3 color);
        void setPosition(glm::vec2 position);
        void setFontSize(float size);

        void init();
};
#endif
