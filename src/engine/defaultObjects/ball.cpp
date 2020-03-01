#include <engine\defaultObjects\ball.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>
#include <engine\components\physicComponent.hpp>
#include <engine\defaultObjects\bricks\brick.hpp>
#include <engine\defaultObjects\gameManager.hpp>

Ball::Ball(uint16_t UID) : Sphere(UID) {
	init();
}

Ball::Ball(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : Sphere(UID, position, rotation, scale, angle) {
	init();
}


bool Ball::isLaunched() {
	return _launched;
}

void Ball::setLaunched(bool launched) {
	_launched = launched;
}

void Ball::onCollision(GameObject* collisionGameObject)
{
	if (collisionGameObject->isTag(Brick::TAG())) {
		static_cast<Brick*>(collisionGameObject)->hit();
	}else if (collisionGameObject->isTag("gameEnd")) {
		GameManager::instance()->die();
	}
}

void Ball::init() {
	Sphere::init();
	setTag(TAG());
	addComponent<SpotLightComponent>(ComponentType::LIGHT_COMPONENT);
	PhysicComponent* physicComponent = addComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	physicComponent->setCollider(ColliderType::CIRCLE);
	physicComponent->setRigid(false);
	SphereComponent* sphereComponent = getComponent<SphereComponent>(ComponentType::RENDER_COMPONENT);
	sphereComponent->setShader(Engine::instance()->getSystem<RenderSystem>()->getShader(GenericShaderType::LIGHT));
	sphereComponent->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Ball::reset()
{
	setLaunched(false);
	PhysicComponent* physicComponent = getComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	if (physicComponent) {
		physicComponent->setVelocity(glm::vec3(0.0f), 0.0f);
	}
	resetPosition();
}
