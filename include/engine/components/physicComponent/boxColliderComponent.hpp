#ifndef __BOX_COLLIDER_COMPONENT_H__
#define __BOX_COLLIDER_COMPONENT_H__

#include <glm/glm.hpp>
#include <vector>
#include "colliderComponent.hpp"

class BoxColliderComponent : public ColliderComponent {
    public:
        BoxColliderComponent(GameObject* gameObject, glm::vec3 positionMove, bool zEnabled, glm::vec3 size);

        std::vector<glm::vec3> detectCollision(ColliderComponent* colliderComponent, glm::vec3 ownVel, glm::vec3 vel);

        glm::vec3 getSize() const;
        void setSize(glm::vec3 size);

    private:        
        glm::vec3 _size;        
};

#endif
