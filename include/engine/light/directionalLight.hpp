#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__ 1

#include <glm/glm.hpp>
#include <cstdint>

#include "light.hpp"

class Shader;

class DirectionalLight: public Light {
    public:
        explicit DirectionalLight(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
        DirectionalLight() = delete;

        void setDirection(const glm::vec3 direction);

        void use(const Shader& shader) const;
        
    private:
        glm::vec3 _direction;
};

#endif