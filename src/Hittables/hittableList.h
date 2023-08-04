#pragma once

#include <vector>
#include <memory>
#include "hittable.h"
#include "../Math/ray.h"

class HittableList : public Hittable
{
public:
    // Default constructor.
    HittableList();

    // Initialization constructor.
    HittableList(std::shared_ptr<Hittable> object);

    void clear()
    {
        objects.clear();
    }

    void add(std::shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    // Checks whether or not any of the primitives
    // in the hittable list were hit.
    virtual bool hit(const Ray& r, const float tMin,
                     const float tMax, HitRecord& rec) const override;

public:
    std::vector<std::shared_ptr<Hittable>> objects;
};