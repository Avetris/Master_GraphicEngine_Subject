#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

class GameObject;

#include <cstdint>
#include <glm/glm.hpp>
#include <engine\components\component.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\cameraComponent.hpp>
#include <engine\components\graphicComponent.hpp>
#include <engine\components\geometryComponent\quadComponent.hpp>
#include <engine\components\geometryComponent\cubeComponent.hpp>
#include <engine\components\geometryComponent\sphereComponent.hpp>
#include <engine\components\geometryComponent\teapotComponent.hpp>
#include <engine\systems\transformSystem.hpp>
#include <engine\systems\cameraSystem.hpp>
#include <engine\systems\graphicSystem.hpp>
#include <engine\systems\renderSystem.hpp>
#include <engine\engine.hpp>

const size_t NUMBER_COMPONENTS = 9;
const enum TYPE {
    NON_COMPONENT = -1,
    INPUT_COMPONENT = 0,
    TRANSFORM_COMPONENT = 1,
    PHYSIC_COMPONENT = 2,
    LOGIC_COMPONENT = 3,
    CAMERA_COMPONENT = 4,
    GRAPHIC_COMPONENT = 5,
    GEOMETRY_COMPONENT = 6,
    UI_COMPONENT = 7,
    AUDIO_COMPONENT = 8
};

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
	else if (std::is_same<Component, GraphicComponent>::value) {
		component = (Component*) new GraphicComponent(_GUID, gameObject);
		Engine::instance()->getSystem<GraphicSystem>()->addComponent(component);
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
	_GUID++;
	return component;
}
#endif
