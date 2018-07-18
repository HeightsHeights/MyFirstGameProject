
#include "../header/gamesystem.h"
#include "../header/shader.h"
#include "../header/toolkit.h"
extern StaticShader shader;
Title::Title()
    : Scene()
{
    player = *new Player("data/data_3d/player.obj");
}

void Title::InitScene()
{
    Mix_PlayMusic(Audio_Manager::music[BGM_Title], -1);
}

GameMode Title::System()
{
    if (Controller_Maneger::Joystics[0].state.button[B_SHOOT_DICITION]) {
        Mix_FadeOutMusic(1000);
        return gamemode_main;
    } else if (Controller_Maneger::Joystics[0].state.button[B_PAUSE])
        return gamemode_end;
    else
        return gamemode_title;
}
void Title::Render()
{
    glLoadIdentity();
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glRotated(player.rotation.y += 0.01, 0, 1, 0);
    Colored(player.color_type);
    player.Draw();
    glPopMatrix();

    shader.stop();
    glPushMatrix();
    glColor3d(1, 0.5, 1);
    printString(-23, -10, "PRESS 6 KEY!", 12);
    glPopMatrix();
    shader.start();
    //glutSolidTeapot(2);
}