#include "engine/light/light.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>


Light::Light(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : _name(name), _position(position), _ambient(ambient), _diffuse(diffuse), _specular(specular){
}

void Light::setName(std::string name) { _name = name; }
void Light::setPosition(glm::vec3 position) { _position = position; }
glm::vec3 Light::getPosition() const { return _position; }
void Light::setColor(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular) {
    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
}
glm::vec3 Light::getSpecular() const { return _specular; }

void Light::use(const Shader& shader) const {

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