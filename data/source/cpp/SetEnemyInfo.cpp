#include "../header/gamesystem.h"

#define POSITION_LEFT 30
#define POSITION_RIGHT -30
#define POSITION_UP 40
#define POSITION_DOWN -40
#define POSITION_BACK 100

void MainGame::SetEnemyInfo()
{
    EnemyInfo ei[] = {
        {
            60,                                        //スポーン時間
            130,                                       //デスポーン時間
            ET_Sphere,                                 //敵の形
            EMT_StayPoint,                             //敵の移動方法
            EMD_toRight,                               //敵の移動方向
            EDT_toPlayer,                              //敵の向き設定
            EST_Machine_Aim,                           //敵の攻撃の設定
            ESST_WaitUntilStop,                        //敵の攻撃開始の設定
            3,                                         //敵のHP
            0,                                         //敵の攻撃開始時間
            150,                                       //敵の攻撃スパン
            5,                                         //敵の攻撃回数
            0,                                         //一回の攻撃内の一間隔ごとのスパン
            1,                                         //一回の攻撃内のループ回数
            0.4f,                                      //攻撃速度
            0.0f,                                      //攻撃加速度
            3,                                         //一回の発射による弾数
            15.0f,                                     //角度的な幅間隔
            1.0f,                                      //数値的な幅間隔
            Vector3f(POSITION_LEFT, 0, POSITION_BACK), //敵の初期位置
            Vector3f_ZERO,                             //敵の初期向き
            Vector3f(1, 0, 0),                         //敵のスピードの向き
            0.1f,                                      //スピードの大きさ
            Vector3f_ZERO,                             //敵の加速度の向き
            0.00f,                                     //加速度の大きさ
            Vector3f(10, 0, 50),                       //敵の目的地
        },
        {
            60,                                         //スポーン時間
            130,                                        //デスポーン時間
            ET_Sphere,                                  //敵の形
            EMT_StayPoint,                              //敵の移動方法
            EMD_toLeft,                                 //敵の移動方向
            EDT_toPlayer,                               //敵の向き設定
            EST_Machine_Aim,                            //敵の攻撃の設定
            ESST_WaitUntilStop,                         //敵の攻撃開始の設定
            3,                                          //敵のHP
            0,                                          //敵の攻撃開始時間
            150,                                        //敵の攻撃スパン
            6,                                          //敵の攻撃回数
            0,                                          //一回の攻撃内の一間隔ごとのスパン
            1,                                          //一回の攻撃内のループ回数
            0.3f,                                       //攻撃速度
            0.0f,                                       //攻撃加速度
            3,                                          //一回の発射による弾数
            15.0f,                                      //角度的な幅間隔
            1.0f,                                       //数値的な幅間隔
            Vector3f(POSITION_RIGHT, 0, POSITION_BACK), //敵の初期位置
            Vector3f_ZERO,                              //敵の初期向き
            Vector3f_ZERO,                              //敵のスピードの向き
            0.1f,                                       //スピードの大きさ
            Vector3f_ZERO,                              //敵の加速度の向き
            0.00f,                                      //加速度の大きさ
            Vector3f(-10, 0, 50),                       //敵の目的地
        },
        {
            60,                                          //スポーン時間
            130,                                         //デスポーン時間
            ET_Sphere,                                   //敵の形
            EMT_StayPoint,                               //敵の移動方法
            EMD_toLeft,                                  //敵の移動方向
            EDT_toPlayer,                                //敵の向き設定
            EST_Machine_Aim,                             //敵の攻撃の設定
            ESST_WaitUntilStop,                          //敵の攻撃開始の設定
            3,                                           //敵のHP
            0,                                           //敵の攻撃開始時間
            150,                                         //敵の攻撃スパン
            6,                                           //敵の攻撃回数
            0,                                           //一回の攻撃内の一間隔ごとのスパン
            1,                                           //一回の攻撃内のループ回数
            0.2f,                                        //攻撃速度
            0.0f,                                        //攻撃加速度
            2,                                           //一回の発射による弾数
            15.0f,                                       //角度的な幅間隔
            1.0f,                                        //数値的な幅間隔
            Vector3f(POSITION_RIGHT, 20, POSITION_BACK), //敵の初期位置
            Vector3f_ZERO,                               //敵の初期向き
            Vector3f_ZERO,                               //敵のスピードの向き
            0.1f,                                        //スピードの大きさ
            Vector3f_ZERO,                               //敵の加速度の向き
            0.00f,                                       //加速度の大きさ
            Vector3f(-10, 10, 50),                       //敵の目的地
        },
        {
            60,                                         //スポーン時間
            130,                                        //デスポーン時間
            ET_Sphere,                                  //敵の形
            EMT_StayPoint,                              //敵の移動方法
            EMD_toRight,                                //敵の移動方向
            EDT_toPlayer,                               //敵の向き設定
            EST_Machine_Aim,                            //敵の攻撃の設定
            ESST_WaitUntilStop,                         //敵の攻撃開始の設定
            3,                                          //敵のHP
            0,                                          //敵の攻撃開始時間
            150,                                        //敵の攻撃スパン
            6,                                          //敵の攻撃回数
            0,                                          //一回の攻撃内の一間隔ごとのスパン
            1,                                          //一回の攻撃内のループ回数
            0.2f,                                       //攻撃速度
            0.0f,                                       //攻撃加速度
            2,                                          //一回の発射による弾数
            15.0f,                                      //角度的な幅間隔
            1.0f,                                       //数値的な幅間隔
            Vector3f(POSITION_LEFT, 20, POSITION_BACK), //敵の初期位置
            Vector3f_ZERO,                              //敵の初期向き
            Vector3f_ZERO,                              //敵のスピードの向き
            0.1f,                                       //スピードの大きさ
            Vector3f_ZERO,                              //敵の加速度の向き
            0.00f,                                      //加速度の大きさ
            Vector3f(10, 10, 50),                       //敵の目的地
        },
        {
            140,                            //スポーン時間
            0,                              //デスポーン時間
            ET_Sphere,                      //敵の形
            EMT_Sin,                        //敵の移動方法
            EMD_toRight,                    //敵の移動方向
            EDT_Forward,                    //敵の向き設定
            EST_Forward,                    //敵の攻撃の設定
            ESST_Always,                    //敵の攻撃開始の設定
            3,                              //敵のHP
            10,                             //敵の攻撃開始時間
            20,                             //敵の攻撃スパン
            1000,                           //敵の攻撃回数
            0,                              //一回の攻撃内の一間隔ごとのスパン
            1,                              //一回の攻撃内のループ回数
            0.2f,                           //攻撃速度
            0.0f,                           //攻撃加速度
            1,                              //一回の発射による弾数
            15.0f,                          //角度的な幅間隔
            1.0f,                           //数値的な幅間隔
            Vector3f(POSITION_LEFT, 5, 50), //敵の初期位置
            Vector3f_ZERO,                  //敵の初期向き
            Vector3f_ZERO,                  //敵のスピードの向き
            0.1f,                           //スピードの大きさ
            Vector3f_ZERO,                  //敵の加速度の向き
            0.00f,                          //加速度の大きさ
            Vector3f_ZERO                   //敵の目的地
        },
        {
            140,                              //スポーン時間
            0,                                //デスポーン時間
            ET_Sphere,                        //敵の形
            EMT_Sin,                          //敵の移動方法
            EMD_toLeft,                       //敵の移動方向
            EDT_Forward,                      //敵の向き設定
            EST_Forward,                      //敵の攻撃の設定
            ESST_Always,                      //敵の攻撃開始の設定
            3,                                //敵のHP
            10,                               //敵の攻撃開始時間
            20,                               //敵の攻撃スパン
            1000,                             //敵の攻撃回数
            0,                                //一回の攻撃内の一間隔ごとのスパン
            1,                                //一回の攻撃内のループ回数
            0.2f,                             //攻撃速度
            0.0f,                             //攻撃加速度
            1,                                //一回の発射による弾数
            15.0f,                            //角度的な幅間隔
            1.0f,                             //数値的な幅間隔
            Vector3f(POSITION_RIGHT, -5, 50), //敵の初期位置
            Vector3f_ZERO,                    //敵の初期向き
            Vector3f_ZERO,                    //敵のスピードの向き
            0.1f,                             //スピードの大きさ
            Vector3f_ZERO,                    //敵の加速度の向き
            0.00f,                            //加速度の大きさ
            Vector3f_ZERO                     //敵の目的地
        },
        {
            160,                             //スポーン時間
            0,                               //デスポーン時間
            ET_Sphere,                       //敵の形
            EMT_Sin,                         //敵の移動方法
            EMD_toRight,                     //敵の移動方向
            EDT_Forward,                     //敵の向き設定
            EST_Forward,                     //敵の攻撃の設定
            ESST_Always,                     //敵の攻撃開始の設定
            3,                               //敵のHP
            10,                              //敵の攻撃開始時間
            20,                              //敵の攻撃スパン
            1000,                            //敵の攻撃回数
            0,                               //一回の攻撃内の一間隔ごとのスパン
            1,                               //一回の攻撃内のループ回数
            0.2f,                            //攻撃速度
            0.0f,                            //攻撃加速度
            1,                               //一回の発射による弾数
            15.0f,                           //角度的な幅間隔
            1.0f,                            //数値的な幅間隔
            Vector3f(POSITION_LEFT, -5, 50), //敵の初期位置
            Vector3f_ZERO,                   //敵の初期向き
            Vector3f_ZERO,                   //敵のスピードの向き
            0.1f,                            //スピードの大きさ
            Vector3f_ZERO,                   //敵の加速度の向き
            0.00f,                           //加速度の大きさ
            Vector3f_ZERO                    //敵の目的地
        },
        {
            160,                             //スポーン時間
            0,                               //デスポーン時間
            ET_Sphere,                       //敵の形
            EMT_Sin,                         //敵の移動方法
            EMD_toLeft,                      //敵の移動方向
            EDT_Forward,                     //敵の向き設定
            EST_Forward,                     //敵の攻撃の設定
            ESST_Always,                     //敵の攻撃開始の設定
            3,                               //敵のHP
            10,                              //敵の攻撃開始時間
            20,                              //敵の攻撃スパン
            1000,                            //敵の攻撃回数
            0,                               //一回の攻撃内の一間隔ごとのスパン
            1,                               //一回の攻撃内のループ回数
            0.2f,                            //攻撃速度
            0.0f,                            //攻撃加速度
            1,                               //一回の発射による弾数
            15.0f,                           //角度的な幅間隔
            1.0f,                            //数値的な幅間隔
            Vector3f(POSITION_RIGHT, 5, 50), //敵の初期位置
            Vector3f_ZERO,                   //敵の初期向き
            Vector3f_ZERO,                   //敵のスピードの向き
            0.1f,                            //スピードの大きさ
            Vector3f_ZERO,                   //敵の加速度の向き
            0.00f,                           //加速度の大きさ
            Vector3f_ZERO                    //敵の目的地
        },
        {
            170,                                        //スポーン時間
            300,                                        //デスポーン時間
            ET_Sphere,                                  //敵の形
            EMT_StayPoint,                              //敵の移動方法
            EMD_toBack,                                 //敵の移動方向
            EDT_toPlayer,                               //敵の向き設定
            EST_Machine_Aim,                            //敵の攻撃の設定
            ESST_WaitUntilStop,                         //敵の攻撃開始の設定
            3,                                          //敵のHP
            0,                                          //敵の攻撃開始時間
            150,                                        //敵の攻撃スパン
            6,                                          //敵の攻撃回数
            0,                                          //一回の攻撃内の一間隔ごとのスパン
            1,                                          //一回の攻撃内のループ回数
            0.3f,                                       //攻撃速度
            0.0f,                                       //攻撃加速度
            3,                                          //一回の発射による弾数
            15.0f,                                      //角度的な幅間隔
            1.0f,                                       //数値的な幅間隔
            Vector3f(POSITION_RIGHT, 0, POSITION_BACK), //敵の初期位置
            Vector3f_ZERO,                              //敵の初期向き
            Vector3f_ZERO,                              //敵のスピードの向き
            0.1f,                                       //スピードの大きさ
            Vector3f_ZERO,                              //敵の加速度の向き
            0.00f,                                      //加速度の大きさ
            Vector3f(-10, 0, 50),                       //敵の目的地
        },
    };

    for (int i = 0; i < sizeof(ei) / sizeof(EnemyInfo); i++) {
        enemyinfo.push_back(ei[i]);
    }
}