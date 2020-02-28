#ifndef __CIRCLE_COLLIDER_COMPONENT_H__
#define __CIRCLE_COLLIDER_COMPONENT_H__

#include <glm/glm.hpp>>
#include <vector>
#include <engine\gameObject.hpp>
#include "colliderComponent.hpp"

class CircleColliderComponent : public ColliderComponent {
    public:
        CircleColliderComponent(GameObject* gameObject, glm::vec3 positionMove, bool zEnabled, float radius);

        std::vector<glm::vec3> detectCollision(ColliderComponent* colliderComponent, glm::vec3 ownVel, glm::vec3 vel);

        float getRadius() const;
        void setRadius(float radius);

    private:
        float _radius;
};

#endif
