#ifndef __BRICK_H__
#define __BRICK_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Brick: public GameObject{
    public:
        Brick(uint16_t UID);
        Brick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void hit();

        virtual void actionOnBreak() const;

        virtual void init();

    protected:
        uint8_t _hitNeccesaries = 1;
};
#endif
