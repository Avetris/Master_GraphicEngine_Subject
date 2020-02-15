#ifndef __SPOT_LIGHT_COMPONENT_H__
#define __SPOT_LIGHT_COMPONENT_H__ 1

#include <glm/glm.hpp>
#include <cstdint>
#include <string>

#include "../lightComponent.hpp"

class Shader;

class SpotLightComponent : public LightComponent {
    public:
        explicit SpotLightComponent(uint16_t UID, GameObject* gameObject);

        void setIndex(int index) override;

        void setDirection(const glm::vec3 direction);
        void setConstat(const float constant);
        void setLinear(const float linear);
        void setQuadratic(const float quadratic);
        void setCutOff(const float cutOff);
        void setOuterCutOff(const float outerCutOff);

        glm::vec3 getDirection() const;

        void use(const Shader& shader) const;

    private:
        glm::vec3 _direction =glm::vec3(0,0,0);
        float _constant = 0.0f;
        float _linear = 0.0f;
        float _quadratic = 0.0f;
        float _cutOff = 0.0f;
        float _outerCutOff = 0.0f;
};

#endif