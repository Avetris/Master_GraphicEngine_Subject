
#ifndef __LIGHT_COMPONENT_H__
#define __LIGHT_COMPONENT_H__ 1

#include "component.hpp"
#include <glm/glm.hpp>
#include <cstdint>
#include <string>

class Shader;

class LightComponent : public Component {
    public:
        LightComponent(uint16_t UID, GameObject* gameObject);
        
        virtual void setIndex(int index);
        void setColor(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular);
        virtual glm::mat4 getSpaceMatrix(float shadowNear, float shadowFar) const;

        virtual void use(const Shader* shader) const;
        
    protected:
        std::string _name = "";
        glm::vec3 _ambient = glm::vec3(1.0f);
        glm::vec3 _diffuse = glm::vec3(1.0f);
        glm::vec3 _specular = glm::vec3(1.0f);
};

#endif