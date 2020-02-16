#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class PointLight: public GameObject{
    public:
        PointLight(uint16_t UID);
        PointLight(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
