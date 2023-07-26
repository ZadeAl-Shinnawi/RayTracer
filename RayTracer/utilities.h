/*
 *	This class contains some constants and utility functions useful
 *  to many of the other files contained within this project.
 */

#pragma once

#include <limits>
#include <random>

// Constants
const float INF = std::numeric_limits<float>::infinity();
const float PI = 3.1415926f;

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Converts input degree(s) value to radian(s).
inline float degreesToRadians(float degrees)
{
    return (degrees * PI) / 180.0f;
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Returns a random float within the range [0, 1).
inline float randomFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;

    return distribution(generator);
}

// REQUIRES: Nothing.
// MODIFIES: Nothing.
// EFFECTS:  Clamps x within the bounds of [min, max] if needed.
inline float clamp(float x, float min, float max)
{
    if (x < min)
    {
        return min;
    }

    if (x > max)
    {
        return max;
    }

    return x;
}