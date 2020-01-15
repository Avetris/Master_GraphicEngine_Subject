#include "engine/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
 : _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}


glm::mat4 Camera::getViewMatrix(bool customLookAt) const {
    if (customLookAt) {
        glm::mat4 translation(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            -_position.x, -_position.y, -_position.z, 1);
        glm::vec3 cameraDirection = glm::normalize(_front);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDirection, _up));
        glm::vec3 cameraUp = glm::cross(cameraRight, cameraDirection);
        glm::mat4 matrix(cameraRight.x, cameraUp.x, -cameraDirection.x, 0,
            cameraRight.y, cameraUp.y, -cameraDirection.y, 0,
            cameraRight.z, cameraUp.z, -cameraDirection.z, 0,
            0, 0, 0, 1);

        return matrix * translation;
    }
    else {
        return glm::lookAt(_position, _position + _front, _up);
    }
}

glm::vec3 Camera::getCameraDirection() const {
    return glm::normalize(_front);
}

float Camera::getFOV() const {
    return _fov;
}

glm::vec3 Camera::getPosition() const {
    return _position;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

void Camera::handleKeyboard(Movement direction, float dt, bool canFly) {
    const float velocity = k_Speed * dt;
    glm::vec3 movement(0,0,0);

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

