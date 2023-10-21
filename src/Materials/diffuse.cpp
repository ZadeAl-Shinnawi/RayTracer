#include "diffuse.h"

#include "../Hittables/hittable.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/color.h"

Diffuse::Diffuse(const Color& albedo) : m_albedo(albedo) {}

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

    scattered = Ray(rec.p, scatterDirection, inputRay.time());
    attenuation = m_albedo;

    return true;
}
