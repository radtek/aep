/**
* @file
* @brief 向量类cpp文件.
* @author ruoxi
*
* 实现了向量类.
*/

#include "vector.h"

Vector::Vector()
:
x(0),
y(0),
z(0)
{
}

Vector::Vector(double _x, double _y, double _z)
:
x(_x),
y(_y),
z(_z)
{
}

Vector::Vector(const Vector &v)
:
x(v.x),
y(v.y),
z(v.z)
{
}

Vector &Vector::operator =(const Vector &v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

const Vector Vector::operator +(const Vector &v) const
{
    Vector result(*this);
    result += v;
    return result;
}

const Vector Vector::operator -(const Vector &v) const
{
    Vector result(*this);
    result -= v;
    return result;
}

const Vector Vector::operator *(double d) const
{
    Vector result(*this);
    result *= d;
    return result;
}

const Vector Vector::operator /(double d) const
{
    Vector result(*this);
    result /= d;
    return result;
}

const Vector &Vector::operator +=(const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

const Vector &Vector::operator -=(const Vector &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

const Vector &Vector::operator *=(double d)
{
    x *= d;
    y *= d;
    z *= d;
    return *this;
}

const Vector &Vector::operator /=(double d)
{
    x /= d;
    y /= d;
    z /= d;
    return *this;
}
