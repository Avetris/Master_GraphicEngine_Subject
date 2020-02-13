#include <engine/systems/renderSystem.hpp>
#include <engine/components/renderComponent.hpp>

RenderSystem::RenderSystem(){}

void RenderSystem::init() {

}

void RenderSystem::update(const float dt) {
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			RenderComponent* component = static_cast<RenderComponent*>(*it);
			component->render();
		}
	}
}