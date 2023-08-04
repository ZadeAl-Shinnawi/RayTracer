#pragma once

#include <limits>
#include <random>

const float INF = std::numeric_limits<float>::infinity();
const float PI = 3.1415926f;

inline float degreesToRadians(float degrees)
{
    return (degrees * PI) / 180.0f;
}

// Returns a random float within the range [0, 1).
inline float randomFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;

    return distribution(generator);
}

// Returns a random float within the range [min, max).
inline float randomFloat(float min, float max)
{
    return min + (max - min) * randomFloat();
}

// Clamps x within the bounds of [min, max] if needed.
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