#include <engine\engine.hpp>

int main(int, char* []) {
    Engine* engine = Engine::instance();
    engine->mainLoop();
    delete[] Engine::instance();
    return 0;
}