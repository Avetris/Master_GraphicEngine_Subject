#ifndef __QUAD_H__
#define __QUAD_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Quad: public GameObject{
    public:
        Quad(uint16_t UID);
        Quad(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
