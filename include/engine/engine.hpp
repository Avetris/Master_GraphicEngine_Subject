#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <cstdint>
#include <engine\systems\system.hpp>
#include <engine\window.hpp>

const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

class Engine {
    public:
        static Engine* instance() {
            static Engine i;
            return &i;
        }
        void init();
        void update(const float dt);
        void mainLoop();

        template<class T>
        bool getSystem(T* system) const;
    private:
        Engine();
        Window* window;
        std::vector<System*> _systemList;
        int _nextGameTick;
        int _loops = 0;
        bool _gameIsRunning = true;
};

#endif
