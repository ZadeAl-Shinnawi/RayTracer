#pragma once

#include "vector3.h"

class Ray
{
public:
    // Default constructor.
    Ray() : m_origin(Point3()), m_direction(Vector3()) {}

    // Initialization constructor.
    Ray(const Point3& origin, const Vector3& direction) :
        m_origin(origin), m_direction(direction) {}

    Point3 origin() const
    {
        return m_origin;
    }

    Vector3 direction() const
    {
        return m_direction;
    }

    // Returns the location components of the given ray.
    // P(t) = A + tB
    // P(t): Position
    // A:    Origin
    // t:    Magnitude
    // B:    Direction
    Point3 at(float t) const
    {
        return m_origin + t * m_direction;
    }

private:
    // Ray origin.
    Point3 m_origin;

    // Ray direction.
    Vector3 m_direction;
};
