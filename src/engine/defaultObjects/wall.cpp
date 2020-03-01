#include <engine\defaultObjects\wall.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>
#include <engine\components\physicComponent.hpp>
#include <engine\components\physicComponent\boxColliderComponent.hpp>
#include <engine\gameObject.hpp>

Wall::Wall(uint16_t UID) : GameObject(UID) {
	init();
}

Wall::Wall(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : GameObject(UID, position, rotation, scale, angle) {
	init();
}

void Wall::init() {
	setTag(TAG());
	addComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
	PhysicComponent* physicComponent = addComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	physicComponent->setCollider(ColliderType::BOX);
	if (getScale().x > getScale().y) {
		RenderComponent* renderComponent = addComponent<CubeComponent>(ComponentType::RENDER_COMPONENT);
		renderComponent->setColor(glm::vec3(0.8f, 0.8f, 0.8f));
	}
	else {
		ModelComponent* modelComponent = addComponent<ModelComponent>(ComponentType::RENDER_COMPONENT);
		modelComponent->setInitialParameters("../assets/models/tower/wooden watch tower2.obj");
		BoxColliderComponent* collider = static_cast<BoxColliderComponent*>(physicComponent->getCollider());
		collider->setSize(glm::vec3(3.0f, 40.0f, 3.0f));
	}

}
