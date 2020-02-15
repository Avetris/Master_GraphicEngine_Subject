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
/*
void Light::render(glm::mat4 view, glm::mat4 proj) const {

    _shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    model = glm::scale(model, glm::vec3(0.25f));
    _shader.set("model", model);
    _shader.set("view", view);
    _shader.set("proj", proj);
    _shader.set("lightColor", _color);

    _shader.render();
}*/