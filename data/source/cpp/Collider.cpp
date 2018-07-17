#include "../header/collider.h"
#include <cmath>

Sphere::Sphere()
{
}

Sphere::Sphere(Vector3f c, float arg)
{
    center = c;
    r      = arg;
}

Collider::Collider()
{
}

Collider::Collider(Sphere s[])
{
}

bool Collider::isCollision(Collider other)
{
    for (int i = 0; i < spheres.size(); i++) {
        for (int j = 0; j < other.spheres.size(); j++) {
            if ((spheres[i].center - other.spheres[j].center).magnitude_second_power() <= std::pow(spheres[i].r + other.spheres[j].r, 2.0)) {
                return true;
            }
        }
    }
    return false;
}

void Collider::MoveCollider(Vector3f v)
{
    for (int i = 0; i < spheres.size(); i++) {
        spheres[i].center = spheres[i].center + v;
    }
}