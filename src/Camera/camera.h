/*
 * This class provides the necessary functionality to set up a virtual camera,
 * cast rays for rendering, and capture scenes.
 */

#pragma once

#include "../Math/vector3.h"
#include "../Hittables/hittable.h"

class Camera
{
public:
    // Initialization constructor.
    Camera(int imageWidth, int imageHeight, int samplesPerPixel, int maxDepth,
           float aspectRatio, float verticalFOV, float defocusAngle,
           float focusDistance, Point3 lookFrom, Point3 lookAt,
           Vector3 upVector);

    // Outputs all of the image's RGB values for each pixel to std::cout
    // (a PPM file) and continuously displays the number of lines left to
    // render in the console.
    void render(const Hittable& world) const;

private:
    // Rendered image width in pixels.
    int m_imageWidth;

    // Rendered image height in pixels.
    int m_imageHeight;

    // Number of rays to cast per pixel.
    int m_samplesPerPixel;

    // Maximum number of bounces per Ray into the scene.
    int m_maxDepth;

    // Ratio = Image width : Image height.
    float m_aspectRatio;

    // Vertical field of view angle.
    float m_verticalFOV;

    //  Ray angle variation through each pixel (used for motion blur).
    float m_defocusAngle;

    // Distance from the lookFrom vector to the plane of perfect focus.
    float m_focusDistance;

    // Used to determine viewport dimensions.
    float m_theta;
    float m_h;
    float m_viewportHeight;
    float m_viewportWidth;

    // Relative origin pixel.
    Point3 m_originPixel;

    // The point that the camera looks from.
    Point3 m_lookFrom;

    // The point that the camera looks at.
    Point3 m_lookAt;

    // Offset to the pixel to the right of the given pixel.
    Vector3 m_pixelDeltaU;

    // Offset to the pixel below the given pixel.
    Vector3 m_pixelDeltaV;

    // Camera frame basis vectors.
    Vector3 m_u;
    Vector3 m_v;
    Vector3 m_w;
    
    // Relative up direction of the camera.
    Vector3 m_upVector;

    // Generates a random point in the square [-0.5, 1.0) surrounding a pixel
    // at the origin.
    Vector3 pixelSampleSquare() const;

    // Generates a random point within the camera defocus disk.
    Point3 defocusDiskSample() const;

    // Generates a random point in the disk of the specified radius around a
    // pixel at the origin.
    Vector3 pixelSampleDisk(float radius) const;

    // Retrieves the ray at the specified (i, j) position.
    Ray getRay(int i, int j) const;
};
