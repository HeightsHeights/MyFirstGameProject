#include <SDL2/SDL.h>

typedef enum {
    gamemode_title   = 0,
    gamemode_playing = 1,
    gamemode_pause   = 2,
    gamemode_end     = 3,
} GameMode;

class Scene {
private:
    virtual void Render();

public:
    Scene();
    virtual GameMode System();
};

class Title : public Scene {
private:
    void Render();

public:
    Title();
    GameMode System();
};

class MainGame : public Scene {
private:
    void Render();

public:
    MainGame();
    GameMode System();
};

class Pause : public Scene {
private:
    void Render();

public:
    Pause();
    GameMode System();
};