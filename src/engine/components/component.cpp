#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>
#include <engine\gameObject.hpp>

Component::Component(uint16_t UID, GameObject* gameObject) : 
	Object(UID), 
	_gameObject(gameObject){}

Component::~Component()
{
	delete _gameObject;
}

bool Component::isEnable() const
{
	return _enable;
}
