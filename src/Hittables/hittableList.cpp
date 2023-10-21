#include "hittable.h"
#include "hittableList.h"

#include "../Math/interval.h"
#include "../Math/ray.h"

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
    add(object);
}

bool HittableList::hit(const Ray& r, Interval interval, HitRecord& rec) const
{
    HitRecord tempRec;

    bool wasHit = false;
    float closestSoFar = interval.max;

    // Iterate through all objects in the HittableList.
    for (const auto& object : m_objects)
    {
        // Check if the current object was hit.
        if (object->hit(r, Interval(interval.min, closestSoFar), tempRec))
        {
            wasHit = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return wasHit;
}
