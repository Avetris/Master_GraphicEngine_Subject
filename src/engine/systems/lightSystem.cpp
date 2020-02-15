#include <engine/systems/lightSystem.hpp>
#include <iostream>
#include <engine\engine.hpp>
#include <engine\shader.hpp>
#include <engine\systems\renderSystem.hpp>
#include <engine\components\lightComponent\spotLightComponent.hpp>
#include <engine\components\lightComponent\pointLightComponent.hpp>
#include <engine\components\lightComponent\directionalLightComponent.hpp>

LightSystem::LightSystem(){}

void LightSystem::init() {
}

void LightSystem::update(const float dt) {
	if (_useShadows) {
		for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
			if ((*it)->isEnable()) {
				(*it)->update(dt);
			}
		}
	}
	std::vector<Shader*> shaders = Engine::instance()->getSystem<RenderSystem>()->getUsedShaders();
	int numLights = 0;
	int numDirecLights = 0;
	int numSpotLights = 0;
	int numPointLights = 0;
	bool numShadersChecked = false;
	for (auto shad = shaders.begin(); shad < shaders.end(); shad++) {
		(*shad)->use();
		for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
			if ((*it)->isEnable()) {
				(*it)->update(dt);
				if (!numShadersChecked) {
					numLights++;
					if (dynamic_cast<SpotLightComponent*>(*it)) {
						numSpotLights++;
					}
					else if (dynamic_cast<PointLightComponent*>(*it)) {
						numPointLights++;
					}
					else if (dynamic_cast<DirectionalLightComponent*>(*it)) {
						numDirecLights++;
					}
				}
			}
		}
		(*shad)->set("numberOfLights", numLights);
		(*shad)->set("numDirectLight", numDirecLights);
		(*shad)->set("numPointLight", numPointLights);
		(*shad)->set("numSpotLight", numSpotLights);
		numShadersChecked = true;
	}
}

void LightSystem::setUseShadows(bool useShadows)
{
	_useShadows = useShadows;
}
