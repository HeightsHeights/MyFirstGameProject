#pragma once
#include "../header/vector.h"

class Light {
private:
    Vector3f position;
    Vector3f color;

public:
    Light(Vector3f position, Vector3f color);

    Vector3f getPosition();
    void setPosition(Vector3f p);
    Vector3f getColor();
    void setColor(Vector3f c);
};