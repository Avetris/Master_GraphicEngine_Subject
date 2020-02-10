#ifndef __TRANSFORM_SYSTEM_H__
#define __GRAPHIC_SYSTEM__TRANSFORM_SYSTEM_H___H__

#include <cstdint>
#include <vector>
#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>

class TransformSystem : public System{
    public:
        static TransformSystem* instance() {
            TransformSystem tranInstance;
            return &tranInstance;
        }
        void init();
        void update(const float dt);
        
    private:
        TransformSystem();
};

#endif
