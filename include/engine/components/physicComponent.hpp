#ifndef __PHYSIC_COMPONENT_H__
#define __PHYSIC_COMPONENT_H__

#include "component.hpp"
#include <glm/glm.hpp>
#include <memory>
#include "physicComponent\colliderComponent.hpp"

class PhysicComponent : public Component {
    public:
        PhysicComponent(uint16_t UID, GameObject* gameObject);
        void init();
        void update(float dt);
        ~PhysicComponent();

        void applyVelocity() const;

        void setVelocity(glm::vec3 direction, float velocity);
        float getVelocity() const;
        glm::vec3 getVelocityWithDirection() const;
        glm::vec3 getVelocityDirection() const;

        bool isRigid() const;
        void setRigid(bool rigid);

        void addForce(glm::vec3 direction, float force);

        void setCollider(ColliderType colliderType, glm::vec3 positionMove = glm::vec3(0.0f), bool zEnabled = true);
        ColliderComponent* getCollider() const;
        void checkCollisions(PhysicComponent* physicComponent);
        void calculateReflecVelocity(glm::vec3 normal);

    private:
        std::unique_ptr<ColliderComponent> _colliderComponent = nullptr;
        bool _rigid = true;
        bool _useGravity = false;
        float _mass = 1.0f;
        glm::vec3 _forceDirection = glm::vec3(0.0f);
        float _force = 0.0f;
        glm::vec3 _velocityDirection = glm::vec3(0.0f);
        float _velocity = 0.0f;
};

#endif
