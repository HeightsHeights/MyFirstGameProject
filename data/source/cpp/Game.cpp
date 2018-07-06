//ゲームのメイン
#include "../header/game.h"
#include "../header/rawmodel.h"

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

GLdouble vertex[][3] = {
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0}};

int face[][4] = {
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {5, 4, 7, 6},
    {4, 0, 3, 7},
    {4, 5, 1, 0},
    {3, 2, 6, 7}};

GLdouble color[][3] = {
    {1.0, 0.0, 0.0}, /* 赤 */
    {0.0, 1.0, 0.0}, /* 緑 */
    {0.0, 0.0, 1.0}, /* 青 */
    {1.0, 1.0, 0.0}, /* 黄 */
    {1.0, 0.0, 1.0}, /* マゼンタ */
    {0.0, 1.0, 1.0}  /* シアン 　*/
};

GLdouble normal[][3] = {
    {0.0, 0.0, -1.0},
    {1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {-1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 1.0, 0.0}};

GLfloat light0pos[] = {0.0, 3.0, 5.0, 1.0};
GLfloat light1pos[] = {5.0, 3.0, 0.0, 1.0};

GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat red[] = {0.8, 0.2, 0.2, 1.0};

OBJMESH mesh;

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
        //glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Draw();

        //glDisable(GL_DEPTH_TEST);
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

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

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

    mesh.LoadFile("data/data_3d/plane.obj");

    for (int i = 0; i < mesh.VERTICES.size() / 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("x:%fy:%fz:%f\n", mesh.VERTICES[i + j].position.x, mesh.VERTICES[i + j].position.y, mesh.VERTICES[i + j].position.z);
    }

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

    glCullFace(GL_FRONT);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);

    /* The Type Of Depth Test To Do */
    //glDepthFunc(GL_LEQUAL);

    /* Really Nice Perspective Calculations */
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return true;
}

void Draw()
{

    mesh.Draw();

    //https://stackoverflow.com/questions/19986570/interleaved-vbo-with-coords-normals-and-color
    GLuint vao, vbo, ib;

    //make vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //make vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, mesh.VERTICES.size() * sizeof(OBJVERTEX), &mesh.VERTICES[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.INDICES.size() * sizeof(unsigned int), &mesh.INDICES[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVERTEX), (void *)0); //send positions on pipe 0
    /*
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVERTEX), (void *)(sizeof(float) * 3)); //send normals on pipe 1
    */
    /*
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVERTEX), (void *)(6 * sizeof(float)));
    */
    //glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glDrawElements(GL_TRIANGLES, mesh.INDICES.size(), GL_UNSIGNED_INT, 0);

    /*
    glRotated(0.01, 0, 1, 0);
    for (int i = 0; i < 36; i++)
    {
        glDrawArrays(GL_LINE_LOOP, i, 3);
    }
    */
    glBegin(GL_LINES);
    for (int i = 0; i < 3; i++)
    {
        glColor4fv(manupilator_color[i]);
        glVertex3dv(manupilator_vertex[manupilator_edge[i][0]]);
        glVertex3dv(manupilator_vertex[manupilator_edge[i][1]]);
    }
    glEnd();

    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

    /*
    glRotated(0.1, 0, 1, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    glBegin(GL_QUADS);
    for (int j = 0; j < 6; ++j)
    {
        glNormal3dv(normal[j]);
        for (int i = 0; i < 4; ++i)
        {
            //glColor3dv(color[j]);
            glVertex3dv(vertex[face[j][i]]);
        }
    }
    glEnd();
    */
    /*
    glRotated(0.01, 0, 1, 0);
    for (int i = 0; i < mesh.VERTICES.size(); i += 3)
    {
        glBegin(GL_TRIANGLES);

        glVertex3f(mesh.VERTICES[i + 0].position.x, mesh.VERTICES[i + 0].position.y, mesh.VERTICES[i + 0].position.z);
        glVertex3f(mesh.VERTICES[i + 1].position.x, mesh.VERTICES[i + 1].position.y, mesh.VERTICES[i + 1].position.z);
        glVertex3f(mesh.VERTICES[i + 2].position.x, mesh.VERTICES[i + 2].position.y, mesh.VERTICES[i + 2].position.z);

        glEnd();
    }
    */
    glFlush();
}

void Clear()
{
    SDL_RenderClear(GameManager::renderer);
}
