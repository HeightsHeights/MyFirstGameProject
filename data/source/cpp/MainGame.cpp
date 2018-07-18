#include "../header/gamesystem.h"
#include "../header/shader.h"
#include "../header/toolkit.h"

extern StaticShader shader;

#define TIME 0
//https://www.youtube.com/watch?v=TsmE6PYazxA

unsigned int MainGame::time = 0;

MainGame::MainGame()
    : Scene()
{
    judge = GJ_NULL;
    pause = false;
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

    timer = SDL_AddTimer(100, MainGame::Timer, NULL);
    if (timer == 0) {
        printf("error timer\n");
    }
    time = TIME;
}

GameMode MainGame::System()
{

    if (judge == GJ_NULL) {
        MainGameSystemManager();
    }
    if (time <= 30) {
        goto startyet;
    }
    /////////////////////////
    // 自機
    /////////////////////////

    if (judge != GJ_Lose) {
        PlayerMove();
        PlayerAttack();
    }

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

    if (pause) {
        goto startyet;
    }
    for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
        if (player_bullet[i].exist) {
            for (int j = 0; j < MAX_ENEMY; j++) {
                if (enemy[j].exist) {
                    if (player_bullet[i].collider.isCollision(enemy[j].collider)) {
                        player_bullet[i].exist = false;
                        Mix_Volume(4, MIX_MAX_VOLUME / 2);
                        Mix_PlayChannel(4, Audio_Manager::chunk[SE_Enemy_Damaged], 0);
                        if (--enemy[j].hp <= 0) {
                            enemy[j].exist = false;
                            Mix_PlayChannel(3, Audio_Manager::chunk[SE_Enemy_Killed], 0);
                            if (enemy[j].enemy_type == ET_Ufo) {
                                //クリア
                                for (int k = 0; k < MAX_ENEMY; k++) {
                                    Mix_PlayChannel(6, Audio_Manager::chunk[SE_Boss_Killed], 0);
                                    Mix_FadeOutMusic(100);
                                    Mix_PlayMusic(Audio_Manager::music[BGM_Clear], 0);
                                    judge          = GJ_Win;
                                    pause          = true;
                                    enemy[k].exist = false;
                                    SDL_RemoveTimer(timer);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (pause) {
        goto startyet;
    }
    for (int i = 0; i < MAX_ENEMY_BULLET; i++) {
        if (enemy_bullet[i].exist) {
            if (enemy_bullet[i].collider.isCollision(player.collider)) {
                enemy_bullet[i].exist = false;
                Mix_PlayChannel(5, Audio_Manager::chunk[SE_Player_Damaged], 0);

                if (--player.hp <= 0) {
                    Mix_PlayChannel(6, Audio_Manager::chunk[SE_Player_Killed], 0);
                    Mix_FadeOutMusic(100);
                    Mix_PlayMusic(Audio_Manager::music[BGM_Lose], 0);
                    judge = GJ_Lose;
                    pause = true;
                    SDL_RemoveTimer(timer);
                } else if (player.hp == MAX_PLAYER_HP * 2 / 3) {
                    Mix_PlayChannel(6, Audio_Manager::chunk[SE_Player_Warning_1], 0);
                } else if (player.hp == MAX_PLAYER_HP / 3) {
                    Mix_PlayChannel(6, Audio_Manager::chunk[SE_Player_Warning_2], 0);
                }
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

    if (judge != GJ_Lose) {

        /////////////////////////
        // 自機
        /////////////////////////
        glPushMatrix();
        TranslateVector(player.position);
        LookatPoint(player.position, player.aimpoint);
        glColor4d(1, player.hp / (float)MAX_PLAYER_HP, player.hp / (float)MAX_PLAYER_HP, 1);
        player.Draw();
        glPopMatrix();

        /////////////////////////
        // ポインタ
        /////////////////////////
        glPushMatrix();
        TranslateVector(player.aimpoint);
        LookatPoint(player.aimpoint, player.position);
        glScaled(3, 3, 3);
        Colored(player.color_type);
        pointer.Draw();
        glPopMatrix();
    }
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
            Colored(enemy[i].color_type);
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
            Colored(player.color_type);
            player_bullet[i].Draw();
            glPopMatrix();
        }
    }

    for (int i = 0; i < MAX_ENEMY_BULLET; i++) {
        if (enemy_bullet[i].exist) {
            glPushMatrix();
            TranslateVector(enemy_bullet[i].position);
            glScaled(0.5, 0.5, 0.5);
            Colored(enemy_bullet[i].color_type);
            enemy_bullet[i].Draw();
            glPopMatrix();
        }
    }

    shader.stop();
    /////////////////////////
    // 文字
    /////////////////////////
    if (0 <= time && time <= 20) {

        glPushMatrix();
        glColor3d(1, 0.5, 1);
        printString(0.03, 0.1, "READY?", 6);
        glPopMatrix();

    } else if (25 <= time && time <= 40) {
        glPushMatrix();
        glColor3d(1, 1, 0);
        printString(0.02, 0.1, "GO!", 3);
        glPopMatrix();
    }

    if (judge == GJ_Win) {
        glPushMatrix();
        glColor3d(1, 1, 0);
        printString(0.05, 0.1, "MISSION CLEAR", 13);
        glPopMatrix();
    }
    if (judge == GJ_Lose) {
        glPushMatrix();
        glColor3d(1, 0, 1);
        printString(0.06, 0.1, "MISSION FAILED", 14);
        glPopMatrix();
    }

    /////////////////////////
    // 体力バー
    /////////////////////////

    shader.start();
}

Uint32 MainGame::Timer(Uint32 interval, void *pram)
{
    if (++time > 700) {
        time = 700;
    } else if (time == 690) {
        Mix_FadeOutMusic(2000);
    }
    if (time == 25) {
        Mix_PlayChannel(6, Audio_Manager::chunk[SE_Count], 0);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        Mix_FadeInMusic(Audio_Manager::music[BGM_Main], -1, 1000);
    }
    if (time == 5 || time == 15) {
        Mix_PlayChannel(6, Audio_Manager::chunk[SE_Count], 0);
    }
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
        if (player.attack_span++ % 22 == 0) {
            Mix_PlayChannel(1, Audio_Manager::chunk[SE_Player_Shot], 0);
            Mix_Volume(1, MIX_MAX_VOLUME / 3);
            for (int i = 0; i < MAX_PLAYER_BULLET; i++) {
                if (!player_bullet[i].exist) {
                    player_bullet[i] = *new Bullet(m_bullet);
                    player_bullet[i].Set(player.position, (player.aimpoint - player.position).normalize() * 1.5, *new Vector3f(0, 0, 0), BT_Player);
                    player_bullet[i].color_type = player.color_type;
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
                            enemy_bullet[j].color_type = enemy[i].bullet_color_type;
                            v                          = v.Rotate(rotation_axis, -enemy[i].interval_angle);
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

                for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                    if (!enemy_bullet[j].exist) {
                        enemy_bullet[j] = *new Bullet(m_bullet);
                        enemy_bullet[j].Set(enemy[i].position, forward * enemy[i].shot_speed, forward * enemy[i].shot_accel, BT_Enemy);
                        enemy_bullet[j].color_type = enemy[i].bullet_color_type;
                        break;
                    }
                }

                for (int l = 0; l < (int)enemy[i].shoot_width; l++) {
                    Vector3f v = forward.Rotate(side, enemy[i].interval_angle * (l + 1));

                    for (int k = 0; k < enemy[i].number_of_bullet; k++) {
                        for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                            if (!enemy_bullet[j].exist) {
                                enemy_bullet[j] = *new Bullet(m_bullet);
                                enemy_bullet[j].Set(enemy[i].position, v * enemy[i].shot_speed, v * enemy[i].shot_accel, BT_Enemy);
                                enemy_bullet[j].color_type = enemy[i].bullet_color_type;
                                v                          = v.Rotate(forward, 360 / enemy[i].number_of_bullet);
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
                            enemy_bullet[j].color_type = (ColorType)RandBetween(2, 8);
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

                            switch (k) {
                            case 0:
                                enemy_bullet[j].color_type = CT_RED;
                                break;
                            case 1:
                                enemy_bullet[j].color_type = CT_BLUE;
                                break;
                            case 2:
                                enemy_bullet[j].color_type = CT_YELLLOW;
                                break;
                            }

                            break;
                        }
                    }
                }

                for (int j = 0; j < MAX_ENEMY_BULLET; j++) {
                    if (!enemy_bullet[j].exist) {
                        Vector3f v      = *new Vector3f(0, 0, -1);
                        enemy_bullet[j] = *new Bullet(m_bullet);
                        enemy_bullet[j].Set(enemy[i].position, v * enemy[i].shot_speed * 4, v * enemy[i].shot_accel, BT_Enemy);
                        enemy_bullet[j].color_type = CT_PURPLE;
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