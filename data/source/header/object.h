#pragma once
#include "../header/collider.h"
#include "../header/rawmodel.h"
#include "../header/toolkit.h"

#define MAX_PLAYER_HP 30
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

typedef enum {
    ET_NULL   = 0,
    ET_Sphere = 1,
    ET_Ufo    = 2,
    ET_Plane  = 3,
    ET_NUMBER = 4,
} EnemyType;

typedef enum {
    EST_NULL                                      = 0,
    EST_Forward                                   = 1,
    EST_Machine_Aim                               = 2,
    EST_Follow_Enemy_Direction                    = 3,
    EST_Scattering_Bullets_Forward                = 4,
    EST_Scattering_Bullets_Machine_Aim            = 5,
    EST_Scattering_Bullets_Follow_Enemy_Direction = 6,
    EST_Random_Scattering                         = 7,
    EST_Boss                                      = 8,
} EnemyShotType;

typedef enum {
    ESST_NULL          = 0,
    ESST_Always        = 1,
    ESST_Delay         = 2,
    ESST_WaitUntilStop = 3,
} EnemyShotStartType;

typedef enum {
    EMT_NULL       = 0,
    EMT_SpeedAccel = 1,
    EMT_Forward    = 2,
    EMT_Sin        = 3,
    EMT_Spiral     = 4,
    EMT_GoPoint    = 5,
    EMT_StayPoint  = 6,
    EMT_Away       = 7,
    EMT_Ufo        = 8,
    EMT_Boss       = 9,
} EnemyMoveType;

typedef enum {
    EMD_NULL    = 0,
    EMD_toRight = 1,
    EMD_toLeft  = 2,
    EMD_toFront = 3,
    EMD_toBack  = 4,
} EnemyMoveDirection;

typedef enum {
    EDT_NULL     = 0,
    EDT_toPlayer = 1,
    EDT_Forward  = 2,
    EDT_Custom   = 3,
} EnemyDirectionType;

typedef enum {
    BT_NULL   = 0,
    BT_Player = 1,
    BT_Enemy  = 2,
} Bullet_Type;
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
    ColorType color_type;
    bool exist;
    unsigned int hp;
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
//敵 スポーン時間　デスポーン時間　敵の形　敵の移動方法　敵の移動方向　敵の向き設定　敵の攻撃方法　敵の攻撃開始の設定　敵のHP　敵の攻撃開始時間　敵の攻撃スパン　敵のおおまかな攻撃回数　敵の初期位置　敵の初期向き　敵のスピードの向き　スピードの大きさ　敵の加速度の向き　加速度の大きさ敵の目的位置
/////////////////////////////////////////////////////////////////////////////

typedef struct {
    unsigned int spawn_time;
    unsigned int despawn_time;

    EnemyType enemy_type;
    EnemyMoveType enemy_move_type;
    EnemyMoveDirection enemy_move_direction;
    EnemyDirectionType enemy_direction_type;

    EnemyShotType enemy_shot_type;
    EnemyShotStartType enemy_shot_start_type;

    unsigned int hp;

    unsigned int attack_delay;
    unsigned int attack_span;
    unsigned int attack_times;

    unsigned int attack_span_a_span_to_a_span;
    unsigned int attack_times_in_a_span;

    float shot_speed;
    float shot_accel;
    unsigned int number_of_bullet;
    float interval_angle;
    float shoot_width;

    Vector3f enemy_position;
    Vector3f enemy_rotation;
    Vector3f enemy_speed;
    float enemy_speed_magnitude;
    Vector3f enemy_accel;
    float enemy_accel_magnitude;

    Vector3f point;

    ColorType enemy_color_type;
    ColorType bullet_color_type;

} EnemyInfo;
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Enemy : public Chara {
private:
public:
    unsigned int spawn_time;
    unsigned int despawn_time;

    unsigned int living_time;

    EnemyType enemy_type;
    EnemyMoveType enemy_move_type;
    EnemyMoveDirection enemy_move_direction;
    EnemyDirectionType enemy_direction_type;

    EnemyShotType enemy_shot_type;
    EnemyShotStartType enemy_shot_start_type;

    unsigned int hp;

    unsigned int attack_delay;
    unsigned int attack_span;
    unsigned int attack_span_count;
    unsigned int attack_times;

    unsigned int attack_span_a_span_to_a_span;
    unsigned int attack_times_in_a_span;
    unsigned int attack_span_a_span_to_a_span_count;
    unsigned int attack_times_in_a_span_count;

    float shot_speed;
    float shot_accel;
    unsigned int number_of_bullet;
    float interval_angle;
    float shoot_width;

    float enemy_speed_magnitude;
    float enemy_accel_magnitude;

    Vector3f point;
    Vector3f shot_to_point[3];
    Vector3f shot_from_point[3];

    float subargument[3];

    ColorType bullet_color_type;

    Enemy();
    Enemy(const char *filename);
    Enemy(OBJMESH model);
    void Move(Player player);
    void Set(EnemyInfo info);
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
    void Set(Vector3f p, Vector3f v, Vector3f a, Bullet_Type bullet_type);
};
