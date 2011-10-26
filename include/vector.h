/**
* @file
* @brief ������ͷ�ļ�.
* @author ruoxi
*
* ������������.
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

struct Vector
{
    Vector();
    Vector(double _x, double _y, double _z);
    Vector(const Vector &v);

    Vector &operator =(const Vector &v);

    const Vector operator +(const Vector &v) const;
    const Vector operator -(const Vector &v) const;
    const Vector operator *(double d) const;
    const Vector operator /(double d) const;

    const Vector &operator +=(const Vector &v);
    const Vector &operator -=(const Vector &v);
    const Vector &operator *=(double d);
    const Vector &operator /=(double d);

    double x, y, z;
};

#endif // __VECTOR_H__
