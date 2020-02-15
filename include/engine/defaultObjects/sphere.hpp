#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Sphere: public GameObject{
    public:
        Sphere(uint16_t UID);
        Sphere(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
