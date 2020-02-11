#include <engine/systems/geometrySystem.hpp>
#include <engine/components/geometryComponent.hpp>
#include <engine\handle\handleManager.hpp>

GeometrySystem::GeometrySystem(){}

void GeometrySystem::init() {

}

void GeometrySystem::update(const float dt) {
	GeometryComponent* component;
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if (HandleManager::instance()->GetAs(*it, component)) {
			component->render();
		}
	}
}