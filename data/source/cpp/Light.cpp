#include "../header/light.h"

Light::Light(Vector3f position, Vector3f color)
{
}

Vector3f Light::getPosition()
{
    return position;
}

void Light::setPosition(Vector3f p)
{
    position = p;
}

Vector3f Light::getColor()
{
    return color;
}

void Light::setColor(Vector3f c)
{
    color = c;
}