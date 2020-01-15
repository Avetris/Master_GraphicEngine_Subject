#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__ 1

#include <glm/glm.hpp>
#include <cstdint>
#include <string>

#include "light.hpp"

class Shader;

class SpotLight : public Light {
    public:
        explicit SpotLight(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
        SpotLight() = delete;

        void setConstat(const float constant);
        void setLinear(const float linear);
        void setQuadratic(const float quadratic);

        void use(const Shader& shader) const;

    private:
        float _constant = 0.0f;
        float _linear = 0.0f;
        float _quadratic = 0.0f;
};

#endif