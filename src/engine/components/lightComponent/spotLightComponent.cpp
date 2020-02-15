#include "engine/components/lightComponent/spotLightComponent.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>
#include <iostream>
#include <engine/gameObject.hpp>


SpotLightComponent::SpotLightComponent(uint16_t UID, GameObject* gameObject) : LightComponent(UID, gameObject) {}

void SpotLightComponent::setIndex(int index) {
    _name = "spotLight[" + std::to_string(index) + "]";
}

glm::vec3 SpotLightComponent::getDirection() const { return _direction; }
void SpotLightComponent::setDirection(const glm::vec3 direction) { _direction = direction; }
void SpotLightComponent::setConstat(const float constant) { _constant = constant; }
void SpotLightComponent::setLinear(const float linear) { _linear = linear; }
void SpotLightComponent::setQuadratic(const float quadratic) { _quadratic = quadratic; }
void SpotLightComponent::setCutOff(const float cutOff) { _cutOff = cutOff; }
void SpotLightComponent::setOuterCutOff(const float outerCutOff) { _outerCutOff = outerCutOff; }

void SpotLightComponent::use(const Shader& shader) const {
    shader.set((_name + ".position").c_str(), _gameObject->getPosition());
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