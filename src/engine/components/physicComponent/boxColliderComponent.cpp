#include "engine/components/physicComponent/boxColliderComponent.hpp"
#include "engine/components/physicComponent/circleColliderComponent.hpp"

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject, glm::vec3 positionMove, bool zEnabled, glm::vec3 size) : ColliderComponent(gameObject, positionMove, zEnabled), _size(size) {}

std::vector<glm::vec3> BoxColliderComponent::detectCollision(ColliderComponent* colliderComponent, glm::vec3 ownVel, glm::vec3 vel)
{
	std::vector<glm::vec3> vector;
	BoxColliderComponent* boxCollider = dynamic_cast<BoxColliderComponent*>(colliderComponent);
	if (boxCollider) {
		vector = detectBoxBoxCollision(this, ownVel, boxCollider, vel);
	}
	else {
		CircleColliderComponent* circleCollider = dynamic_cast<CircleColliderComponent*>(colliderComponent);
		if (circleCollider) {
			vector = detectBoxCircleCollision(this, ownVel, circleCollider, vel);
		}
	}
	return vector;
}

glm::vec3 BoxColliderComponent::getSize() const
{
	return _size;
}

void BoxColliderComponent::setSize(glm::vec3 size)
{
	_size = size;
}
