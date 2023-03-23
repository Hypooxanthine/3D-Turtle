#pragma once

#include "FuncObject3D.h"
#include "Primitives.h"

class Cube3D : public FuncObject3D
{
public:
    Cube3D(const Transform& t = Transform())
        : FuncObject3D(&Primitives::Cube, t)
    {}
};
