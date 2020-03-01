#ifndef __BRICK_H__
#define __BRICK_H__

#include <cstdint>
#include <engine/gameObject.hpp>

class Brick: public GameObject{
    public:
        static std::string TAG() { return "BRICK"; }
        Brick(uint16_t UID, uint8_t hitNeccesaries);
        Brick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle, uint8_t hitNeccesaries);

        void hit();

        virtual void actionOnBreak() const;

        virtual void checkHitStatus() = 0;

        virtual void init();

    protected:
        uint8_t _hitNeccesaries = 1;
        uint8_t _scoreGiven = 1;
};
#endif
