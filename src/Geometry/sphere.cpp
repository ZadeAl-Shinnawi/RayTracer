#include <memory>
#include "sphere.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"
#include "../Materials/material.h"

Sphere::Sphere() : m_center{0.0f, 0.0f, 0.0f}, m_radius(1.0f) {}

Sphere::Sphere(Point3 center, float radius, std::shared_ptr<Material> matPtr) :
               m_center(center), m_radius(radius), m_matPtr(matPtr) {}

bool Sphere::hit(const Ray& r, const float tMin,
                 const float tMax, HitRecord& rec) const
{
    Vector3 oc = r.origin() - m_center;

    // Calculate a, b, and c values to solve quadratic.
    float a = r.direction().magnitudeSquared();
    float halfB = dot(oc, r.direction());
    float c = oc.magnitudeSquared() - m_radius * m_radius;

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
    Vector3 outwardNormal = (rec.p - m_center) / m_radius;
    rec.setFaceNormal(r, outwardNormal);

    // Set sphere material pointer.
    rec.matPtr = m_matPtr;

    return true;
}
