#include "engine/light/directionalLight.hpp"
#include "engine/light/light.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>


DirectionalLight::DirectionalLight(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction) : Light(name, position, ambient, diffuse, specular), _direction(direction){
}

void DirectionalLight::setDirection(const glm::vec3 direction) {
	_direction = direction;
}

void DirectionalLight::use(const Shader& shader) const {
    shader.set((_name + ".direction").c_str(), _direction);
    shader.set((_name + ".ambient").c_str(), _ambient);
    shader.set((_name + ".diffuse").c_str(), _diffuse);
    shader.set((_name + ".specular").c_str(), _specular);
}