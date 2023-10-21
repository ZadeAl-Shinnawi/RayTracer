/*
 * This class provides the necessary functionality to manipulate and output
 * colors.
 */

#pragma once

#include <ostream>

#include "vector3.h"
#include "ray.h"
#include "utilities.h"
#include "../Materials/material.h"
#include "../Hittables/hittable.h"

// Writes RGB triplets to standard output in PPM format.
void inline writeColor(std::ostream& out, const Color& pixelColor,
                const int samplesPerPixel, const bool msaa)
{
    // Multisample anti-aliasing disabled.
    if (!msaa)
    {
        out << static_cast<int>(255.999 * pixelColor.x()) << ' '
            << static_cast<int>(255.999 * pixelColor.y()) << ' '
            << static_cast<int>(255.999 * pixelColor.z()) << std::endl;

        return;
    }

    // Get RGB triplet.
    float r = pixelColor.x();
    float g = pixelColor.y();
    float b = pixelColor.z();

    // Calculate color intensity.
    float scale = 1.0f / samplesPerPixel;

    // Apply gamma correction (gamma = 2.0).
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256.0f * clamp(r, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256.0f * clamp(g, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256.0f * clamp(b, 0.0f, 0.999f)) << '\n';
}

// Calculates the pixel color for the given ray.
Color inline rayColor(const Ray& r, int depth, const Hittable& world)
{
    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0.0f, 0.0f, 0.0f);

    HitRecord rec;

    if (world.hit(r, Interval(0.001f, INF), rec))
    {
        Ray scattered;
        Color attenuation;

        if (rec.matPtr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * rayColor(scattered, depth - 1, world);
        }

        return Color(0.0f, 0.0f, 0.0f);
    }

    Vector3 unitDirection = unitVector(r.direction());
    float a = 0.5f * (unitDirection.y() + 1.0f);

    return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}
