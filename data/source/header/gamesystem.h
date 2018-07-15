#pragma once
#include "../header/audio.h"
#include "../header/controller.h"
#include "../header/game.h"
#include "../header/object.h"
#include "../header/ui_image.h"
#include <SDL2/SDL.h>

#define MAX_ENEMY 30
#define MAX_PLAYER_BULLET 100
#define MAX_ENEMY_BULLET 200

typedef enum {
    gamemode_title = 0,
    gamemode_main  = 1,
    gamemode_pause = 2,
    gamemode_end   = 3,
} GameMode;

/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////

class Scene {
private:
    virtual void InitScene();
    virtual void Render();
    virtual GameMode System();
    bool have_inited;

public:
    Scene();
    GameMode Update();
};

class Title : public Scene {
private:
    Player player;

    void InitScene();
    void Render();
    GameMode System();

public:
    Title();
};

class MainGame : public Scene {
private:
    Player player;
    Object pointer;
    Enemy enemy[MAX_ENEMY];
    Bullet player_bullet[MAX_PLAYER_BULLET];
    Bullet enemy_bullet[MAX_ENEMY_BULLET];

    static unsigned int time;

    OBJMESH m_bullet;
    OBJMESH m_enemy[ET_NUMBER];

    std::vector<EnemyInfo> enemyinfo;

    void Render();
    GameMode System();
    void InitScene();

    void MainGameSystemManager();

    void PlayerMove();
    void PlayerAttack();
    void EnemyMove();
    void EnemyAttack();
    void BulletMove();

    void SetEnemyInfo();

public:
    MainGame();
    static Uint32 Timer(Uint32 interval, void *pram);
};

class Pause : public Scene {
private:
    void Render();
    GameMode System();
    void InitScene();

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
