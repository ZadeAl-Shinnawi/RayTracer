#pragma once

#include "material.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"

class Diffuse : public Material
{
public:
    // Default constructor.
    Diffuse(const Color& a);

    // Scatters light rays equally in all directions.
    virtual bool scatter(const Ray& inputRay, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const override;

    Color albedo;
};
