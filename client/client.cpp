#include "client.h"

Client::Client()
:
m_Platform(Platform::GetInstance())
{
}

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

    return rc;
}

RC Client::Login(const wstring &name, const wstring &password)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::LOGIN_COMMAND));

    CHECK_RC(m_Socket.SendWString(name.c_str()));
    CHECK_RC(m_Socket.SendWString(password.c_str()));

    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));
    return _rc;
}
