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
#include <engine\components\renderComponent\modelComponent.hpp>
#include <engine\components\renderComponent\uiTextComponent.hpp>
#include <engine\components\physicComponent.hpp>
#include <engine\components\lightComponent\directionalLightComponent.hpp>
#include <engine\components\lightComponent\pointLightComponent.hpp>
#include <engine\components\lightComponent\spotLightComponent.hpp>
#include <engine\systems\inputSystem.hpp>
#include <engine\systems\transformSystem.hpp>
#include <engine\systems\cameraSystem.hpp>
#include <engine\systems\renderSystem.hpp>
#include <engine\systems\lightSystem.hpp>
#include <engine\systems\physicSystem.hpp>
#include <engine\engine.hpp>

class ComponentManager{
    public:
        static ComponentManager* instance() {
            static ComponentManager cmInstance;
            return &cmInstance;
        }

        template<typename Component>
        Component* createComponent(GameObject* gameObject);

		void removeComponent(Component* component, ComponentType componentType);
    private:
        uint16_t _GUID;
};

template<typename Component>
inline Component* ComponentManager::createComponent(GameObject* gameObject)
{
	Component* component = nullptr;
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
	else if (std::is_same<Component, InputComponent>::value) {
		component = (Component*) new InputComponent(_GUID, gameObject);
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
	else if (std::is_same<Component, ModelComponent>::value) {
		component = (Component*)  new ModelComponent(_GUID, gameObject);
		Engine::instance()->getSystem<RenderSystem>()->addComponent(component);
	}
	else if (std::is_same<Component, UITextComponent>::value) {
		RenderSystem* renderSystem = Engine::instance()->getSystem<RenderSystem>();
		component = (Component*)  new UITextComponent(_GUID, gameObject, renderSystem->getShader(GenericShaderType::UI));
		renderSystem->addComponent(component);
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
	else if (std::is_same<Component, PhysicComponent>::value) {
		component = (Component*)  new PhysicComponent(_GUID, gameObject);
		Engine::instance()->getSystem<PhysicSystem>()->addComponent(component);
	}
	_GUID++;
	return component;
}


inline void ComponentManager::removeComponent(Component* component, ComponentType componentType)
{
	switch (componentType)
	{
	case ComponentType::INPUT_COMPONENT:
		Engine::instance()->getSystem<InputSystem>()->removeComponent(component);
		break;
	case ComponentType::TRANSFORM_COMPONENT:
		Engine::instance()->getSystem<TransformSystem>()->removeComponent(component);
		break;
	case ComponentType::PHYSIC_COMPONENT:
		Engine::instance()->getSystem<PhysicSystem>()->removeComponent(component);
		break;
	/*case ComponentType::CAMERA_COMPONENT:
		Engine::instance()->getSystem<CameraSystem>()->removeComponent(component);
		break;*/
	case ComponentType::RENDER_COMPONENT:
		Engine::instance()->getSystem<RenderSystem>()->removeComponent(component);
		break;
	case ComponentType::LIGHT_COMPONENT:
		Engine::instance()->getSystem<LightSystem>()->removeComponent(component);
		break;
	}
}
#endif
