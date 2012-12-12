/**
* @file
* @brief 通用图像算法类头文件.
* @author ruoxi
*
* 定义了通用图像算法类.
*/

#ifndef __IMAGE_ALGORITHM_H__
#define __IMAGE_ALGORITHM_H__

#include "image_processing_ifaces.h"

class ImageAlgorithm : public IImageAlgorithm
{
public:
    ImageAlgorithm();
    virtual ~ImageAlgorithm();

    virtual UINT32 _stdcall GetTypeId();
    virtual void _stdcall Save(CArchive &ar);
    virtual void _stdcall Load(CArchive &ar);
    virtual void _stdcall Destroy();
    virtual void * _stdcall GetInterface(UINT32 iid);
    virtual UINT32 _stdcall GetId();
    virtual void _stdcall SetId(UINT32 id);
    virtual wstring _stdcall GetName();
    virtual void _stdcall SetName(wstring name);
    enum AAID
    {
        AAID_WIDTH1 = 0,
        AAID_WIDTH2,
        AAID_WIDTH3,
        AAID_WIDTH4,
        AAID_WIDTH5,
        AAID_HEIGHT1,
        AAID_HEIGHT2,
        AAID_HEIGHT3,
        AAID_HEIGHT4,
        AAID_HEIGHT5,
        AAID_DLL_FILE_NAME,
        AAID_FUNC_NAME,
        AAID_FROM_ALGORITHM_OUTPUT_INDEX,
        AAID_FACTOR1,
        AAID_FACTOR2,
        AAID_FACTOR3,
        AAID_FACTOR4,
        AAID_FACTOR5,
        AAID_IS_ENTRANCE,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual IComponent * _stdcall Clone();
    virtual void _stdcall Reset();
    virtual RC _stdcall Config();
    virtual RC _stdcall SetInput(IData *input);
    virtual RC _stdcall GetOutput(IData *&output);

    virtual RC _stdcall InternalRun();

    virtual bool _stdcall IsEntrance();

protected:
    IImageAlgorithmInput1 *m_Input1;
    IImageAlgorithmInput2 *m_Input2;
    static const UINT32 m_OutputCount = 5;
    IImageAlgorithmOutput *m_Output;
    UINT32 m_Width[m_OutputCount], m_Height[m_OutputCount];
    wstring m_DllFileName;
    wstring m_FuncName;
    UINT32 m_FromAlgorithmOutputIndex;
    UINT32 m_IsEntrance;
    double m_Factor[m_OutputCount];

public:
    double m_ImageAlgorithmFactor[m_OutputCount];

    UINT32 m_Id;
    wstring m_Name;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_IMAGE_ALGORITHM;
    static ImageAlgorithm *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __IMAGE_ALGORITHM_H__
