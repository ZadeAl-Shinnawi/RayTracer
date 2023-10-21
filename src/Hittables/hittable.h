/*
 * This class provides an abstract, "Hittable" object (i.e. can be intersected
 * with a ray) as well as a HitRecord struct to package intersection
 * information.
 */

#pragma once

#include <memory>

#include "../Materials/material.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/interval.h"

class Hittable
{
public:
    // Checks whether or not the general primitive was hit.
    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

struct HitRecord
{
    // Front (or back) face of general primitive.
    bool frontFace;

    // Ray direction magnitude.
    float t;

    // Intersection point.
    Point3 p;

    Vector3 normal;

    // Pointer to primitive material type.
    std::shared_ptr<Material> matPtr;

    // Negates the surface normal direction, if required.
    inline void setFaceNormal(const Ray& r, const Vector3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
