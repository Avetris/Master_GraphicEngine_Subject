#include "engine/systems/system.hpp"
#include <engine\handle\handleManager.hpp>

System::~System()
{
	Component* component;
	for (auto it = _componentList.end(); it >= _componentList.begin(); it--) {
		if (*it != nullptr && HandleManager::instance()->GetAs(*it, component)) {
			delete *it;
		}
	}
}

void System::addComponent(Handle* component)
{
	_componentList.push_back(component);
}

void System::removeComponent(Component* component)
{
	Component* comp;
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		HandleManager::instance()->GetAs(*it, comp);
		if (component != nullptr && comp->_UID == component->_UID) {
			_componentList.erase(it);
			return;
		}
	}
}

System::System(): Object(0){}
