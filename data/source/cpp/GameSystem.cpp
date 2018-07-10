//弾や敵の動き
//当たり判定処理
#include "../header/gamesystem.h"

class GameSystem {
private:
    static Title title;
    static MainGame maingame;
    static Pause pause;

    static GameMode mode;
    static SDL_atomic_t atm;

    static bool InitGameSystem();

public:
    GameSystem();
    static int SystemUpdate(void *data);
};

Title GameSystem::title;
MainGame GameSystem::maingame;
Pause GameSystem::pause;

GameMode GameSystem::mode;
SDL_atomic_t GameSystem::atm;

GameSystem::GameSystem()
{
}

bool GameSystem::InitGameSystem()
{
    title    = *new Title();
    maingame = *new MainGame();
    pause    = *new Pause();

    mode = gamemode_title;

    SDL_AtomicSet(&atm, 1);
    SDL_Thread *System_thread = SDL_CreateThread(SystemUpdate, "InputThread", &atm);
    if (System_thread == NULL) {
        printf("error create thread");
        return false;
    }
    return true;
}

int GameSystem::SystemUpdate(void *data)
{
    while (mode != gamemode_end) {
        switch (mode) {
        case gamemode_title:
            mode = title.System();
        case gamemode_playing:
            mode = maingame.System();
        case gamemode_pause:
            mode = pause.System();
        }
    }
}