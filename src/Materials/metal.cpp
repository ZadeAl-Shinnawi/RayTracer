#include "metal.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"

Metal::Metal(const Color& albedo, float fuzz) : m_albedo(albedo),
                                                m_fuzz(fuzz < 1.0f ? fuzz :
                                                       1.0f) {}

bool Metal::scatter(const Ray& inputRay, const HitRecord& rec,
                    Color& attenuation, Ray& scattered) const
{
    // Calculate light ray scatter direction.
    Vector3 reflected = reflect(unitVector(inputRay.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + m_fuzz * randUnitSphereVector(),
                    inputRay.time());

    attenuation = m_albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
}
