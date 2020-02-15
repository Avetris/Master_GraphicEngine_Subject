#ifndef __LIGHT_SYSTEM_H__
#define __LIGHT_SYSTEM_H__

#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>

class LightSystem : public System{
    public:
        LightSystem();
        void init();
        void update(const float dt);

        void setUseShadows(bool useShadows);
    private:
        bool _useShadows = true;
};

#endif
