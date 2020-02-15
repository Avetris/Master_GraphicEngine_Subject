#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include <engine\window.hpp>
#include <engine\components\component.hpp>

class GameObject;

class InputComponent: public Component {
    public:
        InputComponent(uint16_t UID, GameObject* gameObject) : Component(UID, gameObject){}

        virtual void onKeyPressed(GPU::KeyId key, GPU::KeyActions action) = 0;
        virtual void onMouseMoved(float x, float y) = 0;
        virtual void onScrollMoved(float x, float y) = 0;
    
        virtual void onKeyDown(GPU::KeyId key) {

        }

        virtual void onKeyUp(GPU::KeyId key) {

        }

        virtual void onKeyRepeat(GPU::KeyId key) {

        }

        virtual void init() = 0;
        virtual void update(float dt) = 0;

        bool isKeyPressed(GPU::KeyId key) {
            return Window::instance()->keyPressed((int)key);
        }
    };

#endif