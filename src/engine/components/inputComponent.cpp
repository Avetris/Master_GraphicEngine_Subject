#include <engine/components/inputComponent.hpp>
#include <engine/gameObject.hpp>

InputComponent::InputComponent(uint16_t UID, GameObject* gameObject) : Component(UID, gameObject){}

void InputComponent::onKeyPressed(GPU::KeyId key, GPU::KeyActions action) {
    if (getGameObject()) {
        getGameObject()->onKeyPressed(key, action);
    }
}

void  InputComponent::onMouseMoved(float x, float y) {
    if (getGameObject()) {
        getGameObject()->onMouseMoved(x, y);
    }
}

void  InputComponent::onScrollMoved(float x, float y) {
    if (getGameObject()) {
        getGameObject()->onScrollMoved(x, y);
    }
}
    
void  InputComponent::onKeyDown(GPU::KeyId key){
    if (getGameObject()) {
        getGameObject()->onKeyDown(key);
    }
}

void  InputComponent::onKeyUp(GPU::KeyId key) {
    if (getGameObject()) {
        getGameObject()->onKeyUp(key);
    }
}

void InputComponent::onKeyRepeat(GPU::KeyId key) {
    if (getGameObject()) {
        getGameObject()->onKeyRepeat(key);
    }
}

void InputComponent::init() {}
void InputComponent::update(float dt){
    if (getGameObject()) {
        getGameObject()->onUpdateInput(dt);
    }
}

bool InputComponent::isKeyPressed(GPU::KeyId key) {
    return Window::instance()->keyPressed((int)key);
}