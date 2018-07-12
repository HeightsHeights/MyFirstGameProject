
#include "../header/gamesystem.h"
#include "../header/toolkit.h"

Title::Title()
    : Scene()
{
    player   = *new Player("data/data_3d/untitled.obj");
    enemy[0] = *new Enemy("data/data_3d/pointer.obj");
    point    = *new Vector3f(0, 0, 30);
    front    = *new Vector3f(0, 0, 1);
}
Vector3f location = *new Vector3f(0, 0, 0);
GameMode Title::System()
{

    point.x = location.x -= Controller_Maneger::Joystics[0].state.Lx_axis * 0.1;
    point.y = location.y -= Controller_Maneger::Joystics[0].state.Ly_axis * 0.1;
    point.x -= Controller_Maneger::Joystics[0].state.Rx_axis * 30;
    point.y -= Controller_Maneger::Joystics[0].state.Ry_axis * 30;
    if (!Controller_Maneger::Joystics[0].state.button_pause)
        return gamemode_title;
    else
        gamemode_end;
}

void Title::Render()
{

    glLoadIdentity();

    gluPerspective(30.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(0.0, 0.0, -30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();

    glTranslated(location.x, location.y, 0);
    LookatPoint(location, point);
    player.Draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(point.x, point.y, point.z);
    LookatPoint(point, location);
    enemy[0].Draw();
    glPopMatrix();
}
