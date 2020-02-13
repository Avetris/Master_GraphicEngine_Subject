#include <engine/systems/cameraSystem.hpp>
#include <engine/components/cameraComponent.hpp>

CameraSystem::CameraSystem() {}

void CameraSystem::init() {

}

void CameraSystem::update(const float dt) {
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {

		}
	}
}