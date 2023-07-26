/*
 *	Contains all Color utility and member function descriptions,
 *	requirements, and modification details.
 */

#pragma once

#include <ostream>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "utilities.h"

// REQUIRES: Nothing.
// MODIFIES: Standard output (cout).
// EFFECTS:  Outputs vector RGB values.
void writeColor(std::ostream& out, Color pixelColor, int samplesPerPixel, bool msaa)
{
    // Check if MSAA is enabled.
    if (!msaa)
    {
        //Write the translated [0,255] value of each color component.
        out << static_cast<int>(255.999 * pixelColor.getX()) << ' '
            << static_cast<int>(255.999 * pixelColor.getY()) << ' '
            << static_cast<int>(255.999 * pixelColor.getZ()) << std::endl;

        return;
    }

    float r = pixelColor.getX();
    float g = pixelColor.getY();
    float b = pixelColor.getZ();

    // Divide the color by the number of samples.
    float scale = 1.0f / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0,256) value of each color component.
    out << static_cast<int>(256.0f * clamp(r, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256.0f * clamp(g, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256.0f * clamp(b, 0.0f, 0.999f)) << '\n';
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns the color that the pixel hit by the ray should be colored.
Color rayColor(const Ray& r, const Hittable& world)
{
    HitRecord rec;
    if (world.hit(r, 0.0f, INF, rec))
    {
        return 0.5f * (rec.normal + Color(1.0f, 1.0f, 1.0f));
    }

    Vec3 unitDirection = unitVector(r.direction());
    float t = 0.5f * (unitDirection.getY() + 1.0f);

    // Lerp: (1 - t) * bottomColor + t * topColor.
    return (1.0f - t) * Color(1.0f, 1.0f, 0.0f) + t * Color(1.0f, 0.25f, 0.0f);
}