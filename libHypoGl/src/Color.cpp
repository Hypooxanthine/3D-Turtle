#include "HypoGl/Color.h"

Color::Color(const float& r, const float& g, const float& b)
    : r(r), g(g), b(b)
{}

Color::Color()
    : Color(1.f, 1.f, 1.f)
{}

const Color Color::Black    (0.f, 0.f, 0.f);
const Color Color::White    (1.f, 1.f, 1.f);
const Color Color::Red      (1.f, 0.f, 0.f);
const Color Color::Green    (0.f, 1.f, 0.f);
const Color Color::Blue     (0.f, 0.f, 1.f);
const Color Color::Yellow   (1.f, 1.f, 0.f);
const Color Color::Magenta  (1.f, 0.f, 1.f);
const Color Color::Cyan     (0.f, 1.f, 1.f);
