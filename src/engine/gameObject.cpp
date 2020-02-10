#include <engine\gameObject.hpp>
#include <engine\handle\handleManager.hpp>
#include <engine\components\transformComponent.hpp>

GameObject::GameObject(uint16_t UID) :
	Object(UID),
	_position(0.0f), 
	_rotation(0.0f), 
	_scale(1.0f){}

GameObject::GameObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
	Object(UID),
	_position(position),
	_rotation(rotation), 
	_scale(scale){}

GameObject::~GameObject()
{
	bool exist = false;
	for (Handle* h : _componentList) {
		Component* component;
		exist = HandleManager::instance()->GetAs(h, component);
		if (exist) delete component;
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

void GameObject::removeComponent(Handle* componentHandle)
{
	Component* component;
	if (HandleManager::instance()->GetAs(componentHandle, component)) {
		Component* currentComponent;
		for (size_t i = 0; i < NUMBER_COMPONENTS; i++) {
			if (_componentList[i] != nullptr && HandleManager::instance()->GetAs(_componentList[i], currentComponent)) {
				if (currentComponent->_UID == component->_UID) {
					_componentList[i] = nullptr;
					return;
				}
			}
		}
	}
}

void GameObject::removeComponent(TYPE componentType)
{
	if (componentType > 0) {
		_componentList[componentType] = nullptr;
	}
}

template<typename T>
T* GameObject::addComponent(TYPE componentType)
{
	T* component = getComponent(componentType);
	if (component == nullptr) {
		component = ComponentManager::instance()->createComponent(_handle, componentType);
		_componentList[componentType] = component->getHandle();
	}
	return component;
}

template<typename T>
T* GameObject::getComponent(TYPE componentType) const
{
	T* component = nullptr;
	if (componentType >= 0 && _componentList[componentType] != nullptr) {
		HandleManager::instance()->GetAs(_componentList[componentType], component);
	}
	return component;
}

void GameObject::addChildren(Handle* child)
{
	bool exist = false;
	GameObject* gameobject;
	GameObject* gameobjectChild;
	HandleManager::instance()->GetAs(child, gameobjectChild);
	for (auto it = _children.begin(); !exist && it < _children.end(); it++) {
		HandleManager::instance()->GetAs(*it, gameobject);
		exist = gameobject->_UID == gameobjectChild->_UID;
	}

	if (!exist) {
		_children.push_back(child);
	}
}

std::vector<Handle*> GameObject::getChildren() const
{
	return _children;
}

GameObject* GameObject::removeChildren(uint16_t UID)
{
	GameObject* gameObject = nullptr;

	for (auto it = _children.begin(); it < _children.end(); it++) {
		HandleManager::instance()->GetAs(*it, gameObject);
		if (gameObject->_UID == UID) {
			_children.erase(it);
			break;
		}
	}
	return gameObject;
}

