#ifndef __GRAPHIC_SYSTEM_H__
#define __GRAPHIC_SYSTEM_H__

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>

static std::string SHADER_PATH = "shaders/";

class GraphicSystem : public System{
    public:
        enum GENERIC_SHADER_TYPE {
            BLINN,
            BLEND,
            LIGHT,
            SHADOW,
        };

        GraphicSystem();
        void init();
        void update(const float dt);

        Shader* getShader(GENERIC_SHADER_TYPE type);
        void positionRefresh();
        
    private:
        void sortObjectsToRender();

        bool _positionRefresh = true;
        std::unordered_map<GENERIC_SHADER_TYPE, Shader*> _defaultShaders;
};

#endif
