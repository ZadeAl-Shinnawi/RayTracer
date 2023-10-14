#pragma once

#include "../Math/vector3.h"
#include "../Math/ray.h"

class Camera
{
public:
    // Initialization constructor.
    Camera(Point3 lookFrom, Point3 lookAt, Vector3 viewUp,
           float aspectRatio, float verticalFOV, float aperture,
           float focusDistance);

    // Returns the ray located at the specified screen coordinate values.
    Ray getRay(float s, float t) const;

private:
    // In degrees.
    // Increasing this gives a wider camera angle view as if you are zoomed out
    // or viewing the scene from further back
    float m_verticalFOV;

    // Viewport width : length ratio.
    float m_aspectRatio;

    // Vertical FOV in degrees.
    float m_theta;

    // Half of the FOV height.
    float m_fovHeight;

    float m_viewportHeight;

    float m_viewportWidth;

    // Camera lens light array amount.
    // Increasing this "widens" the lens and results
    // in blurrier background objects.
    float m_aperture;

    // Everything within this distance will be perfectly in focus.
    float m_focusDist;

    float m_lensRadius;

    // Camera origin.
    Point3 m_lookFrom;

    // Camera direction.
    Point3 m_lookAt;
    
    // Camera up direction vector (0, 1, 0).
    Vector3 m_viewUp;

    // Camera z direction vector.
    Vector3 m_w;

    // Camera x direction vector.
    Vector3 m_u;
    
    // Camera v direction vector.
    Vector3 m_v;

    // Camera origin.
    Point3 m_origin;

    // Horizontal window vector.
    Vector3 m_horizontal;

    // Vertical window vector.
    Vector3 m_vertical;

    // Lower, left corner of viewing plane.
    Point3 m_lowerLeftCorner;
};
