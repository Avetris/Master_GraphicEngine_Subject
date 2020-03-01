#include <engine\defaultObjects\bricks\simpleBrick.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>

SimpleBrick::SimpleBrick(uint16_t UID, uint8_t hitNeccesaries) : Brick(UID, hitNeccesaries) {
	init();
}

SimpleBrick::SimpleBrick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle, uint8_t hitNeccesaries) : Brick(UID, position, rotation, scale, angle, hitNeccesaries) {
	init();
}

void SimpleBrick::init() {
	Brick::init();

	checkHitStatus();
}

void SimpleBrick::checkHitStatus()
{
	RenderComponent* renderComponent = getComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);
	switch (_hitNeccesaries)
	{
	case 1:
		renderComponent->setMaterial(MaterialManager::instance()->getMaterial("../assets/textures/bricks_albedo.png", "../assets/textures/bricks_specular.png", "../assets/textures/bricks_normal.png", 32));
		break;
	case 2:
		renderComponent->setMaterial(MaterialManager::instance()->getMaterial("../assets/textures/brick_wall2/albedo.jpg", "../assets/textures/brick_wall2/specular.jpg", "../assets/textures/brick_wall2/normal.jpg", 32));
		break;
	case 3:
		renderComponent->setMaterial(MaterialManager::instance()->getMaterial("../assets/textures/brick_wall/albedo.jpg", "../assets/textures/brick_wall/specular.jpg", "../assets/textures/brick_wall/normal.jpg", 32));
		break;
	case 4:
		renderComponent->setMaterial(MaterialManager::instance()->getMaterial("../assets/textures/brick_wall3/albedo.jpg", "../assets/textures/brick_wall3/specular.jpg", "../assets/textures/brick_wall3/normal.jpg", 32));
		break;
	case 5:
		renderComponent->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	default:
		break;
	}
}
