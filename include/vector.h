/**
* @file
* @brief 向量类头文件.
* @author ruoxi
*
* 定义了向量类.
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

struct Vector
{
    Vector();
    Vector(double _x, double _y, double _z);
    Vector(const Vector &v);

    void Save(CArchive &ar);
    void Load(CArchive &ar);

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

double Distance(const Vector &v1, const Vector &v2);
double Angle(const Vector &v1, const Vector &v2);

#endif // __VECTOR_H__
