#include "../header/game.h"
#include "../header/gamesystem.h"

#include "../header/audio.h"
#include "../header/controller.h"
#include "../header/object.h"
#include "../header/ui_image.h"

extern Player player;
Title::Title()
    : Scene()
{
}

GameMode Title::System()
{
    return gamemode_title;
}

void Title::Render()
{
    glRotated(0.05, 0, 1, 0);
    static const GLfloat diffuse[]  = { 0.6f, 0.1f, 0.1f, 1.0f };
    static const GLfloat specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
    player.Draw();
}