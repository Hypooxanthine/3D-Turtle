#pragma once

#include "FuncObject3D.h"
#include "Primitives.h"

class Line3D : public FuncObject3D
{
public:
    Line3D(const Transform& t = Transform())
        : FuncObject3D(&Primitives::Line, t)
    {}
};
