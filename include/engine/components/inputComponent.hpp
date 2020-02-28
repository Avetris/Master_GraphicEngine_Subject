#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include <engine\window.hpp>
#include "component.hpp"
#include <iostream>

class InputComponent: public Component {
    public:
        InputComponent(uint16_t UID, GameObject* gameObject);

        virtual void onKeyPressed(GPU::KeyId key, GPU::KeyActions action);

        virtual void onMouseMoved(float x, float y);

        virtual void onScrollMoved(float x, float y);
    
        void onKeyDown(GPU::KeyId key);

        void onKeyUp(GPU::KeyId key);

        void onKeyRepeat(GPU::KeyId key);

        virtual void init();
        virtual void update(float dt);

        static bool isKeyPressed(GPU::KeyId key);
    };

#endif