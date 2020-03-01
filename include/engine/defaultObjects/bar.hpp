#ifndef __BAR_H__
#define __BAR_H__

#include <cstdint>
#include "cube.hpp"
#include <engine\defaultObjects\ball.hpp>

class Bar : public Cube{
    public:
        static std::string TAG() { return "BAR"; };
        Bar(uint16_t UID);
        Bar(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void onUpdateInput(float dt) override;

        void setBall(Ball* ball);

        void init();

        void reset();
    private:
        Ball* _ball;
};
#endif
