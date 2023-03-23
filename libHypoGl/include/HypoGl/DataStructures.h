#pragma once

/* Simple classe de vector3 templatée. Permet les opérateurs arithmétiques de base. */
template <typename T>
struct Vector3
{
    Vector3(const T& x, const T& y, const T& z)
        : x(x), y(y), z(z)
    {}

    Vector3()
        : Vector3<T>(0, 0, 0)
    {}

    Vector3<T> operator+(const Vector3<T>& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3<T>& operator+=(const Vector3<T>& other)
    {
        *this = *this + other;
        return *this;
    }

    Vector3<T> operator-(const Vector3<T>& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3<T>& operator-=(const Vector3<T>& other)
    {
        *this = *this - other;
        return *this;
    }

    template <typename S>
    Vector3<T> operator*(const S& scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }

    template <typename S>
    const Vector3<T>& operator *=(const S& scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    template <typename S>
    Vector3<T> operator/(const S& scalar) const
    {
        return {x / scalar, y / scalar, z / scalar};
    }

    template <typename S>
    const Vector3<T>& operator/=(const S& scalar)
    {
        *this = *this / scalar;
        return *this;
    }

    T x, y, z;
};

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;

/* Simple classe de vector2 templatée. Permet les opérateurs arithmétiques de base. */
template <typename T>
struct Vector2
{
    Vector2(const T& x, const T& y)
        : x(x), y(y)
    {}

    Vector2()
        : Vector2<T>(0, 0)
    {}

    Vector2<T> operator+(const Vector2<T>& other) const
    {
        return {x + other.x, y + other.y};
    }

    Vector2<T>& operator+=(const Vector2<T>& other)
    {
        *this = *this + other;
        return *this;
    }

    Vector2<T> operator-(const Vector2<T>& other) const
    {
        return {x - other.x, y - other.y};
    }

    Vector2<T>& operator-=(const Vector2<T>& other)
    {
        *this = *this - other;
        return *this;
    }

    template <typename S>
    Vector2<T> operator*(const S& scalar) const
    {
        return {x * scalar, y * scalar};
    }

    template <typename S>
    const Vector2<T>& operator *=(const S& scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    template <typename S>
    Vector2<T> operator/(const S& scalar) const
    {
        return {x / scalar, y / scalar};
    }

    template <typename S>
    const Vector2<T>& operator/=(const S& scalar)
    {
        *this = *this / scalar;
        return *this;
    }

    T x, y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;

/*
    Une transformation permet de stocker une translation, une rotation et une mise à l'échelle. Son
    rôle est uniquement de stockage.
    Une transformation est stockée sous forme de float. Peut être modifié et templaté pour une plus
    grande flexibilité.
*/
struct Transform
{
    Transform(const Vector3f& pos, const Vector3f& rot, const Vector3f& sca)
        : position(pos), rotation(rot), scale(sca)
    {}

    Transform(const Vector3f& pos, const Vector3f& rot)
        : Transform(pos, rot, {1.f, 1.f, 1.f})
    {}

    Transform(const Vector3f& pos)
        : Transform(pos, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f})
    {}


    Transform()
        : Transform({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f})
    {}

    Vector3f position, rotation, scale;
};
