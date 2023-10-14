#include "hittableList.h"
#include "../Math/ray.h"

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
    add(object);
}

bool HittableList::hit(const Ray& r, const float tMin,
                       const float tMax, HitRecord& rec) const
{
    HitRecord tempRec;
    bool wasHit = false;
    float closestSoFar = tMax;

    // Iterate through all objects in hittable list.
    for (const auto& object : objects)
    {
        // Check if current object was hit.
        if (object->hit(r, tMin, closestSoFar, tempRec))
        {
            wasHit = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return wasHit;
}
