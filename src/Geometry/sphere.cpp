#include <memory>
#include "sphere.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"
#include "../Materials/material.h"

Sphere::Sphere() : center{0.0f, 0.0f, 0.0f}, radius(1.0f) {}

Sphere::Sphere(Point3 center, float radius, std::shared_ptr<Material> matPtr) :
               center(center), radius(radius), matPtr(matPtr) {}

bool Sphere::hit(const Ray& r, const float tMin,
                 const float tMax, HitRecord& rec) const
{
    Vector3 oc = r.origin() - center;

    // Calculate a, b, and c values to solve quadratic.
    float a = r.direction().magnitudeSquared();
    float halfB = dot(oc, r.direction());
    float c = oc.magnitudeSquared() - radius * radius;

    // Calculate discriminant.
    float discriminant = halfB * halfB - a * c;

    // Ray did not hit sphere (negative discriminant).
    if (discriminant < 0.0f)
    {
        return false;
    }

    float sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (-halfB - sqrtd) / a;

    if (root < tMin || tMax < root)
    {
        root = (-halfB + sqrtd) / a;

        if (root < tMin || tMax < root)
        {
            return false;
        }
    }

    // Set HitRecord magnitude and intersection point.
    rec.t = root;
    rec.p = r.at(rec.t);

    // Negate normal, if necessary.
    Vector3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);

    // Set sphere material pointer.
    rec.matPtr = matPtr;

    return true;
}