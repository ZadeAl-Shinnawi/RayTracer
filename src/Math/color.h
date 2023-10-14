#pragma once

#include <ostream>
#include <cmath>
#include "vector3.h"
#include "ray.h"
#include "../Hittables/hittable.h"
#include "utilities.h"
#include "../Materials/material.h"

// Writes RGB triplets to standard output in PPM format.
void writeColor(std::ostream& out, const Color& pixelColor,
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
Color rayColor(const Ray& r, const Hittable& world, const int depth)
{
    HitRecord rec;

    // If the ray bounce limit has been exceeded, no more light is gathered.
    if (depth <= 0)
    {
        return Color(0.0f, 0.0f, 0.0f);
    }

    if (world.hit(r, 0.001f, INF, rec))
    {
        // Direction of light ray scattering/reflection.
        Ray scattered;

        // Light ray loss due to scattering and absorption.
        Color attenuation;

        if (rec.matPtr->scatter(r, rec, attenuation, scattered))
        {
            // Calculate less intense ray color recursively.
            return attenuation * rayColor(scattered, world, depth - 1);
        }

        return Color(0.0f, 0.0f, 0.0f);
    }

    Vector3 unitDirection = unitVector(r.direction());
    float t = 0.5f * (unitDirection.y() + 1.0f);

    // Linear interpolation: (1 - t) * bottomColor + t * topColor.
    return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
}
