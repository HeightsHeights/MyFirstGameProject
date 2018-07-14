#pragma once
#include "../header/vector.h"
#include <vector>
class Sphere {
private:
public:
    Sphere();
    Sphere(Vector3f c, float r);
    Vector3f center;
    float r;
};

class Collider {
private:
public:
    Collider();
    Collider(Sphere s[]);
    std::vector<Sphere> spheres;
    bool isCollision(Collider other);
    void MoveCollider(Vector3f v);
};