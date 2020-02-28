#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Player : public GameObject{
    public:
        Player(uint16_t UID);
        Player(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
