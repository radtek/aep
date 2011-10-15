/**
* @file
* @brief TestTcpClient��cpp�ļ�.
* @author ruoxi
*
* ʵ����TestTcpClient��.
*/

#include "test_tcp_client.h"

/**
* @param hostName ������TCP�����������.
* @param port ������TCP����������˿�.
* @param logFileName ��־�ļ���.
* @param id �ͻ���ID, Ĭ��ֵΪ0.
*
* TestTcpClient���캯��. ���ܲ�����TCP�����������, �˿�, ��־�ļ������ͻ���ID.
*/
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

/**
* @return �������.
*
* TestTcpClient��ʼ��. ��ʼ��Socket����, ��ʼ���ͻ�����TcpSocket.
*/
RC TestTcpClient::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_TcpSocket->Init());

    return rc;
}

/**
* @return �������.
*
* TestTcpClient����. ����ͻ�����TcpSocket, ����Socket����.
*/
RC TestTcpClient::Shut()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Shut());

    CHECK_RC(Socket::Shut());

    m_Logger.close();

    return rc;
}

/**
* @return �������.
*/
RC TestTcpClient::Connect()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Connect(m_HostName, m_Port));

    return rc;
}

/**
* @return ��־�ļ���.
*/
const char *TestTcpClient::GetLogFileName()
{
    return m_LogFileName;
}
