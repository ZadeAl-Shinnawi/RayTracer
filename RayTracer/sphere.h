/*
 *	This derived class contains information on the hittable, Sphere
 *  primitive which is defined by a center and a radius.
 */

#pragma once

#include "hittable.h"
#include "vec3.h"
#include "ray.h"

class Sphere : public Hittable
{
public:
    // Default Constructor: Initializes vector components to 0.
    Sphere();

    // Constructor: Initializes vector components to specified values.
    Sphere(Point3 cen, float r);

    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Checks whether or not the given sphere primitive was hit.
    virtual bool hit(
        const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

public:
    // Sphere center.
    Point3 center;

    // Sphere radius.
    float radius;
};