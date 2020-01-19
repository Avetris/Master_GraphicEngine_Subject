#include "engine/light/pointLight.hpp"
#include "engine/light/light.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>


PointLight::PointLight(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) : Light(name, position, ambient, diffuse, specular), _constant(constant), _linear(linear), _quadratic(quadratic) {
    std::cout << name << std::endl;
    std::cout << _name << std::endl;
}

void PointLight::setConstat(float constant) {_constant = constant;}
void PointLight::setLinear(float linear) {_linear = linear;}
void PointLight::setQuadratic(float quadratic) {_quadratic = quadratic;}

void PointLight::use(const Shader& shader) const {
    shader.set((_name + ".position").c_str(), _position);
    shader.set((_name + ".ambient").c_str(), _ambient);
    shader.set((_name + ".diffuse").c_str(), _diffuse);
    shader.set((_name + ".specular").c_str(), _specular);
    shader.set((_name + ".constant").c_str(), _constant);
    shader.set((_name + ".linear").c_str(), _linear);
    shader.set((_name + ".quadratic").c_str(), _quadratic);
}