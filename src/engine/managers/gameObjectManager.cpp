#include <engine\managers\gameObjectManager.hpp>
#include <engine\handle\handleManager.hpp>

template<typename GameObject>
GameObject* GameObjectManager::createGameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	GameObject gameObject = new GameObject(_GUID, position, rotation, scale);
	_GUID++;
	return gameObject;
}

