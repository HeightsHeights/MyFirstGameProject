//ゲームのメイン
#include "../header/game.h"

//window系の初期化
bool InitWindow();
//gl系の初期化
bool InitGL(int argc, char *argv[]);
//音楽系の初期化
bool InitAudio();
//システム全体の初期化
bool InitSystem();

bool LoadOBJ(const char *path, std::vector<float> &out_vertices, std::vector<float> &out_uvs, std::vector<float> &out_noemals);

void Draw();
void Clear();

//*******************************************************************************************************************************************

GLdouble manupilator_vertex[][3] = {
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}};
int manupilator_edge[][2] = {
    {0, 1},
    {0, 2},
    {0, 3}};
GLfloat manupilator_color[][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f}};

//*******************************************************************************************************************************************

int main(int argc, char *argv[])
{
    if (!InitWindow())
    {
        printf("error initwindow\n");
        return -1;
    }
    if (!InitGL(argc, argv))
    {
        printf("error initgl\n");
        return -1;
    }

    SDL_Event event;
    while (event.type != SDL_QUIT)
    {
        SDL_PollEvent(&event);
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        Draw();

        SDL_GL_SwapWindow(GameManager::window);
    }

    Clear();
    return 0;
}

bool InitWindow()
{
    //sdlの初期化
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("error sdlinit\n");
        return false;
    }
    //********************************
    //ディスプレイのwindow関係の初期化
    GameManager::window = SDL_CreateWindow("HALLO_WORLD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (GameManager::window == NULL)
    {
        printf("Dont creat window\n");
        return false;
    }

    GameManager::renderer = SDL_CreateRenderer(GameManager::window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (GameManager::renderer == NULL)
    {
        printf("Dont creat renderer\n");
        return false;
    }
    return true;
}
bool InitGL(int argc, char *argv[])
{
    //gl系とglut系の初期化
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    //二次元テクスチャを有効
    glEnable(GL_TEXTURE_2D);

    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);



  glMatrixMode(GL_PROJECTION);
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
    //glEnable(GL_DEPTH_TEST);

    /* The Type Of Depth Test To Do */
    //glDepthFunc(GL_LEQUAL);

    /* Really Nice Perspective Calculations */
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return true;
}

bool LoadOBJ(const char *path, std::vector<float> &out_vertices, std::vector<float> &out_uvs, std::vector<float> &out_noemals)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("file open error\n");
        return false;
    }

    while (1)
    {
        char lineHeHeader[128];
        int res = fscanf(file, "%s", lineHeHeader);
        if (res == EOF)
        {
            break;
        }
        if (strcmp(lineHeHeader, "v") == 0)
        {
        }
        else if (strcmp(lineHeHeader, "vt") == 0)
        {
        }
        else if (strcmp(lineHeHeader, "vn") == 0)
        {
        }
        else if (strcmp(lineHeHeader, "f") == 0)
        {
        }
    }
}

void Draw()
{

    glBegin(GL_LINES);
    for (int i = 0; i < 3; i++)
    {
        glColor4fv(manupilator_color[i]);
        glVertex3dv(manupilator_vertex[manupilator_edge[i][0]]);
        glVertex3dv(manupilator_vertex[manupilator_edge[i][1]]);
    }
    glEnd();

    glFlush();
}

void Clear()
{
    SDL_RenderClear(GameManager::renderer);
}
