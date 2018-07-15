
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

    player   = *new Player("data/data_3d/untitled.obj");
    enemy[0] = *new Enemy("data/data_3d/pointer.obj");
    bullet.LoadFile("data/data_3d/bullet01.obj");

    pointer = *new Object("data/data_3d/pointer.obj");
    for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
        player_bullet[i]       = *new Bullet();
        player_bullet[i].exist = false;
    }
}
void MainGame::InitScene()
{
    player.position = *new Vector3f(0, 0, 0);
    player.aimpoint = *new Vector3f(0, 0, 50);

    SDL_TimerID timer = SDL_AddTimer(5, MainGame::Timer, NULL);
    if (timer == 0) {
        printf("error timer\n");
    }
}

GameMode MainGame::System()
{
    MainGameSystemManager();

    /////////////////////////
    // 自機
    /////////////////////////
    PlayerMove();
    PlayerAttack();
    /////////////////////////
    // 敵
    /////////////////////////
    for (int i = 0; i < MAX_ENEMY; i++) {
    }
    /////////////////////////
    // 弾
    /////////////////////////
    for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
        if (player_bullet[i].exist) {
            player_bullet[i].Move();
            if (player_bullet[i].position.z > 100) {
                player_bullet[i].exist = false;
            }
        }
    }

    for (int i = 0; i < MAX_ENEMY_BULLET; i++) {
        if (enemy_bullet[i].exist) {
            enemy_bullet[i].Move();
            if (enemy_bullet[i].position.z > 100) {
                enemy_bullet[i].exist = false;
            }
        }
    }
    /////////////////////////
    // 当たり判定
    /////////////////////////
    /////////////////////////
    // ラスト
    /////////////////////////
    if (Controller_Maneger::Joystics[0].state.button[B_PAUSE])
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
    gluPerspective(30.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 150.0);
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
    // ポインタ
    /////////////////////////
    glPushMatrix();
    glTranslated(player.aimpoint.x, player.aimpoint.y, player.aimpoint.z);
    LookatPoint(player.aimpoint, player.position);
    pointer.Draw();
    glPopMatrix();
    /////////////////////////
    // 敵
    /////////////////////////

    /////////////////////////
    // 弾
    /////////////////////////

    for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
        if (player_bullet[i].exist) {
            glPushMatrix();
            glTranslated(player_bullet[i].position.x, player_bullet[i].position.y, player_bullet[i].position.z);

            glScaled(0.4, 0.4, 0.4);
            player_bullet[i].Draw();
            glPopMatrix();
        }
    }
}

Uint32 MainGame::Timer(Uint32 interval, void *pram)
{
    time++;
    return interval;
}

void MainGameSystemManager()
{
    if (true) {
    }
}

void MainGame::PlayerMove()
{

    player.aimpoint.x = player.position.x -= (Controller_Maneger::Joystics[0].state.button[B_SHIFT_BACK]) ? Controller_Maneger::Joystics[0].state.Lx_axis * 0.03 : Controller_Maneger::Joystics[0].state.Lx_axis * 0.1;
    player.aimpoint.y = player.position.y -= (Controller_Maneger::Joystics[0].state.button[B_SHIFT_BACK]) ? Controller_Maneger::Joystics[0].state.Ly_axis * 0.03 : Controller_Maneger::Joystics[0].state.Ly_axis * 0.1;

    player.aimpoint.x -= Controller_Maneger::Joystics[0].state.Rx_axis * 20;
    player.aimpoint.y -= Controller_Maneger::Joystics[0].state.Ry_axis * 20;
}

void MainGame::PlayerAttack()
{
    if (Controller_Maneger::Joystics[0].state.button[B_SHOOT_DICITION]) {
        if (player.attack_span++ % 20 == 0) {
            for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
                if (!player_bullet[i].exist) {
                    player_bullet[i]          = *new Bullet(bullet);
                    player_bullet[i].exist    = true;
                    player_bullet[i].position = player.position;
                    player_bullet[i].speed    = (player.aimpoint - player.position).normalize() * 1.5;
                    break;
                }
            }
        }
    }
}
//敵　型　移動方法　攻撃方法
void EnemyMove()
{
}