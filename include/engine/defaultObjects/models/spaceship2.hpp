#ifndef __SPACESHIP2_H__
#define __SPACESHIP2_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Spaceship2 : public GameObject{
    public:
        Spaceship2(uint16_t UID);
        Spaceship2(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
