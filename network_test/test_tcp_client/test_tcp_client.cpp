#include "test_tcp_client.h"

TestTcpClient::TestTcpClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
m_HostName(hostName),
m_Port(port),
m_LogFileName(logFileName),
m_Logger(logFileName),
m_Id(id)
{
    m_TcpSocket = new TcpSocket();
}

TestTcpClient::~TestTcpClient()
{
}

RC TestTcpClient::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_TcpSocket->Init());

    return rc;
}

RC TestTcpClient::Shut()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Shut());

    CHECK_RC(Socket::Shut());

    m_Logger.close();

    return rc;
}

RC TestTcpClient::Connect()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Connect(m_HostName, m_Port));

    return rc;
}

const char *TestTcpClient::GetLogFileName()
{
    return m_LogFileName;
}
