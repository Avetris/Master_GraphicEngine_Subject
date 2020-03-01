#ifndef __WALL_H__
#define __WALL_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Wall : public GameObject{
    public:
        static std::string TAG() { return "WALL"; };
        Wall(uint16_t UID);
        Wall(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
