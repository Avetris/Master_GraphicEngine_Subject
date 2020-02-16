#include <engine\defaultObjects\bricks\simpleBrick.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>

SimpleBrick::SimpleBrick(uint16_t UID) : Brick(UID) {
	init();
}

SimpleBrick::SimpleBrick(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle) : Brick(UID, position, rotation, scale, angle) {
	init();
}

void SimpleBrick::init() {
	Brick::init();
	RenderComponent* renderComponent = getComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);
	renderComponent->setMaterial(MaterialManager::instance()->getMaterial("../assets/textures/bricks_albedo.png", "../assets/textures/bricks_specular.png", "../assets/textures/bricks_normal.png", 32));

}
