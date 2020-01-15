#include "engine/light/spotLight.hpp"
#include "engine/light/light.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>
#include <iostream>


SpotLight::SpotLight(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, glm::vec3 direction, float cutOff, float outerCutOff) : Light(name, position, ambient, diffuse, specular), _constant(constant), _linear(linear), _quadratic(quadratic), _direction(direction), _cutOff(cutOff), _outerCutOff(outerCutOff) {
}

void SpotLight::setDirection(const glm::vec3 direction) { _direction = direction; }
void SpotLight::setConstat(const float constant) { _constant = constant; }
void SpotLight::setLinear(const float linear) { _linear = linear; }
void SpotLight::setQuadratic(const float quadratic) { _quadratic = quadratic; }
void SpotLight::setCutOff(const float cutOff) { _cutOff = cutOff; }
void SpotLight::setOuterCutOff(const float outerCutOff) { _outerCutOff = outerCutOff; }


void SpotLight::use(const Shader& shader) const {
    shader.set((_name + ".position").c_str(), _position);
    shader.set((_name + ".direction").c_str(), _direction);
    shader.set((_name + ".ambient").c_str(), _ambient);
    shader.set((_name + ".diffuse").c_str(), _diffuse);
    shader.set((_name + ".specular").c_str(), _specular);
    shader.set((_name + ".constant").c_str(), _constant);
    shader.set((_name + ".linear").c_str(), _linear);
    shader.set((_name + ".quadratic").c_str(), _quadratic);
    shader.set((_name + ".cutOff").c_str(), _cutOff);
    shader.set((_name + ".outerCutOff").c_str(), _outerCutOff);
}