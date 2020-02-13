#include <engine/systems/transformSystem.hpp>
#include <engine/components/transformComponent.hpp>

TransformSystem::TransformSystem(){}

void TransformSystem::init() {

}

void TransformSystem::update(const float dt) {
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			TransformComponent* component = static_cast<TransformComponent*>(*it);
			if (component->modelNeedsToUpdate()) {
				component->updateModel(glm::mat4(1.0f));
			}
		}
	}	
}