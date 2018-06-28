//c++関係
#include <stdio.h>
#include <vector>

//sdl関係
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//gl関係
#include <GL/gl.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//ゲームマネージャー関係
class GameManager
{
public:
  static SDL_Window *window;
  static SDL_Renderer *renderer;
  static SDL_GLContext context;

private:
};
SDL_Window *GameManager::window;
SDL_Renderer *GameManager::renderer;
SDL_GLContext GameManager::context;