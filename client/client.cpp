#include "client.h"

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

Client::Client()
:
m_Platform(Platform::GetInstance()),
m_IsConnected(false),
m_IsLogined(false)
{
}

Client *Client::s_Instance = NULL;

bool Client::s_Initialized = false;

Client::~Client()
{
}

RC Client::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_Platform.Init());
    CHECK_RC(m_Socket.Init());

    // FIXME:
    m_HostName = "localhost";
    m_Port = 10086;

    return rc;
}

RC Client::Shut()
{
    RC rc;

    CHECK_RC(m_Socket.Shut());
    CHECK_RC(m_Platform.Shut());

    CHECK_RC(Socket::Shut());

    return rc;
}

RC Client::Connect()
{
    RC rc;

    CHECK_RC(m_Socket.Connect(m_HostName, m_Port));

    m_IsConnected = true;

    return rc;
}

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

RC Client::SendModelFile(LPCWSTR fileName)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::SEND_MODEL_FILE_COMMAND));

    CHECK_RC(m_Socket.SendFile(fileName));

    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));

    return _rc;
}
