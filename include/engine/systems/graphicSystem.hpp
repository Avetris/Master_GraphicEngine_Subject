#ifndef __GRAPHIC_SYSTEM_H__
#define __GRAPHIC_SYSTEM_H__

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>

std::string SHADER_PATH = "../projects/AG10/";

class GraphicSystem : public System{
    public:
        enum GENERIC_SHADER_TYPE {
            BLINN = 0,
            BLEND = 1,
            LIGHT = 2,
            SHADOW = 3,
        };

        GraphicSystem();
        void init();
        void update(const float dt);

        Handle* getShader(GENERIC_SHADER_TYPE type) const;
        void positionRefresh();
        
    private:
        std::vector<Handle*> _objectsToRender;
        void checkObjectsToRender();

        bool _positionRefresh = true;
        std::unordered_map<GENERIC_SHADER_TYPE, Handle*> _defaultShaders;
};

#endif
