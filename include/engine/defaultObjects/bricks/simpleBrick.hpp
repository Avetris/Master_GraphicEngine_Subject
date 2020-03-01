#ifndef __SIMPLE_BRICK_H__
#define __SIMPLE_BRICK_H__

#include <cstdint>
#include "brick.hpp"

class SimpleBrick: public Brick{
    public:
        SimpleBrick(uint16_t UID, uint8_t hitNeccesaries);
        SimpleBrick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle, uint8_t hitNeccesaries);

        void init();

        void checkHitStatus() override;
};
#endif
