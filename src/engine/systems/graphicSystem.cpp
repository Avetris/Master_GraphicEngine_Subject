#include <engine/systems/graphicSystem.hpp>
#include <engine/components/graphicComponent.hpp>
#include <engine\handle\handleManager.hpp>

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
