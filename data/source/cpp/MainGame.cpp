#include "../header/gamesystem.h"
#include "../header/toolkit.h"
//https://www.youtube.com/watch?v=TsmE6PYazxA

unsigned int MainGame::time = 0;

MainGame::MainGame()
    : Scene()
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //スポーン時間　デスポーン時間　敵の形　敵の移動方法　敵の移動方向　敵の向き設定　敵の攻撃方法　敵の攻撃開始の設定　敵のHP　敵の攻撃開始時間　敵の攻撃スパン　敵のおおまかな攻撃回数　敵の初期位置　敵の初期向き　敵のスピード 敵の加速度　敵の目的位置
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    EnemyInfo ei[] = {
        {
            10,
            300,
            ET_Sphere,
            EMT_StayPoint,
            EMD_toRight,
            EDT_Forward,
            EST_Machine_Aim,
            ESST_WaitUntilStop,
            3,
            0,
            300,
            10,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f(0, 0, 0),
        },
        {
            20,
            300,
            ET_Sphere,
            EMT_StayPoint,
            EMD_toRight,
            EDT_Forward,
            EST_Machine_Aim,
            ESST_WaitUntilStop,
            3,
            0,
            300,
            10,
            Vector3f(10, 0, 0),
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f(0, 0, 0),
        },
        {
            30,
            300,
            ET_Sphere,
            EMT_StayPoint,
            EMD_toRight,
            EDT_Forward,
            EST_Machine_Aim,
            ESST_WaitUntilStop,
            3,
            0,
            300,
            10,
            Vector3f(-10, 0, 0),
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f(0, 0, 0),
        },
    };

    for (int i = 0; i < sizeof(ei) / sizeof(EnemyInfo); i++) {
        enemyinfo.push_back(ei[i]);
    }

    player = *new Player("data/data_3d/untitled.obj");

    m_bullet.LoadFile("data/data_3d/bullet01.obj");
    m_enemy[ET_Sphere].LoadFile("data/data_3d/ufo01.obj");
    //m_enemy[ET_Plane].LoadFile("data/data_3d/ufo plane free.obj");
    //m_enemy[ET_Plane].LoadFile("data/data_3d/ufo plane free.obj");
    m_enemy[ET_Plane].LoadFile("data/data_3d/ufo plane free.obj");

    pointer = *new Object("data/data_3d/pointer.obj");

    for (int i = 0; i < MAX_ENEMY; i++) {
        enemy[i]       = *new Enemy();
        enemy[i].exist = false;
    }
    for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
        player_bullet[i]       = *new Bullet();
        player_bullet[i].exist = false;
    }
    for (int i = 0; i < MAX_ENEMY_BULLET; i++) {
        enemy_bullet[i]       = *new Bullet();
        enemy_bullet[i].exist = false;
    }
}
void MainGame::InitScene()
{
    player.position = *new Vector3f(0, 0, 0);
    player.aimpoint = *new Vector3f(0, 0, 100);

    SDL_TimerID timer = SDL_AddTimer(100, MainGame::Timer, NULL);
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
    EnemyMove();
    EnemyAttack();
    /////////////////////////
    // 弾
    /////////////////////////
    BulletMove();
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
    TranslateVector(player.position);
    LookatPoint(player.position, player.aimpoint);
    player.Draw();
    glPopMatrix();
    /////////////////////////
    // ポインタ
    /////////////////////////
    glPushMatrix();
    TranslateVector(player.aimpoint);
    LookatPoint(player.aimpoint, player.position);
    pointer.Draw();
    glPopMatrix();
    /////////////////////////
    // 敵
    /////////////////////////

    for (int i = 0; i < MAX_ENEMY; i++) {
        if (enemy[i].exist) {
            glPushMatrix();
            TranslateVector(enemy[i].position);
            enemy[i].Draw();
            glPopMatrix();
        }
    }

    /////////////////////////
    // 弾
    /////////////////////////

    for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
        if (player_bullet[i].exist) {
            glPushMatrix();
            TranslateVector(player_bullet[i].position);
            glScaled(0.4, 0.4, 0.4);
            player_bullet[i].Draw();
            glPopMatrix();
        }
    }

    for (int i = 0; i < MAX_ENEMY_BULLET; i++) {
        if (enemy_bullet[i].exist) {
            glPushMatrix();
            TranslateVector(enemy_bullet[i].position);
            enemy_bullet[i].Draw();
            glPopMatrix();
        }
    }
}

Uint32 MainGame::Timer(Uint32 interval, void *pram)
{
    time++;
    return interval;
}

void MainGame::MainGameSystemManager()
{
    static int p = 0;

searchagain:
    if (time >= enemyinfo[p].spawn_time) {
        for (int i = 0; i < MAX_ENEMY; i++) {
            if (!enemy[i].exist) {
                enemy[i] = *new Enemy(m_enemy[enemyinfo[p].enemy_type]);
                enemy[i].Set(*new Vector3f(0, 0, 100), *new Vector3f(0, 0, -0.1f), *new Vector3f(0, 0, 0));
                if (p + 1 < enemyinfo.size()) {
                    p++;
                }
                goto searchagain;
            }
        }
    }
}

void MainGame::PlayerMove()
{

    player.aimpoint.x = player.position.x -= (Controller_Maneger::Joystics[0].state.button[B_SHIFT_BACK]) ? Controller_Maneger::Joystics[0].state.Lx_axis * 0.03 : Controller_Maneger::Joystics[0].state.Lx_axis * 0.1;
    player.aimpoint.y = player.position.y -= (Controller_Maneger::Joystics[0].state.button[B_SHIFT_BACK]) ? Controller_Maneger::Joystics[0].state.Ly_axis * 0.03 : Controller_Maneger::Joystics[0].state.Ly_axis * 0.1;

    player.aimpoint.x -= Controller_Maneger::Joystics[0].state.Rx_axis * 10;
    player.aimpoint.y -= Controller_Maneger::Joystics[0].state.Ry_axis * 10;
}

void MainGame::PlayerAttack()
{
    if (Controller_Maneger::Joystics[0].state.button[B_SHOOT_DICITION]) {
        if (player.attack_span++ % 20 == 0) {
            for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
                if (!player_bullet[i].exist) {
                    player_bullet[i] = *new Bullet(m_bullet);
                    player_bullet[i].Set(player.position, (player.aimpoint - player.position).normalize() * 1.5, *new Vector3f(0, 0, 0));
                    break;
                }
            }
        }
    }
}

void MainGame::EnemyMove()
{
    for (int i = 0; i < MAX_ENEMY; i++) {
        if (enemy[i].exist) {
            enemy[i].Move();
            if (enemy[i].position.z > 100) {
                enemy[i].exist = false;
            }
        }
    }
}

void MainGame::EnemyAttack()
{
    for (int i = 0; i < MAX_ENEMY; i++) {
        if (enemy[i].exist) {
        }
    }
}

void MainGame::BulletMove()
{
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
}