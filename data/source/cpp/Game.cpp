//ゲームのメイン
#include "../header/game.h"
#include "../header/audio.h"
#include "../header/controller.h"
#include "../header/gamesystem.h"
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
bool InitSystem(int argc, char *argv[]);

void Render();
void Clear();

//*******************************************************************************************************************************************

float light0_position[4] = { 0.0, 1000.0, 0.0, 1.0 };
GLfloat light1pos[]      = { 5.0, 3.0, 0.0, 1.0 };

GLfloat white[]                 = { 1.0, 1.0, 1.0, 1.0 };
GLfloat green[]                 = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[]                   = { 0.8, 0.2, 0.2, 1.0 };
static const GLfloat lightamb[] = { 0.1f, 0.1f, 0.1f, 1.0f };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// メイン
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Window *GameManager::window;
SDL_Renderer *GameManager::renderer;
StaticShader shader;
int main(int argc, char *argv[])
{
    if (!InitSystem(argc, argv)) {
        printf("error init game system!\n");
        return -1;
    }

    shader = *new StaticShader(true);

    while (SDL_AtomicGet(&Controller_Maneger::atm) > 0 && Controller_Maneger::event.type != SDL_QUIT) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.start();

        GameSystem::SystemUpdate();
        glFlush();

        shader.stop();
        SDL_GL_SwapWindow(GameManager::window);
        SDL_Delay(4);
    }

    Clear();
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// システム初期化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitSystem(int argc, char *argv[])
{

    if (!InitWindow()) {
        printf("error init window\n");
        return false;
    }
    if (!InitGL(argc, argv)) {
        printf("error init gl\n");
        return false;
    }

    if (!GameSystem::InitGameSystem()) {
        printf("error init gamesystem\n");
        return false;
    }

    if (!Controller_Maneger::Init_Controller()) {
        printf("error laod controller\n");
        return false;
    }

    if (!Audio_Manager::Init_Audio()) {
        printf("error load audio\n");
        return false;
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ウィンドウ初期化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitWindow()
{
    //sdlの初期化
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK)) {
        printf("error sdlinit\n");
        return false;
    }
    //********************************
    //ディスプレイのwindow関係の初期化
    GameManager::window = SDL_CreateWindow("HELLO_WORLD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    /* 変換行列の初期化 */
    glLoadIdentity();

    /* Set the background black */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* Enables Depth Testing */
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    /**
 * 光源の環境光
 */
    float lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };

    /**
 * 光源の拡散光
 */
    float lightDiffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };

    /**
 * 光源の位置
 */
    float lightPos[] = { 0, 0, 2, 1 };
    //　Light0の環境光の設定
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

    //　Light0の拡散光の設定
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    //　Light0の場所の設定
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
    // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    /* Really Nice Perspective Calculations */
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clear()
{
    SDL_RenderClear(GameManager::renderer);
}
