#include "engine/components/graphicComponent.hpp"
#include "engine/systems/graphicSystem.hpp"
#include <engine\gameObject.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine\engine.hpp>
//#include <engine\systems\graphicSystem.hpp>

GraphicComponent::GraphicComponent(uint16_t UID, GameObject* gameObject) : Component(UID, gameObject){
	_shader = Engine::instance()->getSystem<GraphicSystem>()->getShader(GraphicSystem::GENERIC_SHADER_TYPE::BLINN);
}

void GraphicComponent::init() {
}

void GraphicComponent::update(float dt) {
	_material->use(*_shader);
}

GraphicComponent::~GraphicComponent() {
	Engine::instance()->getSystem<GraphicSystem>()->removeComponent(this);
	_gameObject->removeComponent(GRAPHIC_COMPONENT);
}

void GraphicComponent::setMaterial(Material* material)
{
	_material = material;
}

void GraphicComponent::setShader(Shader* shader)
{
	_shader = shader;
}



