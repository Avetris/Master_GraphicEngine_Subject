#include <engine/systems/renderSystem.hpp>
#include <engine/components/renderComponent.hpp>
#include <iostream>

RenderSystem::RenderSystem(){}

void RenderSystem::init() {
}

void RenderSystem::update(const float dt) {
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			(*it)->update(dt);
		}
	}
}



Shader* RenderSystem::getShader(GenericShaderType type)
{
	Shader* shader = nullptr;
	auto p = _defaultShaders.find(type);
	if (p != _defaultShaders.end()) {
		shader = p->second;
	}
	else {
		std::string vertexShader = SHADER_PATH;
		std::string fragmentShader = SHADER_PATH;
		switch (type)
		{
		case GenericShaderType::BLINN:
			vertexShader.append("blinn.vs");
			fragmentShader.append("blinn.fs");
			break;
		case GenericShaderType::BLEND:
			vertexShader.append("blend.vs");
			fragmentShader.append("blend.fs");
			break;
		case GenericShaderType::LIGHT:
			vertexShader.append("light.vs");
			fragmentShader.append("light.fs");
			break;
		case GenericShaderType::SHADOW:
			vertexShader.append("depth.vs");
			fragmentShader.append("depth.fs");
			break;
		}
		shader = new Shader(vertexShader.c_str(), fragmentShader.c_str());
		_defaultShaders[type] = shader;
	}
	return shader;
}

void RenderSystem::addComponent(Component* component) {
	System::addComponent(component);
	_reloadShaders = true;
}

void RenderSystem::removeComponent(Component* component) {
	System::removeComponent(component);
	_reloadShaders = true;
}

void RenderSystem::setReloadShaders() {
	_reloadShaders = true;
}

std::vector<Shader*> RenderSystem::getUsedShaders() {
	if (_reloadShaders) {
		_usedShaders.clear();
		for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
			if ((*it)->isEnable()) {
				RenderComponent* component = static_cast<RenderComponent*>(*it);
				if (std::count(_usedShaders.begin(), _usedShaders.end(), component->getShader())) {
					_usedShaders.push_back(component->getShader());
				}
			}
		}
	}
	return _usedShaders;
}
