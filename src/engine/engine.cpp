
#include "engine/engine.hpp"
#include <windows.h>
#include <engine\gpu.hpp>
#include <engine\systems\inputSystem.hpp>
#include <engine\systems\physicSystem.hpp>
#include <engine\systems\cameraSystem.hpp>
#include <engine\systems\transformSystem.hpp>
#include <engine\systems\lightSystem.hpp>
#include <engine\systems\renderSystem.hpp>

Engine::Engine() {
	_systemList.push_back(new InputSystem());
	_systemList.push_back(new PhysicSystem());
	_systemList.push_back(new CameraSystem());
	_systemList.push_back(new TransformSystem());
	_systemList.push_back(new LightSystem());
	_systemList.push_back(new RenderSystem());
	_nextGameTick = GetTickCount64();
	window = Window::instance();
}

void Engine::init()
{
	// The order of insertion determine the orden of 
	for (auto it = _systemList.begin(); it < _systemList.end(); it++) {
		(*it)->init();
	}
	GPU::clearColor(0.0f, 0.3f, 0.6f, 1.0f);
	GPU::enableCullFace();
	GPU::enableBlend();
}

void Engine::update(const float dt) {
	GPU::clearBuffer();
	for (auto it = _systemList.begin(); it < _systemList.end(); it++) {
		(*it)->update(dt);
	}
}

void Engine::mainLoop() {
	while (_gameIsRunning && window->alive()){

		const float currentFrame = glfwGetTime();
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		update(deltaTime);
		//_loops = 0;
		//while (/*GetTickCount64() > _nextGameTick &&*/ _loops < 100) {
		//	update(SKIP_TICKS);
		//	_nextGameTick += SKIP_TICKS;
		//	_loops++;
		//}
		window->frame();
	}
}