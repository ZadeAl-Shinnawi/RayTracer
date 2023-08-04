#include "glass.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"
#include <cmath>

Glass::Glass(float refractionIndex) : ir(refractionIndex) {}

bool Glass::scatter(const Ray& inputRay, const HitRecord& rec,
                    Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0f, 1.0f, 1.0f);

    // Calculate refraction ratio.
    float refractionRatio = rec.frontFace ? (1.0f / ir) : ir;

    Vector3 unitDirection = unitVector(inputRay.direction());

    float cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0f);
    float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0f;
    Vector3 direction;

    if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomFloat())
    {
        direction = reflect(unitDirection, rec.normal);
    }
    else
    {
        direction = refract(unitDirection, rec.normal, refractionRatio);
    }

    scattered = Ray(rec.p, direction);

    return true;
}

float Glass::reflectance(const float cosine, const float refIdx)
{
    // Use Schlick's approximation for reflectance.
    float r0 = (1.0f - refIdx) / (1.0f + refIdx);
    r0 = r0 * r0;

    return r0 + (1.0f - r0) * powf((1.0f - cosine), 5);
}