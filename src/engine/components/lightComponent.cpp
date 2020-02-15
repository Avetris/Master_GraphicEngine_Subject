#include "engine/components/lightComponent.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>


LightComponent::LightComponent(uint16_t UID, GameObject* gameObject)
    : Component(UID, gameObject){}

void LightComponent::setIndex(int index) { 
    _name += std::to_string(index);
}
void LightComponent::setColor(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular) {
    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
}

void LightComponent::use(const Shader& shader) const {

}