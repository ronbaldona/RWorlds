#pragma once

namespace rworlds::math {

template <typename P>
struct Vec3
{
    union 
    {
        struct { P x, y, z; };
        struct { P r, g, b; };
        struct { P data[3]; };
    };

    P& operator[](unsigned i)
    {
        return data[i];
    }

    Vec3<P>& operator-()
    {
        for (auto& x : this->data)
        {
            x = -x;
        }
        return *this;
    }
};

template <typename P>
Vec3<P> operator+(Vec3<P> const lhs, Vec3<P> const rhs)
{
    Vec3<P> toRet;
    for (unsigned i = 0; i < 3; ++i)
    {
        toRet[i] = lhs[i] + rhs[i];
    }
    return toRet;
}

template <typename P>
Vec3<P> operator-(Vec3<P> const lhs, Vec3<P> const rhs)
{
    Vec3<P> toRet;
    for (unsigned i = 0; i < 3; ++i)
    {
        toRet[i] = lhs[i] - rhs[i];
    }
    return toRet;
}

template <typename P>
Vec3<P> operator*(P lhs, Vec3<P> const rhs)
{
    Vec3<P> toRet;
    for (unsigned i = 0; i < 3; ++i)
    {
        toRet[i] = lhs * rhs[i];
    }
    return toRet;
}

}

/*----- COMMON TYPES -----*/
using Vec3f = rworlds::math::Vec3<float>;
