#include <engine\managers\componentManager.hpp>
#include <engine\handle\handleManager.hpp>
#include <engine\systems\transformSystem.hpp>
#include <engine\systems\cameraSystem.hpp>
#include <engine\systems\graphicSystem.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\components\cameraComponent.hpp>
#include <engine\components\graphicComponent.hpp>

Component* ComponentManager::createComponent(Handle* gameObject, TYPE componentType)
{
	Component* component;
	switch (componentType)
	{
	case TRANSFORM_COMPONENT:
		component = new TransformComponent(_GUID, gameObject);
		TransformSystem::instance()->addComponent(component->getHandle());
		break;
	case CAMERA_COMPONENT:
		component = new CameraComponent(_GUID, gameObject);
		CameraSystem::instance()->addComponent(component->getHandle());
		break;
	case GRAPHIC_COMPONENT:
		component = new GraphicComponent(_GUID, gameObject);
		GraphicSystem::instance()->addComponent(component->getHandle());
		break;
	case PHYSIC_COMPONENT:
		break;
	case LOGIC_COMPONENT:
		break;
	case INPUT_COMPONENT:
		break;
	case UI_COMPONENT:
		break;
	case AUDIO_COMPONENT:
		break;
	default:
		break;
	}
	_GUID++;
	return component;
}

