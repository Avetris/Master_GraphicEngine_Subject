#ifndef __BALL_H__
#define __BALL_H__

#include <cstdint>
#include "sphere.hpp"

class Ball : public Sphere{
    public:
        static std::string TAG() { return "BALL"; };
        Ball(uint16_t UID);
        Ball(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle);

        void onCollision(GameObject* collisionGameObject) override;

        bool isLaunched();
        void setLaunched(bool launched);

        void init();

        void reset();
    private:
        bool _launched = false;
};
#endif
