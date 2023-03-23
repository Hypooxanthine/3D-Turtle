#pragma once

#include "DataStructures.h"

class Color
{
public:
    Color(const float& r, const float& g, const float& b);
    Color();

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;

public:
    float r, g, b;
};
