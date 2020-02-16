#include "engine/components/lightComponent/directionalLightComponent.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>


DirectionalLightComponent::DirectionalLightComponent(uint16_t UID, GameObject* gameObject): LightComponent(UID, gameObject) {}

void DirectionalLightComponent::setIndex(int index) {
    _name = "dirLight[" + std::to_string(index) + "]";
}

void DirectionalLightComponent::setDirection(const glm::vec3 direction) {
	_direction = direction;
}

void DirectionalLightComponent::use(const Shader* shader) const {
    shader->set((_name + ".direction").c_str(), _direction);
    shader->set((_name + ".ambient").c_str(), _ambient);
    shader->set((_name + ".diffuse").c_str(), _diffuse);
    shader->set((_name + ".specular").c_str(), _specular);
}