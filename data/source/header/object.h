#include "../header/rawmodel.h"

typedef enum {
    OTYPE_Player = 0,
    OTYPE_Enemy = 1,
    OTYPE_Boss = 2,
    OTYPE_Player_Bullet = 3,
    OTYPE_Enemy_Bullet = 4,
    OTYPE_Other = 5
} Object_Type;

class Object
{
  private:
    Object_Type type;
    OBJMESH Model;
    Vector3f Position;
    Vector3f Rotation;
    Vector3f Scale;

  public:
    Object();
    Object(const char *filename);
    Object(const char *filename, Vector3f p, Vector3f r, Vector3f s);
    void Draw();
};

class Chara : public Object
{
  private:
    unsigned int HP;
    Vector3f forward;
    Vector3f speed;
    Vector3f accel;
    //当たり判定
  public:
    Chara();
    Chara(const char *filename);
    //virtual void move() = 0;
};

class Player : public Chara
{
  private:
  public:
    Player();
    Player(const char *filename);
    //void move();
};

class Enemy : public Chara
{
  private:
  public:
    Enemy();
    Enemy(const char *filename);
    //void move();
};

class Bullet : public Chara
{
  private:
  public:
    Bullet();
    Bullet(const char *filename);
    //void move();
};