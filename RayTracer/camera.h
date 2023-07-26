/*
 *	This class contains information on the Camera object which is used
 *  to construct a virtual camera with all of the necessary properties
 *  required to accurately simulate a real-world, visual representation
 *  of the primitives in a given scene or world.
 */

#pragma once

#include "vec3.h"
#include "ray.h"

class Camera
{
public:
    // Default Constructor: Initializes camera components to set values.
    Camera();

    // REQUIRES: Nothing.
    // MODIFIES: Nothing.
    // EFFECTS:  Returns the ray located at the specified values.
    Ray getRay(float u, float v) const;

private:
    // Window size ratio.
    float aspectRatio;

    // Window height.
    float viewportHeight;

    // Window width.
    float viewportWidth;

    // Distance from camera to viewing plane.
    float focalLength;

    // Horizontal window vector.
    Vec3 horizontal;

    // Vertical window vector.
    Vec3 vertical;

    // Camera origin.
    Point3 origin;

    // Lower, left corner of viewing plane.
    Point3 lowerLeftCorner;
};