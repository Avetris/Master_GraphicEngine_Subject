#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class DirectionalLight: public GameObject{
    public:
        DirectionalLight(uint16_t UID);
        DirectionalLight(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
