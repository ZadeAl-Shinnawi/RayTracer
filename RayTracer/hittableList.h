/*
 *	This derived class contains information on a list of hittable primitives.
 */

#pragma once

#include <vector>
#include <memory>
#include "hittable.h"

class HittableList : public Hittable
{
public:
    // Default Constructor: Initializes vector components to 0.
    HittableList();

    // Constructor: Initializes hittable list with given objects.
    HittableList(std::shared_ptr<Hittable> object);

    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Clears all objects currently in the hittable list.
    inline void clear()
    {
        objects.clear();
    }

    // REQUIRES: Nothing.
    // MODIFIES: Objects.
    // EFFECTS:  Adds specified object to objects.
    inline void add(std::shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Checks whether or not any of the primitives
    //           in the hittable list were hit.
    virtual bool hit(
        const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

public:
    // Vector of hittable objects.
    std::vector<std::shared_ptr<Hittable>> objects;
};