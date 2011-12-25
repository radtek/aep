/**
* @file
* @brief 向量类cpp文件.
* @author ruoxi
*
* 实现了向量类.
*/

#include "vector.h"

#include <math.h>

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

void Vector::Save(CArchive &ar)
{
    ar << x
        << y
        << z;
}

void Vector::Load(CArchive &ar)
{
    ar >> x
        >> y
        >> z;
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

double Distance(const Vector &v1, const Vector &v2)
{
    return sqrt(pow((double)(v1.z - v2.z), 2) + pow((double)(v1.y - v2.y), 2) + pow((double)(v1.x - v2.x), 2));
}

double Angle(const Vector &v1, const Vector &v2)
{
    // FIXME.
    return 0;
}
