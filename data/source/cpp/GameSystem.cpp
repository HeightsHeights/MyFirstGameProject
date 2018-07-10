//弾や敵の動き
//当たり判定処理
#include "../header/gamesystem.h"

Title GameSystem::title;
MainGame GameSystem::maingame;
Pause GameSystem::pause;

GameMode GameSystem::mode;

GameSystem::GameSystem()
{
}

bool GameSystem::InitGameSystem()
{
    title    = *new Title();
    maingame = *new MainGame();
    pause    = *new Pause();

    mode = gamemode_title;

    return true;
}

int GameSystem::SystemUpdate()
{
    switch (mode) {
    case gamemode_title:
        mode = title.Update();
        break;
    case gamemode_playing:
        mode = maingame.Update();
        break;
    case gamemode_pause:
        mode = pause.Update();
        break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
{
}

void Scene::Render()
{
}
GameMode Scene::System()
{
}

GameMode Scene::Update()
{
    GameMode ret_mode = System();
    Render();
    return ret_mode;
}
