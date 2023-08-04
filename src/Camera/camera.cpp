#include "camera.h"
#include "../Math/vector3.h"
#include "../Math/ray.h"
#include "../Math/utilities.h"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vector3 viewUp, float aspectRatio,
               float verticalFOV, float aperture, float focusDist) :

    lookFrom(lookFrom), lookAt(lookAt), viewUp(viewUp),
    aspectRatio(aspectRatio), verticalFOV(verticalFOV),
    aperture(aperture), focusDist(focusDist),
    theta(degreesToRadians(verticalFOV)), h(tan(theta / 2.0f)),
    viewportHeight(2.0f * h), viewportWidth(aspectRatio * viewportHeight),
    w(unitVector(lookFrom - lookAt)), u(unitVector(cross(viewUp, w))),
    v(cross(w, u)), origin(lookFrom),
    horizontal(focusDist * viewportWidth * u),
    vertical(focusDist * viewportHeight * v),
    lowerLeftCorner(origin - (horizontal / 2.0f) -
                   (vertical / 2.0f) - (focusDist * w)),
    lensRadius(aperture / 2.0f) {}

Ray Camera::getRay(float s, float t) const
{
    Vector3 rad = lensRadius * randomInUnitDisk();
    Vector3 offset = u * rad.x() + v * rad.y();

    return Ray(origin + offset,
               lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
}