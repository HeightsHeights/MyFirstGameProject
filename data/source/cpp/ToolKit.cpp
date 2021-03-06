#include "../header/toolkit.h"
#include <stdlib.h>
#include <time.h>

void LookatVector(Vector3f direction)
{
    direction       = direction.normalize();
    Vector3f up     = *new Vector3f(0, 1, 0);
    Vector3f cross1 = Vector3f::cross(direction, up).normalize();
    Vector3f cross2 = Vector3f::cross(cross1, direction).normalize();

    float rotation[4][4] = { { cross1.x, cross1.y, cross1.z, 0 },
        { cross2.x, cross2.y, cross2.z, 0 },
        { direction.x, direction.y, direction.z, 0 },
        { 0, 0, 0, 1 } };

    glMultMatrixf(rotation[0]);
}
void LookatPoint(Vector3f loc, Vector3f point)
{
    LookatVector(point - loc);
}

void TranslateVector(Vector3f delta)
{
    glTranslated(delta.x, delta.y, delta.z);
}

Vector3f getNewSideVector(Vector3f forward)
{
    forward         = forward.normalize();
    Vector3f up     = *new Vector3f(0, 1, 0);
    Vector3f cross1 = Vector3f::cross(forward, up).normalize();
    return cross1;
}

Vector3f getNewUPVector(Vector3f forward)
{
    forward         = forward.normalize();
    Vector3f up     = *new Vector3f(0, 1, 0);
    Vector3f cross1 = Vector3f::cross(forward, up).normalize();
    Vector3f cross2 = Vector3f::cross(cross1, forward).normalize();
    return cross2;
}
void InitRand()
{
    srand((unsigned int)time(NULL));
}
int RandBetween(int min, int max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

bool IsBetween(float n, float min, float max)
{
    return min <= n && n <= max;
}

void printString(float x, float y, const char* str, int length)
{
    float z = -29.0f;
    glRasterPos3f(x, y, z);

    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}

void Colored(ColorType type)
{

    switch (type) {

    case CT_WHITE:
        glColor4d(1, 1, 1, 1);
        break;
    case CT_BLUE:
        glColor4d(0, 0, 1, 1);
        break;
    case CT_RED:
        glColor4d(1, 0, 0, 1);
        break;
    case CT_YELLLOW:
        glColor4d(1, 1, 0, 1);
        break;
    case CT_GREEN:
        glColor4d(0, 1, 0, 1);
        break;
    case CT_CYAN:
        glColor4d(0, 1, 1, 1);
        break;
    case CT_ORANGE:
        glColor4d(1, 0.27, 0, 1);
        break;
    case CT_PURPLE:
        glColor4d(1, 0, 1, 1);
        break;
    }
}