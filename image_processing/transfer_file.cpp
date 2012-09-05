/**
* @file
* @brief 输出外部数据类cpp文件.
* @author ruoxi
*
* 实现了输出外部数据类.
*/

#include "stdafx.h"

#include "transfer_file.h"
#include "tcp_socket.h"
#include "utility.h"

TransferFile::TransferFile()
:
m_HostName(TEXT("192.168.0.1")),
m_Port(10086)
{
}

TransferFile::~TransferFile()
{
}

UINT32 TransferFile::GetTypeId()
{
    return s_ComponentId;
}

void TransferFile::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str());

    ar << CString(m_HostName.c_str()) << m_Port;
}

void TransferFile::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str >> m_Port;
    m_HostName = str;
}

void TransferFile::Destroy()
{
    delete this;
}

void *TransferFile::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_TRANSFER == iid)
    {
        iface = static_cast<ITransfer *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 TransferFile::GetId()
{
    return m_Id;
}

void TransferFile::SetId(UINT32 id)
{
    m_Id = id;
}

wstring TransferFile::GetName()
{
    return m_Name;
}

void TransferFile::SetName(wstring name)
{
    m_Name = name;
}

void TransferFile::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_SERVER_IP;
    attribute.Name = TEXT("服务器地址");
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);

    attribute.Id = AAID_SERVER_PORT;
    attribute.Name = TEXT("服务器端口");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);
}

RC TransferFile::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_SERVER_IP:
        *((wstring *)attr) = m_HostName;
        break;
    case AAID_SERVER_PORT:
        *((INT32 *)attr) = m_Port;
        break;
    }

    return RC::COMPONENT_GETATTRIBUTE_ERROR;
}

RC TransferFile::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_SERVER_IP:
        m_HostName = *((wstring *)attr);
        break;
    case AAID_SERVER_PORT:
        m_Port = *((INT32 *)attr);
        break;
    }

    return RC::COMPONENT_SETATTRIBUTE_ERROR;
}

bool TransferFile::Connect(IComponent *component)
{
    return false;
}

IComponent *TransferFile::Clone()
{
    TransferFile *transferFile = new TransferFile();

    transferFile->m_HostName = m_HostName;
    transferFile->m_Port = m_Port;
    transferFile->m_Input = m_Input;

    transferFile->m_Id = m_Id;
    transferFile->m_Name = m_Name;

    return transferFile;
}

void TransferFile::Reset()
{
    m_Input.Reset();
}

RC TransferFile::Config()
{
    RC rc;

    return rc;
}

RC TransferFile::SetInput(IData *input)
{
    if (NULL == input)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IOutputFileOutput *outputFileOutput = (IOutputFileOutput *)(input->GetInterface(CLIENT_CIID_OUTPUT_FILE_OUTPUT));
    if (NULL != outputFileOutput)
    {
        m_Input.m_Path = outputFileOutput->m_Path;
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC TransferFile::Run()
{
    RC rc;
    TcpSocket m_Socket;
    CHECK_RC(m_Socket.Init());
    string hostName = Utility::Wstring2String(m_HostName);
    m_Socket.Connect(hostName.c_str(), m_Port);

    for (UINT32 i = 0; i < m_Input.m_Path.size(); ++i)
    {
        if (m_Input.m_Path[i].empty())
        {
            continue;
        }
        
        CHECK_RC(m_Socket.SendCommand(CC::UPLOAD_FILE_COMMAND));

        wstring fileNameWithoutPath = Utility::StripFilePath(m_Input.m_Path[i].c_str());
        CHECK_RC(m_Socket.SendWString(fileNameWithoutPath.c_str()));
        CHECK_RC(m_Socket.SendFile(m_Input.m_Path[i].c_str()));
    }
    CHECK_RC(m_Socket.SendCommand(CC::LOGOUT_COMMAND));
    CHECK_RC(m_Socket.Shut());

    return rc;
}

RC TransferFile::GetOutput(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

TransferFile *TransferFile::Factory()
{
    TransferFile *transferFile = new TransferFile;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    transferFile->m_Name = name;
    ++s_Count;
    return transferFile;
}

LPCWSTR TransferFile::s_ComponentName = TEXT("文件传输");

UINT32 TransferFile::s_Count = 0;
