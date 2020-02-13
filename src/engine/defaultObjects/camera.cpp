#include <engine\defaultObjects\camera.hpp>
#include <engine\components\cameraComponent.hpp>

Camera::Camera(uint16_t UID) : GameObject(UID) {
	addComponent<CameraComponent>(CAMERA_COMPONENT);
}

Camera::Camera(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : GameObject(UID, position, rotation, scale) {
	addComponent<CameraComponent>(CAMERA_COMPONENT);
}