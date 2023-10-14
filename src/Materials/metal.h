#pragma once

#include "material.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"

class Metal : public Material
{
public:
    // Default constructor.
    Metal(const Color& a, float f);

    // Scatters light rays according to metal surfaces.
    virtual bool scatter(const Ray& inputRay, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const override;

    Color albedo;
    float fuzz;
};
