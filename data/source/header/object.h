#include "../header/vector.h"
#include "../header/rawmodel.h"

typedef enum {
    Player = 0,
    Enemy = 1,
    Boss = 2,
    Player_Bullet = 3,
    Enemy_Bullet = 4,
    Other = 5
} Object_Type;

class Object
{
  private:
    Object_Type type;
    OBJMESH Model;
    Vector3f Position = Vector3f(0, 0, 0);
    Vector3f Rotation = Vector3f(0, 0, 0);
    Vector3f Scale = Vector3f(1, 1, 1);

  public:
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
    Chara(const char *filename);
    virtual void move() = 0;
};

class Player : public Chara
{
  private:
  public:
    Player(const char *filename);
    void move();
};

class Enemy : public Chara
{
  private:
  public:
    Enemy(const char *filename);
    void move();
};

class Bullet : public Chara
{
  private:
  public:
    Bullet(const char *filename);
    void move();
};