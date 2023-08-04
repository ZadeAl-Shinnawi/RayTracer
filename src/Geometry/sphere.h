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
    Sphere(Point3 cen, float r, std::shared_ptr<Material> mat);

    // Checks whether or not the sphere was hit.
    virtual bool hit(const Ray& r, const float tMin,
                     const float tMax, HitRecord& rec) const override;

public:
    Point3 center;

    float radius;

    std::shared_ptr<Material> matPtr;
};