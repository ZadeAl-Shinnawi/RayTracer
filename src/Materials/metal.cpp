#include "metal.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"

Metal::Metal(const Color& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(const Ray& inputRay, const HitRecord& rec,
                    Color& attenuation, Ray& scattered) const
{
    // Calculate light ray scatter direction.
    Vector3 reflected = reflect(unitVector(inputRay.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * randUnitSphereVector());
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
}
