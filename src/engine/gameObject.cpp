#include <engine\gameObject.hpp>

GameObject::GameObject(uint16_t UID) :
	Object(UID),
	_position(0.0f), 
	_rotation(0.0f), 
	_scale(1.0f),
	_originalPosition(0.0f){}

GameObject::GameObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float _rotationAngle) :
	Object(UID),
	_position(position),
	_rotation(rotation),
	_scale(scale),
	_rotationAngle(_rotationAngle),
	_originalPosition(position) {}

GameObject::~GameObject()
{
	bool exist = false;
	for (Component* component : _componentList) {
		if (component != nullptr) {
			delete component;
		}
	}
}

glm::vec3 GameObject::getPosition() const
{
	return _position;
}

glm::vec3 GameObject::getRotation() const
{
	return _rotation;
}

glm::vec3 GameObject::getScale() const
{
	return _scale;
}

float GameObject::getRotationAngle() const
{
	return _rotationAngle;
}

void GameObject::setPosition(glm::vec3 position)
{
	_position = position;
}

void GameObject::setRotation(float angle, glm::vec3 rotation)
{
	_rotationAngle = angle;
	_rotation = rotation;
}

void GameObject::setScale(glm::vec3 scale)
{
	_scale = scale;
}

void GameObject::removeComponent(Component* component)
{
	for (size_t i = 0; i < NUMBER_COMPONENTS; i++) {
		if (_componentList[i] != nullptr && _componentList[i] == component) {
			delete _componentList[i];
			_componentList[i] = nullptr;
			return;
		}
	}
}

void GameObject::removeComponent(ComponentType componentType)
{
	if ((int) componentType > 0) {
		_componentList[(int) componentType] = nullptr;
	}
}

void GameObject::addChildren(GameObject* child)
{
	bool exist = false;
	GameObject* gameobject;
	for (auto it = _children.begin(); !exist && it < _children.end(); it++) {
		exist = (*it)->_UID == child->_UID;
	}

	if (!exist) {
		_children.push_back(child);
	}
}

std::vector<GameObject*> GameObject::getChildren() const
{
	return _children;
}

GameObject* GameObject::removeChildren(uint16_t UID)
{
	GameObject* removedChild = nullptr;

	for (auto it = _children.begin(); it < _children.end(); it++) {
		if ((*it)->_UID == UID) {
			removedChild = *it;
			_children.erase(it);
			break;
		}
	}
	return removedChild;
}

void GameObject::resetPosition()
{
	setPosition(_originalPosition);
}
