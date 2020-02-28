#ifndef __SPACESHIP1_H__
#define __SPACESHIP1_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Spaceship1 : public GameObject{
    public:
        Spaceship1(uint16_t UID);
        Spaceship1(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
