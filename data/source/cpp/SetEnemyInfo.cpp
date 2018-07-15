#include "../header/gamesystem.h"

void MainGame::SetEnemyInfo()
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //スポーン時間　デスポーン時間　敵の形　敵の移動方法　敵の移動方向　敵の向き設定　敵の攻撃方法　敵の攻撃開始の設定　敵のHP　敵の攻撃開始時間　敵の攻撃スパン　敵のおおまかな攻撃回数　敵の初期位置　敵の初期向き　敵のスピード 敵の加速度　敵の目的位置
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    EnemyInfo ei[] = {
        {
            10,
            300,
            ET_Sphere,
            EMT_StayPoint,
            EMD_toRight,
            EDT_Forward,
            EST_Machine_Aim,
            ESST_WaitUntilStop,
            3,
            0,
            300,
            10,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f(0, 0, 0),
        },
        {
            20,
            300,
            ET_Sphere,
            EMT_StayPoint,
            EMD_toRight,
            EDT_Forward,
            EST_Machine_Aim,
            ESST_WaitUntilStop,
            3,
            0,
            300,
            10,
            Vector3f(10, 0, 0),
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f(0, 0, 0),
        },
        {
            30,
            300,
            ET_Sphere,
            EMT_StayPoint,
            EMD_toRight,
            EDT_Forward,
            EST_Machine_Aim,
            ESST_WaitUntilStop,
            3,
            0,
            300,
            10,
            Vector3f(-10, 0, 0),
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f(0, 0, 0),
        },
        {
            40,
            300,
            ET_Sphere,
            EMT_StayPoint,
            EMD_toRight,
            EDT_Forward,
            EST_Machine_Aim,
            ESST_WaitUntilStop,
            3,
            0,
            300,
            10,
            Vector3f(-10, 0, 0),
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f_ZERO,
            Vector3f(0, 0, 0),
        },
    };

    for (int i = 0; i < sizeof(ei) / sizeof(EnemyInfo); i++) {
        enemyinfo.push_back(ei[i]);
    }
}