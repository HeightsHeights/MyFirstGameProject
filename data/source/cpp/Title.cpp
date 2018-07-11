
#include "../header/gamesystem.h"

Title::Title()
    : Scene()
{
    player   = *new Player("data/data_3d/untitled.obj");
    enemy[0] = *new Enemy("data/data_3d/ufo plane free.obj");
    point    = *new Vector3f(0, 0, 30);
    front    = *new Vector3f(0, 0, 1);
}
Vector3f location = *new Vector3f(0, 0, 0);
GameMode Title::System()
{

    location.x += Controller_Maneger::Joystics[0].state.Lx_axis * 0.1;
    location.y -= Controller_Maneger::Joystics[0].state.Ly_axis * 0.1;
    point.x = Controller_Maneger::Joystics[0].state.Rx_axis * 30;
    point.y = Controller_Maneger::Joystics[0].state.Ry_axis * 30;
    return gamemode_title;
}

void Title::Render()
{

    glLoadIdentity();
    
    gluPerspective(30.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);

    gluLookAt(0.0, 4.0, -50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
glPushMatrix();
    /*
    Vector3f delta = (point - front).normalize();
    Vector3f z     = Vector3f::cross(*new Vector3f(0, 1, 0), delta).normalize();
    Vector3f y     = Vector3f::cross(z, delta).normalize();

    printf("%f\n", (location - point).BetweenAngleDegree(front));
    glRotated((location - point).BetweenAngleDegree(front), y.x, y.y, y.z);
    */
    point = point;

    glRotated(180, 0, 1, 0);

    if (point.x >= 0) {
        glRotated(front.BetweenAngleDegree(*new Vector3f(point.x, 0, point.z)), 0, 1, 0);
    } else {
        glRotated(-front.BetweenAngleDegree(*new Vector3f(point.x, 0, point.z)), 0, 1, 0);
    }
    if (point.y >= 0) {
        glRotated(front.BetweenAngleDegree(*new Vector3f(0, point.y, point.z)), 1, 0, 0);
    } else {
        glRotated(-front.BetweenAngleDegree(*new Vector3f(0, point.y, point.z)), 1, 0, 0);
    }

    glTranslated(location.x, location.y, 0);

    player.Draw();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.3, 0.3, 0.3);
    enemy[0].Draw();
    glPopMatrix();
    
}