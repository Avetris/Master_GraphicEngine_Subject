#include "engine/components/cameraComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <engine\gameObject.hpp>
#include <engine\handle\handleManager.hpp>
#include <engine\components\transformComponent.hpp>

CameraComponent::CameraComponent(uint16_t UID, Handle* gameObject):Component(UID, gameObject){ updateCameraVectors(); }

void CameraComponent::init() {
    updateCameraVectors();
}

void CameraComponent::update(float dt) {

}

CameraComponent::~CameraComponent() {

}

glm::mat4 CameraComponent::getViewMatrix() const {
    GameObject* object;
    if (HandleManager::instance()->GetAs(_gameObject, object)) {
        return glm::lookAt(object->getPosition(), object->getPosition() + _front, _up);
    }
    return glm::mat4(0.0f);
}

glm::vec3 CameraComponent::getCameraDirection() const {
    return glm::normalize(_front);
}

float CameraComponent::getFOV() const {
    return _fov;
}

void CameraComponent::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

void CameraComponent::handleKeyboard(Movement direction, float dt) {
    const float velocity = k_Speed * dt;
    glm::vec3 movement(0,0,0);

    GameObject* object;
    if (HandleManager::instance()->GetAs(_gameObject, object)) {
        switch (direction) {
            case Movement::Forward: movement = _front * velocity; break;
            case Movement::Backward: movement = _front * -velocity; break;
            case Movement::Left: movement = _right * -velocity; break;
            case Movement::Right: movement = _right * velocity; break;
            default:;
        }
        TransformComponent* transform = object->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
        if(transform != nullptr){
            transform->move(movement);
        }
    }

}

void CameraComponent::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    const float xoff = xoffset * k_Sensitivity;
    const float yoff = yoffset * k_Sensitivity;

    _yaw += xoff;
    _pitch += yoff;

    if (constrainPitch) {
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
    }

    updateCameraVectors();
}

void CameraComponent::handleMouseScroll(float yoffset) {
    if (_fov >= 1.0f && _fov <= 45.0f) _fov -= yoffset;
    if (_fov <= 1.0f) _fov = 1.0f;
    if (_fov >= 45.0f) _fov = 45.0f;
}

