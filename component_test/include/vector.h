/**
* @file
* @brief 向量类文件.
* @author ruoxi
*
* 定义了向量类.
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "client_interfaces.h"

class Vector : public IVector
{
public:
    Vector();
    Vector(double _x, double _y, double _z);

    virtual RC _stdcall QueryInterface(UINT32 iid, void **ppi);

    virtual double _stdcall GetX();
    virtual void _stdcall SetX(double x);

    virtual double _stdcall GetY();
    virtual void _stdcall SetY(double y);

    virtual double _stdcall GetZ();
    virtual void _stdcall SetZ(double z);

private:
    double x, y, z;
};

#endif // __VECTOR_H__
