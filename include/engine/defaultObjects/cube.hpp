#ifndef __CUBE_H__
#define __CUBE_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Cube: public GameObject{
    public:
        Cube(uint16_t UID);
        Cube(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
