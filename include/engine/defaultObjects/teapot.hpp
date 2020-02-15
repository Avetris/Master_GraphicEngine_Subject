#ifndef __TEAPOT_H__
#define __TEAPOT_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Teapot: public GameObject{
    public:
        Teapot(uint16_t UID);
        Teapot(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);
        
        void init();
};
#endif
