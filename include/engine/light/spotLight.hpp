#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__ 1

#include <glm/glm.hpp>
#include <cstdint>
#include <string>

#include "light.hpp"

class Shader;

class SpotLight : public Light {
    public:
        explicit SpotLight(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, glm::vec3 direction, float cutOff, float outerCutOff);
        SpotLight() = delete;

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