#include "sphere.h"

#include <memory>

#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"
#include "../Materials/material.h"

Sphere::Sphere() : m_center{0.0f, 0.0f, 0.0f}, m_radius(1.0f),
                   m_isMoving(false) {}

Sphere::Sphere(Point3 center, float radius, std::shared_ptr<Material> matPtr) :
               m_center(center), m_radius(radius), m_matPtr(matPtr),
               m_isMoving(false) {}

Sphere::Sphere(Point3 centerBegin, Point3 centerEnd, float radius,
               std::shared_ptr<Material> matPtr) :
               m_center(centerBegin), m_radius(radius), m_matPtr(matPtr),
               m_isMoving(true), m_centerVector(centerEnd - centerBegin) {}

bool Sphere::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    // Linearly interpolate from the starting center to the end center
    // according to time, where t = 0 gives the starting center, and t = 1
    // gives the end center.
    Point3 center = m_isMoving ? (m_center + r.time() * m_centerVector) :
                                  m_center;

    Vector3 oc = r.origin() - center;

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

    if (!ray_t.surrounds(root))
    {
        root = (-halfB + sqrtd) / a;

        if (!ray_t.surrounds(root))
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
