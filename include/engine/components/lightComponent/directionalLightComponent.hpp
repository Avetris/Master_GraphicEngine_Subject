#ifndef __DIRECTIONAL_LIGHT_COMPONENT_H__
#define __DIRECTIONAL_LIGHT_COMPONENT_H__ 1

#include <glm/glm.hpp>
#include <cstdint>

#include "../lightComponent.hpp"

class Shader;

class DirectionalLightComponent : public LightComponent {
    public:
        explicit DirectionalLightComponent(uint16_t UID, GameObject* gameObject);

        void setIndex(int index) override;
        void setDirection(const glm::vec3 direction);
        void use(const Shader* shader) const;
        
    private:
        glm::vec3 _direction;
};

#endif