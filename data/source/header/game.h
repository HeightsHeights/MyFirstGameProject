//c++関係
#include <stdio.h>
#include <vector>

#define GL_GLEXT_PROTOTYPES 1

//sdl関係
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengles2.h>

//gl関係
#include <GL/gl.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//ゲームマネージャー関係
class GameManager {
public:
    static SDL_Window *window;
    static SDL_Renderer *renderer;

private:
};