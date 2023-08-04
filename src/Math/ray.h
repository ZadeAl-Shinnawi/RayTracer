#pragma once

#include "vector3.h"

class Ray
{
public:
    // Default constructor.
    Ray() : orig(Point3()), dir(Vector3()) {}

    // Initialization constructor.
    Ray(const Point3& origin, const Vector3& direction) :
        orig(origin), dir(direction) {}

    Point3 origin() const
    {
        return orig;
    }

    Vector3 direction() const
    {
        return dir;
    }

    // Returns the location components of the given ray.
    // P(t) = A + tB
    // P(t): Position
    // A:    Origin
    // t:    Magnitude
    // B:    Direction
    Point3 at(float t) const
    {
        return orig + t * dir;
    }

private:
    // Ray origin.
    Point3 orig;

    // Ray direction.
    Vector3 dir;
};