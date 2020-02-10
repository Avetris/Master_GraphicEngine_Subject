#ifndef __TRANSFORM_SYSTEM_H__
#define __GRAPHIC_SYSTEM__TRANSFORM_SYSTEM_H___H__

#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>

class TransformSystem : public System{
    public:
        TransformSystem();
        void init();
        void update(const float dt);
};

#endif
