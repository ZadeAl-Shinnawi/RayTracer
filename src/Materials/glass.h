#pragma once

#include "material.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Hittables/hittable.h"

class Glass : public Material
{
public:
    // Default constructor.
    Glass(float refractionIndex);

    // Refracts/reflects light rays.
    virtual bool scatter(const Ray& inputRay, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const override;

    // Index of refraction.
    float ir;

private:
    // Returns a float with reflectivity that varies with angle.
    static float reflectance(const float cosine, const float refIdx);
};
