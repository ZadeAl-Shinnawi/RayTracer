#include "camera.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/utilities.h"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vector3 viewUp, float aspectRatio,
               float verticalFOV, float aperture, float focusDist) :

    m_lookFrom(lookFrom), m_lookAt(lookAt), m_viewUp(viewUp),
    m_aspectRatio(aspectRatio), m_verticalFOV(verticalFOV),
    m_aperture(aperture), m_focusDist(focusDist),
    m_theta(degreesToRadians(verticalFOV)), m_fovHeight(tan(m_theta / 2.0f)),
    m_viewportHeight(2.0f * m_fovHeight),
    m_viewportWidth(aspectRatio * m_viewportHeight),
    m_w(unitVector(lookFrom - lookAt)), m_u(unitVector(cross(viewUp, m_w))),
    m_v(cross(m_w, m_u)), m_origin(lookFrom),
    m_horizontal(focusDist * m_viewportWidth * m_u),
    m_vertical(focusDist * m_viewportHeight * m_v),
    m_lowerLeftCorner(m_origin - (m_horizontal / 2.0f) -
                   (m_vertical / 2.0f) - (focusDist * m_w)),
    m_lensRadius(aperture / 2.0f) {}

Ray Camera::getRay(float s, float t) const
{
    Vector3 rad = m_lensRadius * randomInUnitDisk();
    Vector3 offset = m_u * rad.x() + m_v * rad.y();

    return Ray(m_origin + offset,
               m_lowerLeftCorner + s * m_horizontal + t *
               m_vertical - m_origin - offset);
}
