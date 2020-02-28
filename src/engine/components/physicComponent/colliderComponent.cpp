#include "engine/components/physicComponent/colliderComponent.hpp"
#include "engine/components/physicComponent/boxColliderComponent.hpp"
#include "engine/components/physicComponent/circleColliderComponent.hpp"
#include "engine/gameObject.hpp"

ColliderComponent::ColliderComponent(GameObject* gameObject, glm::vec3 positionMove, bool zEnabled) : _gameObject(gameObject), _positionMove(positionMove), _zEnabled(zEnabled){}

glm::vec3 ColliderComponent::getPosition(glm::vec3 newPost) const
{
	if (_gameObject) {
		return _gameObject->getPosition() + _positionMove + newPost;
	}
	return _positionMove + newPost;
}

glm::vec3 ColliderComponent::getCollisionVector(bool* collision, glm::vec3 position1, glm::vec3 position2)
{
	glm::vec3 collisionVector(0.0f);
	float numberOfFaces = 0.0f;
	if (collision[1]) {
		collisionVector.x = position1.x > position2.x ? -1 : 1;
		numberOfFaces++;
	}
	if (collision[2]) {
		collisionVector.y = position1.y > position2.y ? -1 : 1;
		numberOfFaces++;
	}
	if (collision[3]) {
		collisionVector.z = position1.z > position2.z ? -1 : 1;
		numberOfFaces++;
	}

	return collisionVector;// / (numberOfFaces > 0 ? numberOfFaces : 1);
}

std::vector<glm::vec3> ColliderComponent::detectBoxBoxCollision(BoxColliderComponent* boxCollider1, glm::vec3 vel1, BoxColliderComponent* boxCollider2, glm::vec3 vel2)
{
	std::vector<glm::vec3> vector;
	bool collision[4] = { false };
	glm::vec3 disVec = abs(boxCollider2->getPosition(vel2) - boxCollider1->getPosition(vel1));
	glm::vec3 disVec2 = abs(boxCollider2->getPosition() - boxCollider1->getPosition());
	glm::vec3 sizeVec = abs((boxCollider1->getSize() / 2.0f) + (boxCollider2->getSize() / 2.0f));
	if (!isZEnabled(boxCollider1, boxCollider2)) {
		sizeVec.z = 0;
		disVec.z = 0;
	}
	// TODO detect normals
	collision[0] = sizeVec.x >= disVec.x && sizeVec.y >= disVec.y && sizeVec.z >= disVec.z;
	if (collision[0]) {
		if (boxCollider1->_gameObject->isTag("bar") || boxCollider2->_gameObject->isTag("bar")) {
			bool t = false;
		}
		vector.push_back(ColliderComponent::getCollisionVector(collision, boxCollider1->getPosition(), boxCollider2->getPosition()));
	}
	return vector;
}

std::vector<glm::vec3> ColliderComponent::detectCircleCircleCollision(CircleColliderComponent* circleCollider1, glm::vec3 vel1, CircleColliderComponent* circleCollider2, glm::vec3 vel2)
{
	std::vector<glm::vec3> vector;
	bool collision[4] = { false };
	float r = circleCollider1->getRadius() + circleCollider2->getRadius();
	r *= r;
	glm::vec3 pos = circleCollider1->getPosition(vel1) + circleCollider2->getPosition(vel2);
	if (!isZEnabled(circleCollider1, circleCollider2)) {
		pos.z = 0;
	}
	// TODO detect normals
	collision[0] = r < (pos.x * pos.x) + (pos.x * pos.x) + (pos.z * pos.z);
	if (collision[0]) {
		vector.push_back(ColliderComponent::getCollisionVector(collision, circleCollider1->getPosition(), circleCollider2->getPosition()));
	}
	return vector;
}

std::vector<glm::vec3> ColliderComponent::detectBoxCircleCollision(BoxColliderComponent* boxCollider, glm::vec3 vel1, CircleColliderComponent* circleCollider, glm::vec3 vel2)
{
	std::vector<glm::vec3> vector;
	bool collision[4] = { false };
	bool zEnabled = ColliderComponent::isZEnabled(boxCollider, circleCollider);

	glm::vec3 circlePosition = circleCollider->getPosition(vel2);
	glm::vec3 boxPositon = boxCollider->getPosition(vel1);
	glm::vec3 boxSize = boxCollider->getSize() / 2.0f;

	// Find the closest point to the circle within the rectangle
	glm::vec3 closest(0.0f);
	closest.x = glm::clamp(circlePosition.x, boxPositon.x - boxSize.x, boxPositon.x + boxSize.x);
	closest.y = glm::clamp(circlePosition.y, boxPositon.y - boxSize.y, boxPositon.y + boxSize.y);
	if(zEnabled)
		closest.z = glm::clamp(circlePosition.z, boxPositon.z - boxSize.z, boxPositon.z + boxSize.z);

	// Calculate the distance between the circle's center and this closest point
	glm::vec3 distance(0.0f);
	distance.x = circlePosition.x - closest.x;
	distance.y = circlePosition.y - closest.y;
	distance.z = circlePosition.z - closest.z;

	distance = abs(distance);

	float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z);
	if (distanceSquared < (circleCollider->getRadius() * circleCollider->getRadius())) {
		collision[0] = true;
		collision[1] = distance.x > 0;
		collision[2] = distance.y > 0;
		collision[3] = distance.z > 0;
		vector.push_back(ColliderComponent::getCollisionVector(collision, boxCollider->getPosition(), circleCollider->getPosition()));
	}
	return vector;
}

bool ColliderComponent::isZEnabled(ColliderComponent* collider1, ColliderComponent* collider2)
{
	return collider1->isZEnabled() && collider2->isZEnabled();
}

bool ColliderComponent::isZEnabled() const
{
	return _zEnabled;
}

void ColliderComponent::setPositionMove(glm::vec3 positionMove)
{
	_positionMove = positionMove;
}

void ColliderComponent::setZEnabled(bool enabled)
{
	_zEnabled = enabled;
}

bool ColliderComponent::isPassable() const
{
	return _passable;
}

void ColliderComponent::setPassable(bool passable)
{
	_passable = passable;
}
