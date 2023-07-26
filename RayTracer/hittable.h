/*
 *	This is an abstract class that contains information on a general
 *  Hittable object which is derived from by multiple other, more
 *  specific, types of hittable (by rays) primitives.
 */

#pragma once

#include "vec3.h"
#include "ray.h"

struct HitRecord
{
    // Intersection point.
    Point3 p;

    // Surface normal.
    Vec3 normal;

    // Ray direction magnitude.
    float t;

    // Front (or back) face of general primitive.
    bool frontFace;

    // REQUIRES: Nothing.
    // MODIFIES: (Possibly) front face.
    // EFFECTS:  Negates the surface normal direction, if required.
    inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Checks whether or not the general primitive was hit.
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec)
            const = 0;
};