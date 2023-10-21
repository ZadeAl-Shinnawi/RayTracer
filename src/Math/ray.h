/*
 * This class provides the concept of a ray. Similar to the Vector class, but
 * rays are defined as an origin and a direction.
 */

#pragma once

#include "vector3.h"

class Ray
{
public:
    // Default constructor.
    Ray() : m_origin(Point3()), m_direction(Vector3()), m_time(0.0f) {}

    // Stationary ray.
    Ray(const Point3& origin, const Vector3& direction) :
        m_origin(origin), m_direction(direction), m_time(0.0f) {}

    // Moving ray.
    Ray(const Point3& origin, const Vector3& direction, float time) :
        m_origin(origin), m_direction(direction), m_time(time) {}

    Point3 origin() const
    {
        return m_origin;
    }
    
    float time() const { return m_time; }

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
    // When to send the ray into the scene.
    float m_time;

    // Ray origin.
    Point3 m_origin;

    // Ray direction.
    Vector3 m_direction;
};
