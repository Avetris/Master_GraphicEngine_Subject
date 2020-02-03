#include "engine/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const Vector3<float> position, const const Vector3<float> up, float yaw, float pitch)
 : _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _position(Vector3<float>(posX, posY, posZ)), _worldUp(Vector3<float>(upX, upY, upZ)), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}


glm::mat4 Camera::getViewMatrix() const {
    return GPU::lookAt(_position, _position + _front, _up);
}

Vector3<float> Camera::getCameraDirection() const {
    return GPU::normalize(_front);
}

float Camera::getFOV() const {
    return _fov;
}

Vector3<float> Camera::getPosition() const {
    return _position;
}

void Camera::updateCameraVectors() {
    Vector3<float> front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = GPU::normalize(front);

    _right = GPU::normalize(GPU::cross(_front, _worldUp));
    _up = GPU::normalize(GPU::cross(_right, _front));
}

void Camera::handleKeyboard(Movement direction, float dt, bool canFly) {
    const float velocity = k_Speed * dt;
    Vector3<float> movement(0,0,0);

    switch (direction) {
        case Movement::Forward: movement = _front * velocity;break;
        case Movement::Backward: movement = _front * -velocity; break;
        case Movement::Left: movement = _right * -velocity; break;
        case Movement::Right: movement = _right * velocity; break;
        default:;
    }
    _position.x += movement.x;
    _position.z += movement.z;
    if (canFly) {
        _position.y += movement.y;
    }
}

void Camera::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
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

void Camera::handleMouseScroll(float yoffset) {
    if (_fov >= 1.0f && _fov <= 45.0f) _fov -= yoffset;
    if (_fov <= 1.0f) _fov = 1.0f;
    if (_fov >= 45.0f) _fov = 45.0f;
}

