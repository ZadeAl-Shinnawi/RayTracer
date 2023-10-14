#include "diffuse.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"

Diffuse::Diffuse(const Color& a) : albedo(a) {}

bool Diffuse::scatter(const Ray& inputRay, const HitRecord& rec,
                      Color& attenuation, Ray& scattered) const
{
    // Calculate light ray scatter direction.
    Vector3 scatterDirection = rec.normal + randUnitVector();

    // Catch degenerate scatter direction.
    if (scatterDirection.nearZero())
    {
        scatterDirection = rec.normal;
    }

    scattered = Ray(rec.p, scatterDirection);
    attenuation = albedo;

    return true;
}
