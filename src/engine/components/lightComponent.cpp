#include "engine/components/lightComponent.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <engine\gameObject.hpp>


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

glm::mat4 LightComponent::getSpaceMatrix(float shadowNear, float shadowFar) const
{
    const glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, shadowNear, shadowFar);
    const glm::mat4 lightView = glm::lookAt(_gameObject->getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    return lightProjection * lightView;
}

void LightComponent::use(const Shader* shader) const {

}

