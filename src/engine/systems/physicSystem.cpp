#include <engine/systems/physicSystem.hpp>
#include <engine\components\inputComponent.hpp>
#include <engine\components\physicComponent.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\gameManager.hpp>

PhysicSystem::PhysicSystem(){}

void PhysicSystem::init() {
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {		
		(*it)->init();
	}
}

void PhysicSystem::update(const float dt) {
	if (!GameManager::instance()->isPaused()) {
		for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
			if ((*it)->isEnable()) {
				(*it)->update(dt);
			}
		}
		for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
			if ((*it)->isEnable()) {
				PhysicComponent* component = static_cast<PhysicComponent*>(*it);
				for (auto it2 = it + 1; it2 < _componentList.end(); it2++) {
					if ((*it2)->isEnable()) {
						PhysicComponent* component2 = static_cast<PhysicComponent*>(*it2);
						component->checkCollisions(component2);
					}
				}
				component->applyVelocity();
			}
		}
		GameObjectManager::instance()->applyDelete();
	}
}