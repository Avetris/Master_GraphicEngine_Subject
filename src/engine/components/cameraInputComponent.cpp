#include "engine/components/cameraInputComponent.hpp"
#include <engine/gameObject.hpp>

CameraInputComponent::CameraInputComponent(uint16_t UID, GameObject* gameObject) : InputComponent(UID, gameObject) {}

void CameraInputComponent::onKeyPressed(GPU::KeyId key, GPU::KeyActions action) {
}

void CameraInputComponent::onMouseMoved(float x, float y) {
    if (_camera) {
        if (firstMouse) {
            firstMouse = false;
            lastX = x;
            lastY = y;
        }

        const float xoffset = x - lastX;
        const float yoffset = lastY - y;
        lastX = x;
        lastY = y;
        _camera->handleMouseMovement(xoffset, yoffset);
    }
}

void CameraInputComponent::onScrollMoved(float x, float y) {
    if (_camera)
        _camera->handleMouseScroll(y);
}

void CameraInputComponent::init() {
    _camera = _gameObject->getComponent<CameraComponent>(ComponentType::CAMERA_COMPONENT);
}

void CameraInputComponent::update(float dt) {
    if (_camera) {
        if (isKeyPressed(GPU::KeyId::W)) {
            _camera->handleKeyboard(InputMovement::Forward, dt);
        }
        if (isKeyPressed(GPU::KeyId::S)) {
            _camera->handleKeyboard(InputMovement::Backward, dt);
        }
        if (isKeyPressed(GPU::KeyId::A)) {
            _camera->handleKeyboard(InputMovement::Left, dt);
        }
        if (isKeyPressed(GPU::KeyId::D)) {
            _camera->handleKeyboard(InputMovement::Right, dt);
        }
    }
}

void CameraInputComponent::setEnable(bool enable)
{
    Component::setEnable(enable);
    _gameObject->getComponent<CameraComponent>(ComponentType::CAMERA_COMPONENT)->reset();
}
