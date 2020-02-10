#ifndef __GRAPHIC_SYSTEM_H__
#define __GRAPHIC_SYSTEM_H__

#include <cstdint>
#include <vector>
#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>

class GraphicSystem : public System{
    public:
        static GraphicSystem* instance() {
            GraphicSystem graphInstance;
            return &graphInstance;
        }
        void init();
        void update(const float dt);

        void positionRefresh();
        
    private:
        GraphicSystem();
        std::vector<Handle*> _objectsToRender;
        void checkObjectsToRender();

        bool _positionRefresh = true;
};

#endif
