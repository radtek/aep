/**
* @file
* @brief 白噪声类头文件.
* @author ruoxi
*
* 定义了白噪声类.
*/

#ifndef __WHITE_NOISE_H__
#define __WHITE_NOISE_H__

#include "aircraft_component_ifaces.h"

class WhiteNoise : public INoise
{
public:
    WhiteNoise();
    virtual ~WhiteNoise();

    virtual UINT32 _stdcall GetTypeId();
    virtual void Save(CArchive &ar);
    virtual void Load(CArchive &ar);
    virtual void _stdcall Destroy();
    virtual void * _stdcall GetInterface(UINT32 iid);
    virtual UINT32 _stdcall GetId();
    virtual void _stdcall SetId(UINT32 id);
    virtual wstring _stdcall GetName();
    virtual void _stdcall SetName(wstring name);
    enum WNAID
    {
        WNAID_COORD_FACTOR,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual double _stdcall Affect(double data);

    virtual double _stdcall GetMean();
    virtual double _stdcall GetVariance();

public:
    double m_Factor;

    UINT32 m_Id;
    wstring m_Name;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_WHITE_NOISE;
    static WhiteNoise *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __WHITE_NOISE_H__
