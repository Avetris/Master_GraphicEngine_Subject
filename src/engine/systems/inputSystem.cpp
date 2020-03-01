#include <engine/systems/inputSystem.hpp>
#include <engine\components\inputComponent.hpp>
#include <engine\defaultObjects\gameManager.hpp>

class Window;

InputSystem::InputSystem(){}

void InputSystem::init() {
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {		
		(*it)->init();
	}
}

void InputSystem::update(const float dt) {
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			if (!GameManager::instance()->isPaused()) {
				(*it)->update(dt);
			}
			else {				
				if (static_cast<CameraInputComponent*>(*it)) {
					(*it)->update(dt);
				}
			}
		}
	}	
}

void InputSystem::keyPressed(GPU::KeyId key, GPU::KeyActions action)
{
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			InputComponent* component = static_cast<InputComponent*>(*it);
			switch (action)
			{
			case GPU::KeyActions::RELEASE:
				component->onKeyDown(key);
				break;
			case GPU::KeyActions::PRESS:
				component->onKeyUp(key);
				break;
			case GPU::KeyActions::REPEAT:
				component->onKeyRepeat(key);
				break;
			default:
				break;
			}
		}
	}
}

void InputSystem::mouseMoved(float x, float y)
{
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			InputComponent* component = static_cast<InputComponent*>(*it);
			component->onMouseMoved(x, y);
		}
	}
}

void InputSystem::scrollMoved(float x, float y)
{
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			InputComponent* component = static_cast<InputComponent*>(*it);
			component->onScrollMoved(x, y);
		}
	}
}
