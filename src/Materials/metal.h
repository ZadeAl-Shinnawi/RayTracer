/*
 * This class represents a metal material which reflects most light rays.
 */

#pragma once

#include "material.h"

#include "../Hittables/hittable.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/color.h"

class Metal : public Material
{
public:
    // Default constructor.
    Metal(const Color& albedo, float fuzz);

    // Scatters light rays according to metal surfaces.
    virtual bool scatter(const Ray& inputRay, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const override;

private:
    float m_fuzz;
    Color m_albedo;
};
