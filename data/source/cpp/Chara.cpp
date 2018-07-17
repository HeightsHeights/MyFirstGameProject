
#include "../header/object.h"
#include "../header/toolkit.h"
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
void Enemy::Move(Player player)
{

    switch (enemy_move_type) {
    case EMT_Forward: {
        Vector3f v = Vector3f(0, 0, -enemy_speed_magnitude);
        position   = position + v;
        collider.MoveCollider(v);
        forward = Vector3f(0, 0, -enemy_speed_magnitude);
        break;
    }
    case EMT_Sin: {
        subargument[0] += 0.5f;
        if (subargument[0] >= 360) {
            subargument[0] = 0;
        }
        Vector3f v;
        switch (enemy_move_direction) {
        case EMD_toFront:
            v = *new Vector3f(0, std::cos(subargument[0] * M_PI / 180) / 20, -enemy_speed_magnitude);
            break;
        case EMD_toBack:
            v = *new Vector3f(0, std::cos(subargument[0] * M_PI / 180) / 20, enemy_speed_magnitude);
            break;
        case EMD_toRight:
            v = *new Vector3f(-enemy_speed_magnitude, std::cos(subargument[0] * M_PI / 180) / 20, 0);
            break;
        case EMD_toLeft:
            v = *new Vector3f(enemy_speed_magnitude, std::cos(subargument[0] * M_PI / 180) / 20, 0);
            break;
        }
        position = position + v;
        collider.MoveCollider(v);
        forward = v.normalize();
        break;
    }
    case EMT_Spiral: {
        subargument[0]++;
        if (subargument[0] >= 360) {
            subargument[0] = 0;
        }
        float angle = subargument[0] * M_PI / 180;
        switch (enemy_move_direction) {
        case EMD_toFront:
            Vector3f v = *new Vector3f(std::sin(angle) / 20, std::cos(angle) / 20, -enemy_speed_magnitude);
            forward    = v;
            position   = position + v;
            collider.MoveCollider(v);
            break;
        }
        break;
    }
    case EMT_GoPoint: {
        if ((point - position).magnitude() > enemy_speed_magnitude) {
            Vector3f v = (point - position).normalize();
            position   = position + v * enemy_speed_magnitude;
            forward    = v;
            collider.MoveCollider(v * enemy_speed_magnitude);
        } else {
            enemy_move_type = EMT_StayPoint;
            subargument[1]  = 1;
        }
        break;
    }
    case EMT_StayPoint: {
        if (living_time + spawn_time >= despawn_time) {
            enemy_move_type = EMT_Away;
        } else if ((point - position).magnitude() > enemy_speed_magnitude) {
            point.y    = player.position.y;
            Vector3f v = (point - position).normalize();
            position   = position + v * 0.01f;
            collider.MoveCollider(v * 0.01f);
        }
        break;
    }
    case EMT_Away: {
        Vector3f v;
        switch (enemy_move_direction) {
        case EMD_toFront:
            v = *new Vector3f(0, 0, -enemy_speed_magnitude);
            break;
        case EMD_toBack:
            v = *new Vector3f(0, 0, enemy_speed_magnitude);
            break;
        case EMD_toRight:
            v = *new Vector3f(-enemy_speed_magnitude, 0, 0);
            break;
        case EMD_toLeft:
            v = *new Vector3f(enemy_speed_magnitude, 0, 0);
            break;
        }
        position = position + v;
        collider.MoveCollider(v);
        break;
    }
    case EMT_Ufo: {

        if ((point - position).magnitude() > enemy_speed_magnitude && subargument[1] == 0) {
            Vector3f v;
            v        = (point - position).normalize();
            position = position + v * enemy_speed_magnitude;
            forward  = v;
            collider.MoveCollider(v * enemy_speed_magnitude);
        } else if (living_time + spawn_time >= despawn_time) {
            enemy_move_type = EMT_Away;
        } else {
            subargument[1] = 1;
            point.y        = player.position.y;
            Vector3f v     = (point - position).normalize();
            position       = position + v * 0.01f;
            forward        = forward.Rotate(Vector3f(0, 1, 0), 0.5f);
            collider.MoveCollider(v * 0.01f);
        }
        break;
    }
    case EMT_Boss: {

        switch ((int)subargument[2]) {
        case 0: {

            forward = Vector3f(0, 0, -1);
            if ((point - position).magnitude() > enemy_speed_magnitude) {
                Vector3f v;
                v        = (point - position).normalize();
                position = position + v * enemy_speed_magnitude;
                collider.MoveCollider(v * enemy_speed_magnitude);

                for (int i = 0; i < 3; i++) {
                    shot_from_point[i] = shot_from_point[i] + (v * enemy_speed_magnitude);
                }
            } else {
                subargument[2]++;
            }
            break;
        }
        case 1: {
            float angle = subargument[0] * M_PI / 180;
            Vector3f v  = Vector3f(std::cos(angle) / 10, (2 * std::pow(std::cos(angle), 2) - 1) / 10, 0);
            subargument[0] += 0.2f;
            position = position + v;
            collider.MoveCollider(v);
            forward = forward.Rotate(Vector3f(0, 1, 0), 0.5f);
            for (int i = 0; i < 3; i++) {
                shot_from_point[i] = shot_from_point[i] + v;
                shot_from_point[i] = shot_from_point[i] - position;

                shot_from_point[i] = shot_from_point[i].Rotate(Vector3f(0, 1, 0), 0.5f);
                shot_from_point[i] = shot_from_point[i] + position;
            }
            break;
        }
        }
    }
    }

    if (!IsBetween(position.x, -50, 50) || !IsBetween(position.y, -50, 50) || !IsBetween(position.z, -30, 150)) {
        exist = false;
    }
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
        collider.spheres.push_back(Sphere(info.enemy_position, 1));
        break;
    case ET_Ufo: {
        collider.spheres.push_back(Sphere(info.enemy_position, 3.5));

        Vector3f v         = Vector3f(0, 0, -10);
        shot_from_point[0] = info.enemy_position + v;
        shot_from_point[1] = info.enemy_position + v.Rotate(Vector3f(0, 1, 0), 120);
        shot_from_point[2] = info.enemy_position + v.Rotate(Vector3f(0, 1, 0), -120);

        break;
    }
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

    attack_span_a_span_to_a_span = info.attack_span_a_span_to_a_span;
    attack_times_in_a_span       = info.attack_times_in_a_span;

    shot_speed       = info.shot_speed;
    shot_accel       = info.shot_accel;
    number_of_bullet = info.number_of_bullet;
    interval_angle   = info.interval_angle;
    shoot_width      = info.shoot_width;

    position              = info.enemy_position;
    rotation              = info.enemy_rotation;
    speed                 = info.enemy_speed;
    enemy_speed_magnitude = info.enemy_speed_magnitude;

    accel                 = info.enemy_accel;
    enemy_accel_magnitude = info.enemy_accel_magnitude;

    point = info.point;

    attack_span_a_span_to_a_span_count = 0;
    attack_span_count                  = 0;
    attack_times_in_a_span_count       = 0;
    subargument[0] = subargument[1] = subargument[2] = 0;
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
    collider.MoveCollider(speed);
    if (!IsBetween(position.x, -50, 50) || !IsBetween(position.y, -50, 50) || !IsBetween(position.z, -20, 150)) {
        exist = false;
    }
}
void Bullet::Set(Vector3f p, Vector3f v, Vector3f a, Bullet_Type bullet_type)
{
    exist    = true;
    position = p;
    speed    = v;
    accel    = a;

    switch (bullet_type) {
    case BT_Player:
        collider.spheres.push_back(Sphere(p, 0.4f));
        break;
    case BT_Enemy:
        collider.spheres.push_back(Sphere(p, 0.5f));
        break;
    }
}