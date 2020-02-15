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