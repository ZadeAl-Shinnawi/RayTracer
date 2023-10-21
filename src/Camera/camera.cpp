#include "camera.h"

#include <iostream>
#include <cmath>

#include "../Math/Color.h"
#include "../Hittables/hittable.h"

Camera::Camera(int imageWidth, int imageHeight, int samplesPerPixel,
               int maxDepth, float aspectRatio, float verticalFOV,
               float defocusAngle, float focusDistance, Point3 lookFrom,
               Point3 lookAt, Vector3 upVector) :
               m_imageWidth(imageWidth), m_imageHeight(imageHeight),
               m_samplesPerPixel(samplesPerPixel), m_maxDepth(maxDepth),
               m_aspectRatio(aspectRatio), m_verticalFOV(verticalFOV),
               m_defocusAngle(defocusAngle), m_focusDistance(focusDistance),
               m_lookFrom(lookFrom), m_lookAt(lookAt), m_upVector(upVector),
               m_theta(degreesToRadians(m_verticalFOV)),
               m_h(tan(m_theta / 2.0f)),
               m_viewportHeight(2.0f * m_h * m_focusDistance),
               m_viewportWidth(m_viewportHeight *
                              (static_cast<float>(m_imageWidth) /
                               m_imageHeight))
{
    m_w = unitVector(m_lookFrom - m_lookAt);
    m_u = unitVector(cross(m_upVector, m_w));
    m_v = cross(m_w, m_u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.

    // Vector across the horizontal edge of the viewport.
    Vector3 viewportU = m_viewportWidth * m_u;

    // Vector across the vertical edge of the viewport.
    Vector3 viewportV = m_viewportHeight * -m_v;

    m_pixelDeltaU = viewportU / static_cast<float>(m_imageWidth);
    m_pixelDeltaV = viewportV / static_cast<float>(m_imageHeight);

    Vector3 viewportUpperLeft = m_lookFrom - (m_focusDistance * m_w) -
            viewportU / 2.0f - viewportV / 2.0f;

    m_originPixel = viewportUpperLeft + 0.5f * (m_pixelDeltaU + m_pixelDeltaV);
}

void Camera::render(const Hittable& world) const
{
    // Output PPM header.
    std::cout << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";

    for (int i = 0; i < m_imageHeight; ++i)
    {
        // Log the remaining lines to render.
        std::clog << "\rRemaining lines to render: " << (m_imageHeight - i)
                  << ' ' << std::flush;

        for (int j = 0; j < m_imageWidth; ++j)
        {
            Color pixelColor(0.0f, 0.0f, 0.0f);

            for (int sample = 0; sample < m_samplesPerPixel; ++sample)
            {
                Ray r = getRay(j, i);
                pixelColor += rayColor(r, m_maxDepth, world);
            }

            // Output final color pixel.
            writeColor(std::cout, pixelColor, m_samplesPerPixel, true);
        }
    }

    // Inform the user that the PPM file is finished rendering.
    std::clog << "\rDone.\n";
}

Ray Camera::getRay(int i, int j) const
{
    Vector3 pixelCenter = m_originPixel + (static_cast<float>(i) *
                                           m_pixelDeltaU)
                                        + (static_cast<float>(j) *
                                           m_pixelDeltaV);

    Vector3 pixelSample = pixelCenter + pixelSampleSquare();
    Vector3 rayOrigin = (m_defocusAngle <= 0.0f) ? m_lookFrom :
                                                   defocusDiskSample();
    Vector3 rayDirection = pixelSample - rayOrigin;

    float rayTime = randomFloat();

    return Ray(rayOrigin, rayDirection, rayTime);
}

Vector3 Camera::pixelSampleSquare() const
{
    
    float xCoordinate = randomFloat() - 0.5f;
    float yCoordinate = randomFloat() - 0.5f;

    return (xCoordinate * m_pixelDeltaU) + (yCoordinate * m_pixelDeltaV);
}

Vector3 Camera::pixelSampleDisk(float radius) const
{
    
    Vector3 pixel = randomInUnitDisk() * radius;

    return (pixel[0] * m_pixelDeltaU) + (pixel[1] * m_pixelDeltaV);
}

Point3 Camera::defocusDiskSample() const
{
    Vector3 pixel = randomInUnitDisk();

    // Horizontal radius of the defocus disk.
    Vector3 defocusDiskU;

    // Vertical radius of the defocus disk.
    Vector3 defocusDiskV;

    // Calculate the camera defocus disk basis vectors.
    float defocusRadius = tan(degreesToRadians(m_defocusAngle / 2.0f))
                        * m_focusDistance;

    defocusDiskU = m_u * defocusRadius;
    defocusDiskV = m_v * defocusRadius;

    return m_lookFrom + (pixel[0] * defocusDiskU) + (pixel[1] * defocusDiskV);
}
