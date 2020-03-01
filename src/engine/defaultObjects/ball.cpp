#include <engine\defaultObjects\ball.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>
#include <engine\components\physicComponent.hpp>
#include <engine\defaultObjects\bricks\brick.hpp>

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
	if (collisionGameObject->isTag("brick")) {
		static_cast<Brick*>(collisionGameObject)->hit();
	}
}

void Ball::init() {
	Sphere::init();
	setTag("ball");
	addComponent<SpotLightComponent>(ComponentType::LIGHT_COMPONENT);
	PhysicComponent* physicComponent = addComponent<PhysicComponent>(ComponentType::PHYSIC_COMPONENT);
	physicComponent->setCollider(ColliderType::CIRCLE);
	physicComponent->setRigid(false);
	SphereComponent* sphereComponent = getComponent<SphereComponent>(ComponentType::RENDER_COMPONENT);
	sphereComponent->setShader(Engine::instance()->getSystem<RenderSystem>()->getShader(GenericShaderType::LIGHT));
	sphereComponent->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}
