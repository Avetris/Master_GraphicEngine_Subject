#ifndef __LIGHT_SYSTEM_H__
#define __LIGHT_SYSTEM_H__

#include <engine\systems\system.hpp>
#include <engine\components\component.hpp>
#include <engine\components\lightComponent.hpp>
#include <engine\systems\shadowFBO.hpp>

class LightSystem : public System{
    public:
        LightSystem();
        void init();
        void update(const float dt);

        void renderLights(Shader* shader);
        void setUseShadows(bool useShadows);
        void setShadowDistances(float shadowNear, float shadowFar);
    private:
        void updateIndex(LightComponent* component);
        int _numDirecLights = 0;
        int _numSpotLights = 0;
        int _numPointLights = 0;
        bool _numShadersChecked = false;
        
        bool _useShadows = true;
        int _numberShadows = 0;
        float _shadowNear = 1.0f;
        float _shadowFar = 7.5f;
        std::vector<glm::mat4> _lightSpaceMatrix;
        ShadowFBO* _shadowFBO;

};

#endif
