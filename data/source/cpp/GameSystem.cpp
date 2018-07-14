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
    case gamemode_main:
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
    have_inited = false;
}

void Scene::InitScene()
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
    if (!have_inited) {
        InitScene();
        have_inited = true;
    }

    GameMode ret_mode = System();
    Render();
    return ret_mode;
}
