/**
* @file
* @brief Client�ͻ�����cpp�ļ�.
* @author ruoxi
*
* ʵ����Client�ͻ�����.
*/

#include "client.h"

#include "utility.h"

/**
* @return Client���Ψһʵ��.
*
* �û�ֻ��ͨ���ú������Client���Ψһʵ��.
* ��Client�໹δ����ʼ��, �򴴽�Ψһ��Client�����,
* ����ֱ�ӷ��ظö���.
*/
Client &Client::GetInstance()
{
    if (!s_Initialized)
    {
        s_Instance = new Client;
        s_Initialized = true;
    }
    return *s_Instance;
}

void Client::DestroyInstance()
{
    if (s_Initialized)
    {
        delete s_Instance;
        s_Instance = NULL;
        s_Initialized = false;
    }
}

/**
* ��Client���Ψһ���캯������Ϊ˽��,
* ���Ա�֤������������������������캯��,
* ���Ҹ��಻������ʽ��ʵ����.
* �ù��캯��������ɾ���ĳ�ʼ��,
* ��ʼ������ͨ��Init���������.
*/
Client::Client()
:
m_Platform(Platform::GetInstance()),
m_IsConnected(false),
m_IsLogined(false)
{
}

Client *Client::s_Instance = NULL;

bool Client::s_Initialized = false;

/**
* Client�����������.
* ����������������ɾ��������,
* ���ٹ���ͨ��Shut���������.
*/
Client::~Client()
{
}

/**
* @return �������.
*
* ���Client����ĳ�ʼ��.
* ����Socket�������г�ʼ��,
* ��ƽ̨���г�ʼ��,
* ��TcpSocket������г�ʼ��.
* �������ú�Ĭ�ϵķ�����������ַ�Ͷ˿�.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Client::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_Platform.Init());
    CHECK_RC(m_Socket.Init());

    m_HostName = "localhost";
    m_Port = 10086;

    return rc;
}

/**
* @return �������.
*
* ���Client���������.
* ��������TcpSocket����,
* Ȼ������ƽ̨,
* �������Socket����.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Client::Shut()
{
    RC rc;

    CHECK_RC(m_Socket.Shut());
    CHECK_RC(m_Platform.Shut());

    CHECK_RC(Socket::Shut());

    return rc;
}

/**
* @param hostName ���������������ַ.
*/
RC Client::SetHostName(const char *hostName)
{
    RC rc;

    m_HostName = hostName;

    return rc;
}

/**
* @param port �����������˿�.
*/
RC Client::SetPort(int port)
{
    RC rc;

    m_Port = port;

    return rc;
}

/**
* @return �������.
*
* ������������.
* ʹ��TcpSocket����������������.
* ������ʧ���򷵻ش������.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Client::Connect()
{
    RC rc;

    CHECK_RC(m_Socket.Connect(m_HostName.c_str(), m_Port));

    m_IsConnected = true;

    return rc;
}

/**
* @return �������.
*
* �Ͽ��������������.
* ʹ�õķ������ȹر�TcpSocket����,
* Ȼ�������µ������ʼ��,
* ����TcpSocket����ɹ��´�����ʹ��.
* ���ӳɹ�������m_IsConnectedΪtrue.
* ����OK.
*/
RC Client::Disconnect()
{
    RC rc;

    CHECK_RC(m_Socket.Shut());
    CHECK_RC(m_Socket.Init());

    m_IsConnected = false;

    return rc;
}

bool Client::IsConnected()
{
    return m_IsConnected;
}

/**
* @param name �û���.
* @param password ����.
* @return �������.
*
* ���û��������뷢�������������е�¼.
* �û�����������ܺ��пո�,
* ���ú����������ж�,
* ��һ�㽫�ɵ��øú������ϲ㺯������֤.
* ���շ��������صĽ��.
* ����½ʧ��, �򷵻ش�����Ϣ.
* ��������m_IsLoginedΪtrue,
* ��ʾ�Ѿ���½.
*/
RC Client::Login(const wstring &name, const wstring &password)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::LOGIN_COMMAND));

    CHECK_RC(m_Socket.SendWString(name.c_str()));
    CHECK_RC(m_Socket.SendWString(password.c_str()));

    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));
    if (OK == _rc)
    {
        m_IsLogined = true;
    }

    return _rc;
}

bool Client::IsLogined()
{
    return m_IsLogined;
}

RC Client::Logout()
{
    RC rc;

    if (!m_IsLogined)
    {
        return rc;
    }

    CHECK_RC(m_Socket.SendCommand(CC::LOGOUT_COMMAND));
    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));
    if (OK == _rc)
    {
        m_IsLogined = false;
    }

    return _rc;
}

/**
* @param name �û���.
* @param password ����.
* @return �������.
*
* ���û��������뷢��������������ע��.
* �û�����������ܺ��пո�,
* ���ú����������ж�,
* ��һ�㽫�ɵ��øú������ϲ㺯������֤.
* ���շ��������صĽ��.
* ��ע��ʧ��, �򷵻ش�����Ϣ.
* ���򷵻�OK.
*/
RC Client::Register(const wstring &name, const wstring &password)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::REGISTER_COMMAND));

    CHECK_RC(m_Socket.SendWString(name.c_str()));
    CHECK_RC(m_Socket.SendWString(password.c_str()));

    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));

    return _rc;
}

/**
* @param fileName Ҫ���͵��ļ�·��.
* @return �������.
*
* ��ģ���ļ�������������.
* ���շ��������صĽ��.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Client::SendModelFile(LPCWSTR fileName)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::SEND_MODEL_FILE_COMMAND));
    RC _rc = m_Socket.SendFile(fileName);

    if (OK == _rc)
    {
        CHECK_RC(m_Socket.RecvRC(_rc));
        if (OK == _rc)
        {
            wstring datFileName = fileName;
            datFileName += TEXT(".dat");
            CHECK_RC(m_Socket.RecvFile(datFileName.c_str()));
        }
    }

    return _rc;
}

RC Client::UploadFile(const wstring &fileName)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::UPLOAD_FILE_COMMAND));

    wstring fileNameWithoutPath = Utility::StripFilePath(fileName.c_str());
    CHECK_RC(m_Socket.SendWString(fileNameWithoutPath.c_str()));
    CHECK_RC(m_Socket.SendFile(fileName.c_str()));

    return rc;
}

RC Client::GetFileList(vector<wstring> &fileList)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::GET_FILE_LIST_COMMAND));

    wstring fileName;
    CHECK_RC(m_Socket.RecvWString(fileName));
    while (fileName != TEXT(" "))
    {
        fileList.push_back(fileName);
        CHECK_RC(m_Socket.RecvWString(fileName));
    }

    return rc;
}

RC Client::DownLoadFile(const wstring &fileName, const wstring &pathName)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::DOWNLOAD_FILE_COMMAND));

    CHECK_RC(m_Socket.SendWString(fileName.c_str()));
    
    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));
    CHECK_RC(_rc);

    CHECK_RC(m_Socket.RecvFile(pathName.c_str()));

    return rc;
}
