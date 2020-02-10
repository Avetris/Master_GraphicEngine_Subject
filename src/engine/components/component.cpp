#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>
#include <engine\handle\handleManager.hpp>
#include <engine\gameObject.hpp>

Component::Component(uint16_t UID, Handle* gameObject) : 
	Object(UID), 
	_gameObject(gameObject){}

Component::~Component()
{
	GameObject* object;
	if (HandleManager::instance()->GetAs(_gameObject, object)) {
		object->removeComponent(_handle);
	}
	HandleManager::instance()->Remove(_handle);
}

bool Component::isEnable() const
{
	return _isEnable;
}
