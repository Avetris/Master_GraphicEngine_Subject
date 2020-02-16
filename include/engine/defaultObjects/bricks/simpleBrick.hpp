#ifndef __SIMPLE_BRICK_H__
#define __SIMPLE_BRICK_H__

#include <cstdint>
#include "brick.hpp"

class SimpleBrick: public Brick{
    public:
        SimpleBrick(uint16_t UID);
        SimpleBrick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void init();
};
#endif
