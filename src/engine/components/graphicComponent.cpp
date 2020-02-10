#include "engine/components/graphicComponent.hpp"
#include "engine/systems/graphicSystem.hpp"
#include <engine\gameObject.hpp>
#include <engine\handle\handleManager.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine\engine.hpp>
//#include <engine\systems\graphicSystem.hpp>

GraphicComponent::GraphicComponent(uint16_t UID, Handle* gameObject) : Component(UID, gameObject) {}

void GraphicComponent::init() {
}

void GraphicComponent::update(float dt) {
	Material* mat;

	if (HandleManager::instance()->GetAs(_material, mat)) {
		//	mat->use();
	}
}

GraphicComponent::~GraphicComponent() {
	GraphicSystem* system;
	if(Engine::instance()->getSystem(system)){
		system->removeComponent(this);
	}
	GameObject* gameObject;
	HandleManager::instance()->GetAs(_gameObject, gameObject);
	gameObject->removeComponent(GRAPHIC_COMPONENT);
}

void GraphicComponent::setMaterial(Material* material)
{
	_material = HandleManager::instance()->Add(material, 0);
}



