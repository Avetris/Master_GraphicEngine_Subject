#ifndef __UI_OBJECT_H__
#define __UI_OBJECT_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class UIObject: public GameObject {
    public:
        UIObject(uint16_t UID);
        UIObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
