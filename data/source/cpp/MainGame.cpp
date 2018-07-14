
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

MainGame::MainGame()
    : Scene()
{
    //player = *new Player("data/data_3d/untitled.obj");
}
void MainGame::InitScene()
{
}

GameMode MainGame::System()
{
    /////////////////////////
    // 自機
    /////////////////////////
    //point.x = location.x -= Controller_Maneger::Joystics[0].state.Lx_axis * 0.1;
    //point.y = location.y -= Controller_Maneger::Joystics[0].state.Ly_axis * 0.1;
    //point.x -= Controller_Maneger::Joystics[0].state.Rx_axis * 30;
    //point.y -= Controller_Maneger::Joystics[0].state.Ry_axis * 30;

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
        gamemode_main;
}

void MainGame::Render()
{

    // //////////////////////////
    // // 初期化
    // /////////////////////////
    // glLoadIdentity();
    // gluPerspective(30.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    // gluLookAt(0.0, 0.0, -30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // /////////////////////////
    // // 自機
    // /////////////////////////
    // glPushMatrix();
    // glTranslated(location.x, location.y, 0);
    // LookatPoint(location, point);
    // player.Draw();
    // glPopMatrix();
    // /////////////////////////
    // // 敵
    // /////////////////////////
    // glPushMatrix();
    // glTranslated(point.x, point.y, point.z);
    // LookatPoint(point, location);
    // enemy[0].Draw();
    // glPopMatrix();
    // /////////////////////////
    // // 弾
    // /////////////////////////
}
