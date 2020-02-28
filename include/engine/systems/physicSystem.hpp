#ifndef __PHYSIC_SYSTEM_H__
#define __PHYSIC_SYSTEM_H__

#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\gpu.hpp>

class PhysicSystem : public System{
    public:
        PhysicSystem();
        void init();
        void update(const float dt);
};

#endif
