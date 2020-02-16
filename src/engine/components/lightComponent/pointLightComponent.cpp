#include "engine/components/lightComponent/pointLightComponent.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <engine/gameObject.hpp>


PointLightComponent::PointLightComponent(uint16_t UID, GameObject* gameObject) : LightComponent(UID, gameObject) {}

void PointLightComponent::setIndex(int index) {
    _name = "pointLight[" + std::to_string(index) + "]";
}

void PointLightComponent::setConstat(float constant) {_constant = constant;}
void PointLightComponent::setLinear(float linear) {_linear = linear;}
void PointLightComponent::setQuadratic(float quadratic) {_quadratic = quadratic;}

void PointLightComponent::use(const Shader* shader) const {
    shader->set((_name + ".position").c_str(), _gameObject->getPosition());
    shader->set((_name + ".ambient").c_str(), _ambient);
    shader->set((_name + ".diffuse").c_str(), _diffuse);
    shader->set((_name + ".specular").c_str(), _specular);
    shader->set((_name + ".constant").c_str(), _constant);
    shader->set((_name + ".linear").c_str(), _linear);
    shader->set((_name + ".quadratic").c_str(), _quadratic);
}