#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include <unordered_map>
#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\shader.hpp>

static std::string SHADER_PATH = "../src/engine/systems/shaders/";

const enum class GenericShaderType {
    BLINN,
    BLEND,
    LIGHT,
    SHADOW,
};

class RenderSystem : public System{
    public:
        RenderSystem();
        void init();
        void update(const float dt);
        Shader* getShader(GenericShaderType type);
    private:
        std::unordered_map<GenericShaderType, Shader*> _defaultShaders;
};

#endif
