#ifndef __POINT_LIGHT_COMPONENT_H__
#define __POINT_LIGHT_COMPONENT_H__ 1

#include <glm/glm.hpp>
#include <cstdint>
#include <string>

#include "../lightComponent.hpp"

class Shader;

class PointLightComponent : public LightComponent {
    public:
        explicit PointLightComponent(uint16_t UID, GameObject* gameObject);

        void setIndex(int index) override;

        void setConstat(float constant);
        void setLinear(float linear);
        void setQuadratic(float quadratic);

        void use(const Shader* shader) const;

    private:
        float _constant = 1.0f;
        float _linear = 0.2f;
        float _quadratic = 0.06f;
};

#endif