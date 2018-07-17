#include "../header/gamesystem.h"
#include "../header/toolkit.h"

#define TIME 700
//https://www.youtube.com/watch?v=TsmE6PYazxA

unsigned int MainGame::time = 0;

MainGame::MainGame()
    : Scene()
{
    SetEnemyInfo();

    player = *new Player("data/data_3d/player.obj");
    player.collider.spheres.push_back(Sphere(Vector3f(0, 0, 0), 1));

    m_bullet.LoadFile("data/data_3d/bullet01.obj");
    m_enemy[ET_Sphere].LoadFile("data/data_3d/ufo01.obj");
    m_enemy[ET_Ufo].LoadFile("data/data_3d/boss.obj");

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
    time = TIME;
}

GameMode MainGame::System()
{

    MainGameSystemManager();
    if (time <= 30) {
        goto startyet;
    }
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
    for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
        if (player_bullet[i].exist) {
            for (int j = 0; j < MAX_ENEMY; j++) {
                if (enemy[j].exist) {
                    if (player_bullet[i].collider.isCollision(enemy[j].collider)) {
                        player_bullet[i].exist = false;
                        enemy[j].exist         = false;
                    }
                }
            }
        }
    }
    for (int i = 0; i < MAX_ENEMY_BULLET; i++) {
        if (enemy_bullet[i].exist) {
            if (enemy_bullet[i].collider.isCollision(player.collider)) {
                enemy_bullet[i].exist = false;
                printf("hit\n");
            }
        }
    }

startyet:

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
            switch (enemy[i].enemy_direction_type) {
            case EDT_Forward:
                LookatVector(Vector3f(0, 0, -1));
                break;
            case EDT_toPlayer:
                LookatPoint(enemy[i].position, player.position);
                break;
            case EDT_Custom:
                LookatVector(enemy[i].forward);
                break;
            }
            switch (enemy[i].enemy_type) {
            case ET_Ufo:
                glScaled(3.5, 3.5, 3.5);
                break;
            }
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
            glScaled(0.5, 0.5, 0.5);
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

    for (int i = 0; i < MAX_ENEMY; i++) {
        if (enemy[i].exist) {
            enemy[i].living_time = time - enemy[i].spawn_time;
            enemy[i].attack_span_count++;
            enemy[i].attack_span_a_span_to_a_span_count++;
        }
    }
    static int p = 0;
searchagain:
    if (p < enemyinfo.size()) {
        if (time >= enemyinfo[p].spawn_time) {
            for (int i = 0; i < MAX_ENEMY; i++) {
                if (!enemy[i].exist) {
                    enemy[i] = *new Enemy(m_enemy[enemyinfo[p].enemy_type]);
                    enemy[i].Set(enemyinfo[p]);
                    p++;
                    goto searchagain;
                }
            }
        }
    }
}

void MainGame::PlayerMove()
{

    player.collider.spheres[0].center.x = player.aimpoint.x = player.position.x -= (Controller_Maneger::Joystics[0].state.button[B_SHIFT_BACK]) ? Controller_Maneger::Joystics[0].state.Lx_axis * 0.03 : Controller_Maneger::Joystics[0].state.Lx_axis * 0.1;
    player.collider.spheres[0].center.y = player.aimpoint.y = player.position.y -= (Controller_Maneger::Joystics[0].state.button[B_SHIFT_BACK]) ? Controller_Maneger::Joystics[0].state.Ly_axis * 0.03 : Controller_Maneger::Joystics[0].state.Ly_axis * 0.1;

    if (player.position.x > 12) {
        player.collider.spheres[0].center.x = player.aimpoint.x = player.position.x = 12;
    }
    if (player.position.x < -12) {
        player.collider.spheres[0].center.x = player.aimpoint.x = player.position.x = -12;
    }
    if (player.position.y > 8) {
        player.collider.spheres[0].center.y = player.aimpoint.y = player.position.y = 8;
    }
    if (player.position.y < -8) {
        player.collider.spheres[0].center.y = player.aimpoint.y = player.position.y = -8;
    }

    player.aimpoint.x -= Controller_Maneger::Joystics[0].state.Rx_axis * 15;
    player.aimpoint.y -= Controller_Maneger::Joystics[0].state.Ry_axis * 15;
}

