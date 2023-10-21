/*
 * This class represents a diffuse or Lambertian or matte material which
 * reflects light equally in all directions.
 */

#pragma once

#include "material.h"

#include "../Hittables/hittable.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/color.h"

class Diffuse : public Material
{
public:
    // Default constructor.
    Diffuse(const Color& albedo);

    // Scatters light rays equally in all directions.
    virtual bool scatter(const Ray& inputRay, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const override;
private:
    Color m_albedo;
};
