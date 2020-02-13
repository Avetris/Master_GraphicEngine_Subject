#include <engine/systems/graphicSystem.hpp>
#include <engine/components/graphicComponent.hpp>
#include <engine\shader.hpp>

GraphicSystem::GraphicSystem() {}

void GraphicSystem::init() {

}

void GraphicSystem::update(const float dt) {
	GraphicComponent* component;
	GPU::enableCullFace();
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {

		}
	}
}

Shader* GraphicSystem::getShader(GENERIC_SHADER_TYPE type)
{
	Shader* shader = nullptr;
	auto p = _defaultShaders.find(type);
	if (p != _defaultShaders.end()) {
		shader = p->second;
	}
	else {
		Shader* s;
		std::string vertexShader = SHADER_PATH;
		std::string fragmentShader = SHADER_PATH;
		switch (type)
		{
			case BLINN: 
				vertexShader.append("binn.vs");
				fragmentShader.append("binn.fs");
				break;
			case BLEND:
				vertexShader.append("blend.vs");
				fragmentShader.append("blend.fs");
				break;
			case LIGHT:
				vertexShader.append("light.vs");
				fragmentShader.append("light.fs");
				break;
			case SHADOW:
				vertexShader.append("depth.vs");
				fragmentShader.append("depth.fs");
				break;
		}
		s = new Shader(vertexShader.c_str(), fragmentShader.c_str());
		_defaultShaders[type] = shader;
	}
	return shader;
}