void MainGame::PlayerAttack()
{
    if (Controller_Maneger::Joystics[0].state.button[B_SHOOT_DICITION]) {
        if (player.attack_span++ % 20 == 0) {
            for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
                if (!player_bullet[i].exist) {
                    player_bullet[i] = *new Bullet(m_bullet);
                    player_bullet[i].Set(player.position, (player.aimpoint - player.position).normalize() * 1.5, *new Vector3f(0, 0, 0), BT_Player);
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
            enemy[i].Move(player);
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

            //ディレイ確認
            switch (enemy[i].enemy_shot_start_type) {
            case ESST_Delay:
                if (enemy[i].living_time < enemy[i].attack_delay) {
                    continue;
                }
                break;
            case ESST_WaitUntilStop:
                if (enemy[i].enemy_move_type == EMT_Ufo && enemy[i].subargument[1] > 0) {
                    break;
                }
                if (enemy[i].enemy_move_type == EMT_Boss && enemy[i].subargument[2] > 0) {
                    break;
                }
                if ((enemy[i].point - enemy[i].position).magnitude() > enemy[i].enemy_speed_magnitude) {
                    continue;
                }
                break;
            }

            if (enemy[i].attack_times <= 0) {
                continue;
            }

            //スパン確認
            if (enemy[i].attack_span_a_span_to_a_span <= enemy[i].attack_span_a_span_to_a_span_count && enemy[i].attack_span <= enemy[i].attack_span_count) {
                //攻撃できるか
                enemy[i].attack_span_a_span_to_a_span_count = 0;
                //攻撃回数超えたらちょっとまつ
                if (++enemy[i].attack_times_in_a_span_count >= enemy[i].attack_times_in_a_span) {
                    enemy[i].attack_times--;
                    enemy[i].attack_span_count            = 0;
                    enemy[i].attack_times_in_a_span_count = 0;
                }
            } else {
                continue;
            }

            //攻撃
            ////////////////////////////////////////////////////////
            // way弾
            ////////////////////////////////////////////////////////
            if (enemy[i].enemy_shot_type == EST_Forward || enemy[i].enemy_shot_type == EST_Machine_Aim || enemy[i].enemy_shot_type == EST_Follow_Enemy_Direction) {
                Vector3f v;
                switch (enemy[i].enemy_shot_type) {
                case EST_Forward:
                    v = *new Vector3f(0, 0, -1);
                    break;
                case EST_Machine_Aim:
                    v = (player.position - enemy[i].position).normalize();
                    break;
                case EST_Follow_Enemy_Direction:
                    v = enemy[i].forward;
                    break;
                }

                Vector3f rotation_axis = getNewUPVector(v);

                v = v.Rotate(rotation_axis, (enemy[i].number_of_bullet - 1) / 2.0f * enemy[i].interval_angle);

                for (int k = 0; k < enemy[i].number_of_bullet; k++) {
                    for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                        if (!enemy_bullet[j].exist) {
                            enemy_bullet[j] = *new Bullet(m_bullet);
                            enemy_bullet[j].Set(enemy[i].position, v * enemy[i].shot_speed, v * enemy[i].shot_accel, BT_Enemy);

                            v = v.Rotate(rotation_axis, -enemy[i].interval_angle);
                            break;
                        }
                    }
                }
                ////////////////////////////////////////////////////////
                //　ばらまき（円）
                ////////////////////////////////////////////////////////
            } else if (enemy[i].enemy_shot_type == EST_Scattering_Bullets_Forward || enemy[i].enemy_shot_type == EST_Scattering_Bullets_Machine_Aim || enemy[i].enemy_shot_type == EST_Scattering_Bullets_Follow_Enemy_Direction) {
                Vector3f forward;
                switch (enemy[i].enemy_shot_type) {
                case EST_Scattering_Bullets_Forward:
                    forward = *new Vector3f(0, 0, -1);
                    break;
                case EST_Scattering_Bullets_Machine_Aim:
                    forward = (player.position - enemy[i].position).normalize();
                    break;
                case EST_Scattering_Bullets_Follow_Enemy_Direction:
                    forward = enemy[i].forward;
                    break;
                }
                ////////////////////////////////////////////////////////
                //
                ////////////////////////////////////////////////////////

                Vector3f side = getNewSideVector(forward);

                for (int k = 0; k < enemy[i].number_of_bullet; k++) {
                    for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                        if (!enemy_bullet[j].exist) {
                            enemy_bullet[j] = *new Bullet(m_bullet);
                            enemy_bullet[j].Set(enemy[i].position, forward * enemy[i].shot_speed, forward * enemy[i].shot_accel, BT_Enemy);
                            break;
                        }
                    }
                }

                for (int l = 0; l < (int)enemy[i].shoot_width; l++) {
                    Vector3f v = forward.Rotate(side, enemy[i].interval_angle * (l + 1));

                    for (int k = 0; k < enemy[i].number_of_bullet; k++) {
                        for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                            if (!enemy_bullet[j].exist) {
                                enemy_bullet[j] = *new Bullet(m_bullet);
                                enemy_bullet[j].Set(enemy[i].position, v * enemy[i].shot_speed, v * enemy[i].shot_accel, BT_Enemy);

                                v = v.Rotate(forward, 360 / enemy[i].number_of_bullet);
                                break;
                            }
                        }
                    }
                }
            } else if (enemy[i].enemy_shot_type == EST_Random_Scattering) {

                for (int k = 0; k < enemy[i].number_of_bullet; k++) {
                    Vector3f v;
                    do {
                        v = Vector3f(RandBetween(0, 1000) - 500, RandBetween(0, 1000) - 500, -RandBetween(600, 1000)).normalize();
                    } while (v.magnitude_second_power() == 0);
                    for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                        if (!enemy_bullet[j].exist) {
                            enemy_bullet[j] = *new Bullet(m_bullet);
                            enemy_bullet[j].Set(enemy[i].position, v * ((RandBetween(3, 20) / (20 / enemy[i].shot_speed))), v * enemy[i].shot_accel, BT_Enemy);
                            break;
                        }
                    }
                }
            } else if (enemy[i].enemy_shot_type == EST_Boss) {
                enemy[i].attack_times = 1;
                for (int k = 0; k < 3; k++) {
                    Vector3f v = (enemy[i].shot_from_point[k] - enemy[i].position).normalize();
                    for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                        if (!enemy_bullet[j].exist) {
                            enemy_bullet[j] = *new Bullet(m_bullet);
                            enemy_bullet[j].Set(enemy[i].shot_from_point[k], v * enemy[i].shot_speed, v * enemy[i].shot_accel, BT_Enemy);
                            break;
                        }
                    }
                }

                for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                    if (!enemy_bullet[j].exist) {
                        Vector3f v      = *new Vector3f(0, 0, -1);
                        enemy_bullet[j] = *new Bullet(m_bullet);
                        enemy_bullet[j].Set(enemy[i].position, v * enemy[i].shot_speed * 4, v * enemy[i].shot_accel, BT_Enemy);
                        break;
                    }
                }
            }
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