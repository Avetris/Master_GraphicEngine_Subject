#include <engine/systems/cameraSystem.hpp>
#include <engine/components/cameraComponent.hpp>

CameraSystem::CameraSystem() {}

CameraComponent* CameraSystem::getMainCamera()
{
	if (_mainCamera == nullptr){
		if (_componentList.size() > 0) {
			_mainCamera = static_cast<CameraComponent*>(_componentList.at(0));
		}
		else {
			throw "No Main Camera Exception";
		}
	}
	return _mainCamera;
}
