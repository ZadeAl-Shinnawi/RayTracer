/*
 *	This derived class contains information on the hittable, Sphere
 *  primitive which is defined by a center and a radius.
 */

#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

Sphere::Sphere() : center{0.0f, 0.0f, 0.0f}, radius(1.0f) {}

Sphere::Sphere(Point3 cen, float r) : center(cen), radius(r) {}

bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const
{
    Vec3 oc = r.origin() - center;

    // Calculate a, b, and c values to solve quadratic.
    float a = r.direction().lengthSquared();
    float halfB = dot(oc, r.direction());
    float c = oc.lengthSquared() - radius * radius;

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
    Vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);

    return true;
}