#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

class GameObject;

#include <cstdint>
#include <glm/glm.hpp>
#include <engine\components\component.hpp>
#include <engine\components\cameraInputComponent.hpp>
#include <engine\components\cameraComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\renderComponent\quadComponent.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\renderComponent\sphereComponent.hpp>
#include <engine\components\renderComponent\teapotComponent.hpp>
#include <engine\components\lightComponent\directionalLightComponent.hpp>
#include <engine\components\lightComponent\pointLightComponent.hpp>
#include <engine\components\lightComponent\spotLightComponent.hpp>
#include <engine\systems\inputSystem.hpp>
#include <engine\systems\transformSystem.hpp>
#include <engine\systems\cameraSystem.hpp>
#include <engine\systems\renderSystem.hpp>
#include <engine\systems\lightSystem.hpp>
#include <engine\engine.hpp>

class ComponentManager{
    public:
        static ComponentManager* instance() {
            static ComponentManager cmInstance;
            return &cmInstance;
        }

        template<typename Component>
        Component* createComponent(GameObject* gameObject);


    private:
        uint16_t _GUID;
};

template<typename Component>
inline Component* ComponentManager::createComponent(GameObject* gameObject)
{
	Component* component;
	if (std::is_same<Component, TransformComponent>::value) {
		component = (Component*) new TransformComponent(_GUID, gameObject);
		Engine::instance()->getSystem<TransformSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, CameraComponent>::value) {
		component = (Component*) new CameraComponent(_GUID, gameObject);
		Engine::instance()->getSystem<CameraSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, CameraInputComponent>::value) {
		component = (Component*) new CameraInputComponent(_GUID, gameObject);
		Engine::instance()->getSystem<InputSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, QuadComponent>::value) {
		component = (Component*) new QuadComponent(_GUID, gameObject, 1.0f);
		Engine::instance()->getSystem<RenderSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, CubeComponent>::value) {
		component = (Component*) new CubeComponent(_GUID, gameObject, 1.0f);
		Engine::instance()->getSystem<RenderSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, SphereComponent>::value) {
		component = (Component*)  new SphereComponent(_GUID, gameObject, 1.0f, 25, 25);
		Engine::instance()->getSystem<RenderSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, TeapotComponent>::value) {
		component = (Component*)  new SphereComponent(_GUID, gameObject, 1.0f, 25, 25);
		Engine::instance()->getSystem<RenderSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, DirectionalLightComponent>::value) {
		component = (Component*)  new DirectionalLightComponent(_GUID, gameObject);
		Engine::instance()->getSystem<LightSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, PointLightComponent>::value) {
		component = (Component*)  new PointLightComponent(_GUID, gameObject);
		Engine::instance()->getSystem<LightSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, SpotLightComponent>::value) {
		component = (Component*)  new SpotLightComponent(_GUID, gameObject);
		Engine::instance()->getSystem<LightSystem>()->addComponent(component);
	}
	_GUID++;
	return component;
}
#endif
