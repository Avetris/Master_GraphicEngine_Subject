#ifndef __COLLIDER_COMPONENT_H__
#define __COLLIDER_COMPONENT_H__

#include <glm/glm.hpp>
#include <vector>

class GameObject;

class BoxColliderComponent;
class CircleColliderComponent;

const enum class ColliderType {
    BOX,
    CIRCLE
};

class ColliderComponent {
    public:
        ColliderComponent(GameObject* gameObject, glm::vec3 position, bool zEnabled = true);

        glm::vec3 getPosition(glm::vec3 newPost = glm::vec3(0.0f)) const;

        virtual std::vector<glm::vec3> detectCollision(ColliderComponent* colliderComponent, glm::vec3 ownVel, glm::vec3 vel) = 0;

        void setPositionMove(glm::vec3 positionMove);
        void setZEnabled(bool enabled);

        bool isPassable() const;
        void setPassable(bool passable);

    protected:
        static std::vector<glm::vec3> detectBoxBoxCollision(BoxColliderComponent* boxCollider1, glm::vec3 vel1, BoxColliderComponent* boxCollider2, glm::vec3 vel2);
        static std::vector<glm::vec3> detectCircleCircleCollision(CircleColliderComponent* circleCollider1, glm::vec3 vel1, CircleColliderComponent* circleCollider2, glm::vec3 vel2);
        static std::vector<glm::vec3> detectBoxCircleCollision(BoxColliderComponent* boxCollider, glm::vec3 vel1, CircleColliderComponent* circleCollider, glm::vec3 vel2);
        static glm::vec3 getCollisionVector(bool* collision, glm::vec3 position1, glm::vec3 position2);
        static bool isZEnabled(ColliderComponent* collider1, ColliderComponent* collider2);
        bool isZEnabled() const;

    private:
        GameObject* _gameObject;
        bool _zEnabled = true;
        bool _passable = false;
        glm::vec3 _positionMove;
};
#endif
