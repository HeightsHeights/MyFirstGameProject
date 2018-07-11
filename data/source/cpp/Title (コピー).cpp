
#include "../header/gamesystem.h"

Title::Title()
    : Scene()
{
    player = *new Player("data/data_3d/untitled.obj");
    point  = *new Vector3f(0, 0, 0);
    front  = *new Vector3f(0, 0, 1);
}

GameMode Title::System()
{

    point.x = Controller_Maneger::Joystics[0].state.Rx_axis;
    point.z = Controller_Maneger::Joystics[0].state.Ry_axis;
    return gamemode_title;
}

void Title::Render()
{

    glLoadIdentity();
    gluPerspective(30.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    glTranslated(0.0, 0.0, -5.0);
    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    Vector3f location = *new Vector3f(0, 0, -5.0);

    Vector3f delta = (point - front).normalize();
    Vector3f z     = Vector3f::cross(*new Vector3f(0, 1, 0), delta).normalize();
    Vector3f y     = Vector3f::cross(z, delta).normalize();

    printf("%f\n", front.BetweenAngleDegree(location - point));
    glRotated(front.BetweenAngleDegree(location - point), y.x, y.y, y.z);
    //player.forward.Rotate(*new Vector3f(0, 1, 0), 0.05);
    // static const GLfloat diffuse[]  = { 0.6f, 0.1f, 0.1f, 1.0f };
    // static const GLfloat specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    // glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
    player.Draw();
}