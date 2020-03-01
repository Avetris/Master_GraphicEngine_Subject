#include <engine/systems/lightSystem.hpp>
#include <engine\engine.hpp>
#include <engine\window.hpp>
#include <engine\shader.hpp>
#include <engine\systems\renderSystem.hpp>
#include <engine\components\lightComponent\spotLightComponent.hpp>
#include <engine\components\lightComponent\pointLightComponent.hpp>
#include <engine\components\lightComponent\directionalLightComponent.hpp>

LightSystem::LightSystem(){}

void LightSystem::init() {
	_shadowFBO = new ShadowFBO(_shadowNear, _shadowFar, Engine::instance()->getSystem<RenderSystem>()->getShader(GenericShaderType::SHADOW));
}

void LightSystem::update(const float dt) {
	_numberShadows = 0;
	_numDirecLights = 0;
	_numSpotLights = 0;
	_numPointLights = 0;
	_numShadersChecked = false;
	if (_useShadows) {
		_lightSpaceMatrix.clear();
		_shadowFBO->render();
		Shader* depthShader = _shadowFBO->getShadowShader();
		depthShader->use();
		for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
			if ((*it)->isEnable()) {
				LightComponent* component = static_cast<LightComponent*>(*it);
				glm::mat4 lightSpaceMatrix = component->getSpaceMatrix(_shadowNear, _shadowFar);
				_lightSpaceMatrix.push_back(lightSpaceMatrix);
				depthShader->set("lightSpaceMatrix", lightSpaceMatrix);
				Engine::instance()->getSystem<RenderSystem>()->renderForShadow(depthShader);
			}
		}
	}	
}

void LightSystem::renderLights(Shader* shader) {	
	GPU::changeViewPort(Window::instance()->getWidth(), Window::instance()->getHeight());
	for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
		if ((*it)->isEnable()) {
			LightComponent* component = static_cast<LightComponent*>(*it);
			updateIndex(component);
			component->use(shader);
		}
	}
	shader->set("numberOfShadows", _numberShadows);
	shader->set("numDirectLight", _numDirecLights);
	shader->set("numPointLight", _numPointLights);
	shader->set("numSpotLight", _numSpotLights);
	_numShadersChecked = true;
	if (_useShadows) {
		size_t index = 0;
		for (auto it = _lightSpaceMatrix.begin(); it < _lightSpaceMatrix.end(); it++) {
			shader->set(("lightSpaceMatrix[" + std::to_string(index) + "]").c_str(), *it);
			index++;
		}
		_shadowFBO->renderTexture(shader);
	}
}

void LightSystem::updateIndex(LightComponent* component) {
	if (!_numShadersChecked) {
		if (_useShadows) {
			_numberShadows++;
		}
		if (dynamic_cast<SpotLightComponent*>(component)) {
			component->setIndex(_numSpotLights);
			_numSpotLights++;
		}
		else if (dynamic_cast<PointLightComponent*>(component)) {
			component->setIndex(_numPointLights);
			_numPointLights++;
		}
		else if (dynamic_cast<DirectionalLightComponent*>(component)) {
			component->setIndex(_numDirecLights);
			_numDirecLights++;
		}
	}
}

void LightSystem::setUseShadows(bool useShadows)
{
	_useShadows = useShadows;
}

void LightSystem::setShadowDistances(float shadowNear, float shadowFar)
{
	_shadowNear = shadowNear;
	_shadowFar = shadowFar;

	delete _shadowFBO;
	_shadowFBO = new ShadowFBO(_shadowNear, _shadowFar, Engine::instance()->getSystem<RenderSystem>()->getShader(GenericShaderType::SHADOW));
}
