#include "../header/object.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////s
Chara::Chara()
    : Object()
{
}
Chara::Chara(const char *filename)
    : Object(filename)
{
}
Chara::Chara(OBJMESH model)
    : Object(model)
{
}
void Chara::Move()
{
}
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
Player::Player()
    : Chara()
{
}
Player::Player(const char *filename)
    : Chara(filename)
{
}
Player::Player(OBJMESH model)
    : Chara(model)
{
}
void Player::Move()
{
    speed    = speed + accel;
    position = position + speed;
}
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
Enemy::Enemy()
    : Chara()
{
}
Enemy::Enemy(const char *filename)
    : Chara(filename)
{
}
Enemy::Enemy(OBJMESH model)
    : Chara(model)
{
}
void Enemy::Move()
{

    switch (enemy_move_type) {
    case EMT_Forward:
        position = position + Vector3f(0, 0, -1);
        break;
    case EMT_Sin:
        switch (enemy_move_direction) {
        case EMD_toFront:
            break;
        case EMD_toBack:
            break;
        case EMD_toRight:
            break;
        case EMD_toLeft:
            break;
        }
        break;
    case EMT_Spiral:
        break;
    case EMT_StayPoint:
        break;
    }

    //speed    = speed + accel;
    //position = position + speed;

    static float angle = 0;
    angle += 1.0f;
    position = position + *new Vector3f(0, std::cos(angle * M_PI / 180) / 10, -0.05f);
}
void Enemy::Set(EnemyInfo info)
{
    exist = true;
    //スポーン時間　デスポーン時間　敵の形　敵の移動方法　敵の移動方向　敵の向き設定　敵の攻撃方法　敵の攻撃開始の設定　敵のHP　敵の攻撃開始時間　敵の攻撃スパン　敵のおおまかな攻撃回数　敵の初期位置　敵の初期向き　敵のスピード 敵の加速度　敵の目的位置
    spawn_time   = info.spawn_time;
    despawn_time = info.despawn_time;

    enemy_type = info.enemy_type;
    switch (enemy_type) {
    case ET_Sphere:
        //当たり判定
        break;
    case ET_Ufo:
        break;
    case ET_Plane:
        break;
    default:
        break;
    };

    enemy_move_type      = info.enemy_move_type;
    enemy_move_direction = info.enemy_move_direction;
    enemy_direction_type = info.enemy_direction_type;

    enemy_shot_type       = info.enemy_shot_type;
    enemy_shot_start_type = info.enemy_shot_start_type;

    hp = info.hp;

    attack_delay = info.attack_delay;
    attack_span  = info.attack_span;
    attack_times = info.attack_times;

    position = info.enemy_position;
    rotation = info.enemy_rotation;
    speed    = info.enemy_speed;
    accel    = info.enemy_accel;

    point = info.point;
}
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
Bullet::Bullet()
    : Chara()
{
}
Bullet::Bullet(const char *filename)
    : Chara(filename)
{
}
Bullet::Bullet(OBJMESH model)
    : Chara(model)
{
}
void Bullet::Move()
{
    speed    = speed + accel;
    position = position + speed;
}
void Bullet::Set(Vector3f p, Vector3f v, Vector3f a)
{
    exist    = true;
    position = p;
    speed    = v;
    accel    = a;
}