#pragma once

#include "../Math/vector3.h"
#include "../Math/ray.h"

class Camera
{
public:
    // Initialization constructor.
    Camera(Point3 lookFrom, Point3 lookAt, Vector3 viewUp, float aspectRatio,
           float verticalFOV, float aperture, float focusDistance);

    // Returns the ray located at the specified screen coordinate values.
    Ray getRay(float s, float t) const;

private:
    // In degrees.
    // Increasing this gives a wider camera angle view as if you are zoomed out
    // or viewing the scene from further back
    float verticalFOV;

    // Viewport width : length ratio.
    float aspectRatio;

    // Vertical FOV in degrees.
    float theta;

    // Half of the FOV height.
    float h;

    float viewportHeight;

    float viewportWidth;

    // Camera lens light array amount.
    // Increasing this "widens" the lens and results
    // in blurrier background objects.
    float aperture;

    // Everything within this distance will be perfectly in focus.
    float focusDist;

    float lensRadius;

    // Camera origin.
    Point3 lookFrom;

    // Camera direction.
    Point3 lookAt;
    
    // Camera up direction vector (0, 1, 0).
    Vector3 viewUp;

    // Camera z direction vector.
    Vector3 w;

    // Camera x direction vector.
    Vector3 u;
    
    // Camera v direction vector.
    Vector3 v;

    // Camera origin.
    Point3 origin;

    // Horizontal window vector.
    Vector3 horizontal;

    // Vertical window vector.
    Vector3 vertical;

    // Lower, left corner of viewing plane.
    Point3 lowerLeftCorner;
};