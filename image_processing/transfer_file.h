/*
* @file
* @brief 输出外部数据类头文件.
* @author ruoxi
*
* 定义了输出外部数据类.
*/

#ifndef __TRANSFER_FILE_H__
#define __TRANSFER_FILE_H__

#include "image_processing_ifaces.h"

class TransferFile : public ITransfer
{
public:
    TransferFile();
    virtual ~TransferFile();

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
        AAID_SERVER_IP = 0,
        AAID_SERVER_PORT,
        AAID_LAST,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual IComponent * _stdcall Clone();
    virtual void _stdcall Reset();
    virtual RC _stdcall Config();
    virtual RC _stdcall Run();
    virtual RC _stdcall SetInput(IData *input);
    virtual RC _stdcall GetOutput(IData *&output);

public:
    wstring m_HostName;
    int m_Port;

    UINT32 m_Id;
    wstring m_Name;

protected:
    ITransferInput m_Input;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_TRANSFER_FILE;
    static TransferFile *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __TRANSFER_FILE_H__
