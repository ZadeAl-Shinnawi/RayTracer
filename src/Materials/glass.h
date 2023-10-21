/*
 * This class represents a glass material which reflects light rays equal t
 * the angle of incidence.
 */

#pragma once

#include "material.h"

#include "../Hittables/hittable.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/color.h"

class Glass : public Material
{
public:
    // Default constructor.
    Glass(float refractionIndex);

    // Refracts/reflects light rays.
    virtual bool scatter(const Ray& inputRay, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const override;

private:
    // Index of refraction.
    float m_ir;

    // Returns a float with reflectivity that varies with angle.
    static float reflectance(const float cosine, const float refIdx);
};
