#include <engine/systems/transformSystem.hpp>
#include <engine/components/transformComponent.hpp>
#include <engine\handle\handleManager.hpp>

TransformSystem::TransformSystem(){}

void TransformSystem::init() {

}

void TransformSystem::update(const float dt) {
	TransformComponent* component;
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		HandleManager::instance()->GetAs(*it, component);
		if (component != nullptr && component->isEnable() && component->modelNeedsToUpdate()) {
			component->updateModel(glm::mat4(1.0f));
		}
	}
}