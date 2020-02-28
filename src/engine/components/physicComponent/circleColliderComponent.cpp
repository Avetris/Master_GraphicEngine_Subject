#include "engine/components/physicComponent/circleColliderComponent.hpp"
#include "engine/components/physicComponent/boxColliderComponent.hpp"

CircleColliderComponent::CircleColliderComponent(GameObject* gameObject, glm::vec3 positionMove, bool zEnabled, float radius) :
	ColliderComponent(gameObject, positionMove, zEnabled), _radius(radius) {}

std::vector<glm::vec3> CircleColliderComponent::detectCollision(ColliderComponent* colliderComponent, glm::vec3 ownVel, glm::vec3 vel)
{
	std::vector<glm::vec3> vector;
	CircleColliderComponent* circleCollider = dynamic_cast<CircleColliderComponent*>(colliderComponent);
	if (circleCollider) {
		vector = detectCircleCircleCollision(this, ownVel, circleCollider, vel);
	}
	else {
		BoxColliderComponent* boxCollider = dynamic_cast<BoxColliderComponent*>(colliderComponent);
		if (boxCollider) {
			vector = detectBoxCircleCollision(boxCollider, vel, this, ownVel);
		}
	}
	return vector;
}

float CircleColliderComponent::getRadius() const
{
	return _radius;
}

void CircleColliderComponent::setRadius(float radius)
{
	_radius = radius;
}
