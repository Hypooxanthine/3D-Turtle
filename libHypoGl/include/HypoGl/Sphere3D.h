#pragma once

#include "FuncObject3D.h"
#include "Primitives.h"

class Sphere3D : public FuncObject3D
{
public:
    Sphere3D(const Transform& t = Transform())
        : FuncObject3D(&Primitives::Sphere, t)
    {}
};
