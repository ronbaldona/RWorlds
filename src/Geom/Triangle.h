#pragma once

#include "Math/Vec.h"

namespace rworlds::geom {

struct Vertex
{
    Vec3f pos;
    Vec3f color;
};

struct Triangle
{
    Vertex a, b, c;
};

}
