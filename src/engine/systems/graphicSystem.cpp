#include <engine/systems/graphicSystem.hpp>
#include <engine/components/graphicComponent.hpp>
#include <engine\handle\handleManager.hpp>
#include <engine\shader.hpp>

GraphicSystem::GraphicSystem() {}

void GraphicSystem::init() {

}

void GraphicSystem::update(const float dt) {
	GraphicComponent* component;
	if (_positionRefresh) {
		checkObjectsToRender();
	}
	GPU::enableCullFace();
	for (auto it = _objectsToRender.begin(); it < _objectsToRender.end(); it++) {
		HandleManager::instance()->GetAs(*it, component);
		if (component != nullptr && component->isEnable()) {

		}
	}
}

Handle* GraphicSystem::getShader(GENERIC_SHADER_TYPE type) const
{
	Handle* shader = nullptr;
	auto p = _defaultShaders.find(type);
	if (p != _defaultShaders.end()) {
		HandleManager::instance()->GetAs(p->second, shader);
	}
	else {
		Shader* s;
		switch (type)
		{
			case BLINN:
			s = new Shader(SHADER_PATH + "binn.vs", SHADER_PATH + "binn.fs");
			break;
		}

		if (s != nullptr) {
			shader = HandleManager::instance()->Add(&s, 0);
			std::pair<GENERIC_SHADER_TYPE, Handle*> r(type, shader);
			_defaultShaders.insert(std::pair<GENERIC_SHADER_TYPE, Handle*>(type, shader));
		}
	}
	return shader;
}

void GraphicSystem::positionRefresh()
{
	_positionRefresh = true;
}

void GraphicSystem::checkObjectsToRender()
{
	_objectsToRender.clear();
	GraphicComponent* component;

	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		HandleManager::instance()->GetAs(*it, component);
		if (component != nullptr && component->isEnable()) {

		}
	}
}

//bool GraphicSystem::isBeingShown() {
//	return true;
//}
