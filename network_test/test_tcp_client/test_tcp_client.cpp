/**
* @file
* @brief TestTcpClient类cpp文件.
* @author ruoxi
*
* 实现了TestTcpClient类.
*/

#include "test_tcp_client.h"

/**
* @param hostName 测试用TCP服务端主机名.
* @param port 测试用TCP服务端主机端口.
* @param logFileName 日志文件名.
* @param id 客户端ID, 默认值为0.
*
* TestTcpClient构造函数. 接受测试用TCP服务端主机名, 端口, 日志文件名及客户端ID.
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
* @return 结果代码.
*
* TestTcpClient初始化. 初始化Socket环境, 初始化客户端用TcpSocket.
*/
RC TestTcpClient::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_TcpSocket->Init());

    return rc;
}

/**
* @return 结果代码.
*
* TestTcpClient清理. 清理客户端用TcpSocket, 清理Socket环境.
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
* @return 结果代码.
*/
RC TestTcpClient::Connect()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Connect(m_HostName, m_Port));

    return rc;
}

/**
* @return 日志文件名.
*/
const char *TestTcpClient::GetLogFileName()
{
    return m_LogFileName;
}
