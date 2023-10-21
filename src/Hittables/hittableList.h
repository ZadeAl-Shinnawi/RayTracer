/*
 * This class provides functionality for a list of Hittable objects (useful
 * for implementing BVHs).
 */

#pragma once

#include "hittable.h"

#include <vector>
#include <memory>

#include "../Math/ray.h"
#include "../Math/interval.h"

class HittableList : public Hittable
{
public:
    // Default constructor.
    HittableList();

    // Initialization constructor.
    HittableList(std::shared_ptr<Hittable> object);

    // Clears all objects in the HittableList.
    inline void clear() { m_objects.clear(); }

    // Adds an object to the HittableList.
    inline void add(std::shared_ptr<Hittable> object)
    {
        m_objects.push_back(object);
    }

private:
    // Checks whether or not any of the primitives in the HittableList were
    // hit.
    bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;

    std::vector<std::shared_ptr<Hittable>> m_objects;
};
