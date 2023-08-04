#pragma once

#include <memory>
#include "../Math/vector3.h"
#include "../Math/ray.h"

class Material;

struct HitRecord
{
    // Intersection point.
    Point3 p;

    Vector3 normal;

    // Ray direction magnitude.
    float t;

    // Pointer to primitive material type.
    std::shared_ptr<Material> matPtr;

    // Front (or back) face of general primitive.
    bool frontFace;

    // Negates the surface normal direction, if required.
    inline void setFaceNormal(const Ray& r, const Vector3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    // Checks whether or not the general primitive was hit.
    virtual bool hit(const Ray& r, const float tMin,
                     const float tMax, HitRecord& rec) const = 0;
};