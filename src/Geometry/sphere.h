/*
 * This class represents a spherical Hittable object and allows spheres to be
 * represented in the final scene rendering.
 */

#pragma once

#include <memory>

#include "../Materials/material.h"
#include "../Hittables/hittable.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/interval.h"

class Sphere : public Hittable
{
public:
    // Default constructor.
    Sphere();

    // Stationary sphere.
    Sphere(Point3 center, float radius, std::shared_ptr<Material> matPtr);

    // Moving sphere.
    Sphere(Point3 centerBegin, Point3 centerEnd, float radius,
           std::shared_ptr<Material> matPtr);

    // Checks whether or not the sphere was hit.
    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const
                                                                   override;

private:
    bool m_isMoving;
    float m_radius;
    Point3 m_center;
    Vector3 m_centerVector;

    // Material pointer.
    std::shared_ptr<Material> m_matPtr;
};
