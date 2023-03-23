#pragma once

#include "FuncObject3D.h"
#include "Primitives.h"

class Arrow3D : public FuncObject3D
{
public:
    Arrow3D(const Transform& t = Transform())
        : FuncObject3D(&Primitives::Arrow, t)
    {}
};
