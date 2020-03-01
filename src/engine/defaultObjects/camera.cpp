#include <engine\defaultObjects\camera.hpp>
#include <engine\components\cameraComponent.hpp>
#include <engine\components\cameraInputComponent.hpp>

Camera::Camera(uint16_t UID) : GameObject(UID) {
	init();
}

Camera::Camera(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Camera::init() {
	CameraInputComponent* input = addComponent<CameraInputComponent>(ComponentType::INPUT_COMPONENT);
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
	addComponent<CameraComponent>(ComponentType::CAMERA_COMPONENT);
	input->setEnable(false);
	//pointLightComponent->
}