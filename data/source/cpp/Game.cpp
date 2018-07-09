//ゲームのメイン
#include "../header/game.h"
#include "../header/audio.h"
#include "../header/controller.h"
#include "../header/object.h"
#include "../header/shader.h"
#include "../header/ui_image.h"
#include <SDL2/SDL_mixer.h>

//window系の初期化
bool InitWindow();
//gl系の初期化
bool InitGL(int argc, char *argv[]);
//音楽系の初期化
bool InitAudio();
//システム全体の初期化
bool InitSystem();

void Render();
void Clear();

//*******************************************************************************************************************************************

GLdouble manupilator_vertex[][3] = {
    { 0.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 }
};
int manupilator_edge[][2] = {
    { 0, 1 },
    { 0, 2 },
    { 0, 3 }
};
GLfloat manupilator_color[][4] = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f }
};

float light0_position[4] = { 0.0, 10000.0, 0.0, 1.0 };
GLfloat light1pos[]      = { 5.0, 3.0, 0.0, 1.0 };

GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[]   = { 0.8, 0.2, 0.2, 1.0 };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// メイン
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player player;
Enemy enemy;
int main(int argc, char *argv[])
{
    if (!InitWindow()) {
        printf("error initwindow\n");
        return -1;
    }
    if (!InitGL(argc, argv)) {
        printf("error initgl\n");
        return -1;
    }
    Controller_Maneger::Init_Controller();
    StaticShader shader = *new StaticShader();

    SDL_Event event;
    player = *new Player("data/data_3d/untitled.obj");
    enemy  = *new Enemy("data/data_3d/test03.obj");
    while (event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        //glClearColor(0.f, 0.f, 0.f, 0.f);

        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.start();

        Render();
        glRotated(0.05, 0, 1, 0);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
        player.Draw();
        //enemy.Draw();
        //glColor3f(255, 0, 0);
        glutSolidSphere(1, 10, 10);

        shader.stop();

        SDL_GL_SwapWindow(GameManager::window);
        SDL_Delay(4);
    }

    Clear();
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ウィンドウ初期化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitWindow()
{
    //sdlの初期化
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK)) {
        printf("error sdlinit\n");
        return false;
    }
    //********************************
    //ディスプレイのwindow関係の初期化
    GameManager::window = SDL_CreateWindow("HALLO_WORLD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (GameManager::window == NULL) {
        printf("Dont creat window\n");
        return false;
    }

    GameManager::renderer = SDL_CreateRenderer(GameManager::window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (GameManager::renderer == NULL) {
        printf("Dont creat renderer\n");
        return false;
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// opengl系初期化？
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitGL(int argc, char *argv[])
{
    //gl系とglut系の初期化
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //二次元テクスチャを有効
    //glEnable(GL_TEXTURE_2D);

    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION);
    /* 変換行列の初期化 */
    glLoadIdentity();

    /* スクリーン上の表示領域をビューポートの大きさに比例させる */
    //glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGHT, WINDOW_HEIGHT, -1.0, 1.0);

    gluPerspective(30.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    glTranslated(0.0, 0.0, -5.0);

    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //GameManager::context = SDL_GL_CreateContext(window);
    /* Enable smooth shading */
    //glShadeModel(GL_SMOOTH);

    /* Set the background black */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* Depth buffer setup */
    //glClearDepth(1.0f);

    /* Enables Depth Testing */
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHT1);
    // glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    // glLightfv(GL_LIGHT1, GL_SPECULAR, green);

    //glEnable(GL_COLOR_MATERIAL);
    /* The Type Of Depth Test To Do */
    //glDepthFunc(GL_LEQUAL);

    /* Really Nice Perspective Calculations */
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 描画
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Render()
{

    //マニュピレーター
    glBegin(GL_LINES);
    for (int i = 0; i < 3; i++) {
        glColor4fv(manupilator_color[i]);
        glVertex3dv(manupilator_vertex[manupilator_edge[i][0]]);
        glVertex3dv(manupilator_vertex[manupilator_edge[i][1]]);
    }
    glEnd();

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

    glFlush();
}

void Clear()
{
    SDL_RenderClear(GameManager::renderer);
}
