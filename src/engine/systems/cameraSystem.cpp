#include <engine/systems/cameraSystem.hpp>
#include <engine/components/cameraComponent.hpp>
#include <engine\handle\handleManager.hpp>

CameraSystem::CameraSystem() {
	init();
}

void CameraSystem::init() {

}

void CameraSystem::update(const float dt) {
	CameraComponent* component;
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		HandleManager::instance()->GetAs(*it, component);
		if (component != nullptr && component->isEnable()) {

		}
	}
}