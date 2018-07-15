#pragma once
#include "../header/collider.h"
#include "../header/rawmodel.h"
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
typedef enum {
    OTYPE_Player        = 0,
    OTYPE_Enemy         = 1,
    OTYPE_Boss          = 2,
    OTYPE_Player_Bullet = 3,
    OTYPE_Enemy_Bullet  = 4,
    OTYPE_Other         = 5
} Object_Type;
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Object {
private:
public:
    Object_Type type;
    OBJMESH Model;
    Vector3f position;
    Vector3f rotation;
    Vector3f scale;

    Object();
    Object(const char *filename);
    Object(const char *filename, Vector3f p, Vector3f r, Vector3f s);
    Object(OBJMESH model);
    Object(OBJMESH model, Vector3f p, Vector3f r, Vector3f s);
    void Draw();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Chara : public Object {
private:
public:
    bool exist;
    unsigned int HP;
    Vector3f aimpoint;
    Vector3f forward;
    Vector3f speed;
    Vector3f accel;
    //当たり判定
    Collider collider;

    Chara();
    Chara(const char *filename);
    Chara(OBJMESH model);
    virtual void Move();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Player : public Chara {
private:
public:
    unsigned int attack_span;

    Player();
    Player(const char *filename);
    Player(OBJMESH model);
    void Move();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Enemy : public Chara {
private:
public:
    Enemy();
    Enemy(const char *filename);
    Enemy(OBJMESH model);
    void Move();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Bullet : public Chara {
private:
public:
    Bullet();
    Bullet(const char *filename);
    Bullet(OBJMESH model);
    void Move();
};