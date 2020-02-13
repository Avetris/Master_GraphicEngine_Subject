#ifndef __GEOMETRY_SYSTEM_H__
#define __GEOMETRY_SYSTEM_H__

#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>

class RenderSystem : public System{
    public:
        RenderSystem();
        void init();
        void update(const float dt);
};

#endif
