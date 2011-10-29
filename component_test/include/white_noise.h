/**
* @file
* @brief 白噪声类头文件.
* @author ruoxi
*
* 定义了白噪声类.
*/

#ifndef __WHITE_NOISE_H__
#define __WHITE_NOISE_H__

#include "aircraft_measure_ifaces.h"

class WhiteNoise : public INoise
{
public:
    virtual ~WhiteNoise();

    virtual RC _stdcall GetInterface(UINT32 iid, void **iface);
    virtual RC _stdcall Config();
    virtual RC _stdcall Destroy();
    virtual RC _stdcall GetName(LPWSTR *name);
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Validate();

    virtual RC _stdcall Affect(Vector &data);

public:
    double m_Factor;

    LPWSTR m_Name;

public:
    static LPCWSTR WhiteNoiseTypeName;

    static WhiteNoise *WhiteNoiseFactory();
private:
    static UINT32 WhiteNoiseCount;
};

#endif // __WHITE_NOISE_H__
