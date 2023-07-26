/*
 *	This class contains information on the Ray object which consists
 *  of an origin (a 3D point in space) and a direction.
 */

#pragma once

class Ray
{
public:
    // Default Constructor: Initializes ray components to 0.
    Ray() : orig(Point3()), dir(Vec3()) {}

    // Constructor: Initializes ray components to specified values.
    Ray(const Point3& origin, const Vec3& direction) :
        orig(origin), dir(direction) {}

    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Returns the origin components of the given ray.
    Point3 origin() const
    {
        return orig;
    }

    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Returns the direction components of the given ray.
    Vec3 direction() const
    {
        return dir;
    }

    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Returns the location components of the given ray.
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
    Vec3 dir;
};