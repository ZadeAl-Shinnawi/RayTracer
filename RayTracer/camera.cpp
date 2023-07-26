/*
 *	This class contains information on the Camera object which is used
 *  to construct a virtual camera with all of the necessary properties
 *  required to accurately simulate a real-world, visual representation
 *  of the primitives in a given scene or world.
 */

#include "camera.h"
#include "vec3.h"
#include "ray.h"

Camera::Camera() :
    aspectRatio(16.0f / 9.0f), viewportHeight(2.0f),
    viewportWidth(aspectRatio * viewportHeight), focalLength(1.0f),
    horizontal(Vec3(viewportWidth, 0.0f, 0.0f)),
    vertical(Vec3(0.0f, viewportHeight, 0.0f)), origin(Point3()),
    lowerLeftCorner(
        origin - (horizontal / 2.0f) - (vertical / 2.0f) -
        Vec3(0.0f, 0.0f, focalLength)) {}

Ray Camera::getRay(float u, float v) const
{
    return Ray(origin, lowerLeftCorner + (u * horizontal) + (v * vertical) - origin);
}