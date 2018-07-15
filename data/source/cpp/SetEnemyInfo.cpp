#include "../header/gamesystem.h"

void MainGame::SetEnemyInfo()
{
    EnemyInfo ei[] = {
        {
            10,                  //スポーン時間
            300,                 //デスポーン時間
            ET_Sphere,           //敵の形
            EMT_StayPoint,       //敵の移動方法
            EMD_toRight,         //敵の移動方向
            EDT_Forward,         //敵の向き設定
            EST_Machine_Aim,     //敵の攻撃の設定
            ESST_WaitUntilStop,  //敵の攻撃開始の設定
            3,                   //敵のHP
            0,                   //敵の攻撃開始時間
            300,                 //敵の攻撃スパン
            10,                  //敵の攻撃回数
            Vector3f(0, 0, 100), //敵の初期位置
            Vector3f_ZERO,       //敵の初期向き
            Vector3f_ZERO,       //敵のスピード
            Vector3f_ZERO,       //敵の加速度
            Vector3f(0, 0, 0),   //敵の目的地
        },
        {
            20,                   //スポーン時間
            300,                  //デスポーン時間
            ET_Sphere,            //敵の形
            EMT_StayPoint,        //敵の移動方法
            EMD_toRight,          //敵の移動方向
            EDT_Forward,          //敵の向き設定
            EST_Machine_Aim,      //敵の攻撃の設定
            ESST_WaitUntilStop,   //敵の攻撃開始の設定
            3,                    //敵のHP
            0,                    //敵の攻撃開始時間
            300,                  //敵の攻撃スパン
            10,                   //敵の攻撃回数
            Vector3f(10, 0, 100), //敵の初期位置
            Vector3f_ZERO,        //敵の初期向き
            Vector3f_ZERO,        //敵のスピード
            Vector3f_ZERO,        //敵の加速度
            Vector3f(0, 0, 0),    //敵の目的地
        },
        {
            30,                    //スポーン時間
            300,                   //デスポーン時間
            ET_Sphere,             //敵の形
            EMT_StayPoint,         //敵の移動方法
            EMD_toRight,           //敵の移動方向
            EDT_Forward,           //敵の向き設定
            EST_Machine_Aim,       //敵の攻撃の設定
            ESST_WaitUntilStop,    //敵の攻撃開始の設定
            3,                     //敵のHP
            0,                     //敵の攻撃開始時間
            300,                   //敵の攻撃スパン
            10,                    //敵の攻撃回数
            Vector3f(-10, 0, 100), //敵の初期位置
            Vector3f_ZERO,         //敵の初期向き
            Vector3f_ZERO,         //敵のスピード
            Vector3f_ZERO,         //敵の加速度
            Vector3f(0, 0, 0),     //敵の目的地
        },
        {
            40,                  //スポーン時間
            300,                 //デスポーン時間
            ET_Sphere,           //敵の形
            EMT_StayPoint,       //敵の移動方法
            EMD_toRight,         //敵の移動方向
            EDT_Forward,         //敵の向き設定
            EST_Machine_Aim,     //敵の攻撃の設定
            ESST_WaitUntilStop,  //敵の攻撃開始の設定
            3,                   //敵のHP
            0,                   //敵の攻撃開始時間
            300,                 //敵の攻撃スパン
            10,                  //敵の攻撃回数
            Vector3f(0, 0, 100), //敵の初期位置
            Vector3f_ZERO,       //敵の初期向き
            Vector3f_ZERO,       //敵のスピード
            Vector3f_ZERO,       //敵の加速度
            Vector3f(0, 0, 0),   //敵の目的地
        },
    };

    for (int i = 0; i < sizeof(ei) / sizeof(EnemyInfo); i++) {
        enemyinfo.push_back(ei[i]);
    }
}