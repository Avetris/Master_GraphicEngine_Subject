#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class SpotLight: public GameObject{
    public:
        SpotLight(uint16_t UID);
        SpotLight(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
