/**
* @file
* @brief 向量类文件.
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

RC Vector::QueryInterface(UINT32 iid, void **ppi)
{
    if (CIID_ICOMPONENT == iid)
    {
        *ppi = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_VECTOR == iid)
    {
        *ppi = static_cast<IVector *>(this);
    }
    else
    {
        *ppi = 0;
        return RC::COMPONENT_QUERYINTERFACE_ERROR;
    }
    return OK;
}

double Vector::GetX()
{
    return x;
}

void Vector::SetX(double _x)
{
    x = _x;
}

double Vector::GetY()
{
    return y;
}

void Vector::SetY(double _y)
{
    y = _y;
}

double Vector::GetZ()
{
    return z;
}

void Vector::SetZ(double _z)
{
    z = _z;
}
