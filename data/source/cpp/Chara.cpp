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
    //speed    = speed + accel;
    //position = position + speed;
    angle += 1.0f;
    position = position + *new Vector3f(0, std::cos(angle * M_PI / 180) / 10, -0.05f);
}
void Enemy::Set(Vector3f p, Vector3f v, Vector3f a)
{
    exist    = true;
    position = p;
    speed    = v;
    accel    = a;
    angle    = 0;
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