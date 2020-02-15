#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <cstdint>
#include <engine\systems\system.hpp>

class Window;

const int TICKS_PER_SECOND = 1000;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 10;

class Engine {
    public:
        static Engine* instance() {
            static Engine i;
            return &i;
        }
        void init();
        void update(const float dt);
        void mainLoop();

        template<typename System>
        System* getSystem() const;
    private:
        Engine();
        Window* window;
        std::vector<System*> _systemList;
        int _nextGameTick = 0;
        int _loops = 0;
        bool _gameIsRunning = true;
        float lastFrame = 0.0f;
};

template<typename System>
inline System* Engine::getSystem() const{
    System* output = nullptr;
    for (auto system : _systemList) {
        output = dynamic_cast<System*>(system);
        if (output) {
            break;
        }
    }
    return output;
}
#endif
