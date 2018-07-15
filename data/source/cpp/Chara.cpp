#include "../header/object.h"

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
void Chara::move()
{
    position = position + speed;
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