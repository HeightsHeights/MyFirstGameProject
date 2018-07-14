#include "../header/toolkit.h"

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
