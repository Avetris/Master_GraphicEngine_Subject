#include "engine/engine.hpp"
#include <windows.h>
#include <engine\gpu.hpp>
#include <engine\systems\graphicSystem.hpp>
#include <engine\systems\cameraSystem.hpp>
#include <engine\systems\transformSystem.hpp>
#include <iostream>

Engine::Engine() {
	init();
}

void Engine::init()
{
	// The order of insertion determine the orden of 
	_systemList.push_back(new TransformSystem());
	_systemList.push_back(new CameraSystem());
	_systemList.push_back(new GraphicSystem());
	std::cout << "SALE" << std::endl;
	_nextGameTick = GetTickCount64();
	window = Window::instance();
	std::cout << _systemList.size() << std::endl;
	for (auto it = _systemList.begin(); it < _systemList.end(); it++) {
		(*it)->init();
	}
}

void Engine::update(const float dt) {
	GPU::enableCullFace();
	for (auto it = _systemList.begin(); it < _systemList.end(); it++) {
		//(*it)->update(dt);
	}
}

void Engine::mainLoop() {
	while (_gameIsRunning && window->alive()){
		_loops = 0;
		while (GetTickCount64() > _nextGameTick && _loops < MAX_FRAMESKIP) {
			update((_nextGameTick + SKIP_TICKS) - _nextGameTick);
			_nextGameTick += SKIP_TICKS;
			_loops++;
		}
		window->frame();
	}
}

template<class T>
bool Engine::getSystem(T* system) const {
	for (auto system : _systemList) {
		if (dynamic_cast<const T*>(system) != nullptr) {
			T = system;
			return true;
		}
	}
	return false;
}