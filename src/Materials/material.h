/*
 * This is an abstract class that represents a generic material.
 */

#pragma once

#include "../Math/vector3.h"
#include "../Math/ray.h"

// Forward declaration.
struct HitRecord;

class Material
{
public:
    // Scatters light rays according to the material.
    virtual bool scatter(const Ray& inputRay, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const = 0;
};
