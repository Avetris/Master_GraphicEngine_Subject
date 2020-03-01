#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include <unordered_map>
#include <vector>
#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\shader.hpp>

static std::string SHADER_PATH = "../src/engine/systems/shaders/";

const enum class GenericShaderType {
    BLINN,
    BLEND,
    LIGHT,
    SHADOW,
    UI,
};

class RenderSystem : public System{
    public:
        RenderSystem();
        void init();
        void update(const float dt);
        void renderForShadow(Shader* shader);
        Shader* getShader(GenericShaderType type);
        virtual void addComponent(Component* component) override;
        virtual void removeComponent(Component* component) override;
        void setReloadShaders();
        std::vector<Shader*> getUsedShaders();
    private:
        std::unordered_map<GenericShaderType, Shader*> _defaultShaders;
        std::vector<Shader*> _usedShaders;
        bool _reloadShaders;
};

#endif
