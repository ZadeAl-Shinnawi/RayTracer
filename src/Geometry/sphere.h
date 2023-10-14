#pragma once

#include <memory>
#include "../Hittables/hittable.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Materials/material.h"

class Sphere : public Hittable
{
public:
    // Default Constructor.
    Sphere();

    // Initialization constructor.
    Sphere(Point3 center, float radius, std::shared_ptr<Material> matPtr);

    // Checks whether or not the sphere was hit.
    virtual bool hit(const Ray& r, const float tMin,
                     const float tMax, HitRecord& rec) const override;

public:
    Point3 m_center;

    float m_radius;

    std::shared_ptr<Material> m_matPtr;
};
