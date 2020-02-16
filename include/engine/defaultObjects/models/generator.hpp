#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Generator: public GameObject{
    public:
        Generator(uint16_t UID);
        Generator(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
