#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\gpu.hpp>

class InputSystem : public System{
    public:
        InputSystem();
        void init();
        void update(const float dt);

        void keyPressed(GPU::KeyId key, GPU::KeyActions action);

        void mouseMoved(float x, float y);
        void scrollMoved(float x, float y);
};

#endif
