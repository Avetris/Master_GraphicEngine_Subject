#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <cstdint>
#include <engine\defaultObjects\ui\scoreUIObject.hpp>
#include <engine\defaultObjects\ui\lifesUIObject.hpp>
#include <engine\defaultObjects\ui\finalUIObject.hpp>

class GameManager{
    public:
        static GameManager* instance() {
            static GameManager gameInstance;
            return &gameInstance;
        }

        void init();
        void reset();

        void hit(int score);
        void die();
        bool isPaused();
        void pause();

    private:
        GameManager() {}
        float _z = -15.0f;
        int _lifes = 3;
        int _score = 0;
        bool _paused = false;
        ScoreUIObject* _scoreUIObject;
        LifesUIObject* _lifesUIObject;
        FinalUIObject* _finalUIObject;

        void createUIObjects();
        void createWalls();
        void createBallAndBar();
        void createBricks();

};
#endif
