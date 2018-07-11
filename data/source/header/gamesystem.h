#pragma once
#include "../header/audio.h"
#include "../header/controller.h"
#include "../header/game.h"
#include "../header/object.h"
#include "../header/ui_image.h"
#include <SDL2/SDL.h>

typedef enum {
    gamemode_title   = 0,
    gamemode_playing = 1,
    gamemode_pause   = 2,
    gamemode_end     = 3,
} GameMode;

/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////

class Scene {
private:
    virtual void Render();
    virtual GameMode System();

public:
    Scene();
    GameMode Update();
};

class Title : public Scene {
private:
    Vector3f point;
    Vector3f front;
    Player player;
    Enemy enemy[100];
    void Render();
    GameMode System();

public:
    Title();
};

class MainGame : public Scene {
private:
    void Render();
    GameMode System();

public:
    MainGame();
};

class Pause : public Scene {
private:
    void Render();
    GameMode System();

public:
    Pause();
};
/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////

class GameSystem {
private:
    static Title title;
    static MainGame maingame;
    static Pause pause;

    static GameMode mode;

public:
    GameSystem();
    static bool InitGameSystem();
    static int SystemUpdate();
};
