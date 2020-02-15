#include <engine/systems/lightSystem.hpp>
#include <iostream>

LightSystem::LightSystem(){}

void LightSystem::init() {
}

void LightSystem::update(const float dt) {
	int 
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			(*it)->update(dt);
		}
	}
}

void LightSystem::setUseShadows(bool useShadows)
{
	_useShadows = useShadows;
}
