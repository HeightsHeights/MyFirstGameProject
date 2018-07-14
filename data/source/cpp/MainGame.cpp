
#include "../header/gamesystem.h"
#include "../header/toolkit.h"
//https://www.youtube.com/watch?v=TsmE6PYazxA
typedef enum {
    ET_NULL = 0,
    ET_UFO  = 1,
} EnemyType;

typedef enum {
    ES_NULL        = 0,
    ES_Machine_Aim = 1,
} EnemyShot;

typedef enum {
    EM_NULL   = 0,
    EM_Rush   = 1,
    EM_Spiral = 2,
} EnemyMove;

unsigned int MainGame::time = 0;

MainGame::MainGame()
    : Scene()
{
    //OBJMESH mesh_player = *new OBJMESH();

    player   = *new Player("data/data_3d/untitled.obj");
    enemy[0] = *new Enemy("data/data_3d/pointer.obj");
    /*
    mesh_player.LoadFile("data/data_3d/untitled.obj");

    Player player   = *new Player(mesh_player);
    */
}
void MainGame::InitScene()
{
    player.position = *new Vector3f(0, 0, 0);
    player.aimpoint = *new Vector3f(0, 0, 30);

    SDL_TimerID timer = SDL_AddTimer(5, MainGame::Timer, NULL);
    if (timer == 0) {
        printf("error timer\n");
    }
}

GameMode MainGame::System()
{
    /////////////////////////
    // 自機
    /////////////////////////
    player.aimpoint.x = player.position.x -= (Controller_Maneger::Joystics[0].state.button_shift_back) ? Controller_Maneger::Joystics[0].state.Lx_axis * 0.03 : Controller_Maneger::Joystics[0].state.Lx_axis * 0.1;
    player.aimpoint.y = player.position.y -= (Controller_Maneger::Joystics[0].state.button_shift_back) ? Controller_Maneger::Joystics[0].state.Ly_axis * 0.03 : Controller_Maneger::Joystics[0].state.Ly_axis * 0.1;
    player.aimpoint.x -= Controller_Maneger::Joystics[0].state.Rx_axis * 30;
    player.aimpoint.y -= Controller_Maneger::Joystics[0].state.Ry_axis * 30;

    /////////////////////////
    // 敵
    /////////////////////////

    /////////////////////////
    // 弾
    /////////////////////////

    /////////////////////////
    // 当たり判定
    /////////////////////////

    /////////////////////////
    // ラスト
    /////////////////////////
    if (Controller_Maneger::Joystics[0].state.button_pause)
        return gamemode_end;
    else
        return gamemode_main;
}

void MainGame::Render()
{

    //////////////////////////
    // 初期化
    /////////////////////////
    glLoadIdentity();
    gluPerspective(30.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(0.0, 0.0, -30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    /////////////////////////
    // 自機
    /////////////////////////
    glPushMatrix();
    glTranslated(player.position.x, player.position.y, 0);
    LookatPoint(player.position, player.aimpoint);
    player.Draw();
    glPopMatrix();

    /////////////////////////
    // 敵
    /////////////////////////
    glPushMatrix();
    glTranslated(player.aimpoint.x, player.aimpoint.y, player.aimpoint.z);
    LookatPoint(player.aimpoint, player.position);
    enemy[0].Draw();
    glPopMatrix();
    /////////////////////////
    // 弾
    /////////////////////////
}

Uint32 MainGame::Timer(Uint32 interval, void *pram)
{

    time++;
    return interval;
}