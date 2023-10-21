/*
* This class represents an interval [min, max].
*/

#pragma once

#include "utilities.h"

struct Interval
{
public:
    Interval() : min(+INF), max(-INF) {}

    Interval(float min, float max) : min(min), max(max) {}

    float min, max;

    bool contains(float x) const
    {
        return min <= x && x <= max;
    }

    bool surrounds(float x) const
    {
        return min < x && x < max;
    }

    static const Interval empty, universe;
};

const static Interval empty(+INF, -INF);
const static Interval universe(-INF, +INF);
