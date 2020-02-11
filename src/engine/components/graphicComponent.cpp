#include "engine/components/graphicComponent.hpp"
#include "engine/systems/graphicSystem.hpp"
#include <engine\gameObject.hpp>
#include <engine\handle\handleManager.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine\engine.hpp>
//#include <engine\systems\graphicSystem.hpp>

GraphicComponent::GraphicComponent(Handle* shader, uint16_t UID, Handle* gameObject) : Component(UID, gameObject), _shader(shader) {}

void GraphicComponent::init() {
}

void GraphicComponent::update(float dt) {
	Material* mat;
	Shader* shad;
	if (HandleManager::instance()->GetAs(_shader, shad)) {
		if (HandleManager::instance()->GetAs(_material, mat)) {
			mat->use(*shad);
		}
	}
}

GraphicComponent::~GraphicComponent() {
	Engine::instance()->getSystem<GraphicSystem>()->removeComponent(this);
	GameObject* gameObject;
	HandleManager::instance()->GetAs(_gameObject, gameObject);
	gameObject->removeComponent(GRAPHIC_COMPONENT);
}

void GraphicComponent::setMaterial(Material* material)
{
	_material = HandleManager::instance()->Add(material, 0);
}

void GraphicComponent::setShader(Handle* shader)
{
	_shader = shader;
}

void GraphicComponent::setShader(Shader* shader)
{
	HandleManager::instance()->Add(shader);
}



