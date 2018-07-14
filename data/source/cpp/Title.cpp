
#include "../header/gamesystem.h"

Title::Title()
    : Scene()
{
    player = *new Player("data/data_3d/untitled.obj");
}

void Title::InitScene()
{
}

GameMode Title::System()
{
    if (Controller_Maneger::Joystics[0].state.button_shoot_decition)
        return gamemode_main;
    else if (Controller_Maneger::Joystics[0].state.button_pause)
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
    player.Draw();
    glPopMatrix();
}