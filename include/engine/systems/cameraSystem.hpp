#ifndef __CAMERA_SYSTEM_H__
#define __CAMERA_SYSTEM_H__

#include <cstdint>
#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>

class CameraSystem : public System{
    public:
        static CameraSystem* instance() {
            static CameraSystem camInstance;
            return &camInstance;
        }
        void init();
        void update(const float dt);
    private:
        CameraSystem();
};

#endif
