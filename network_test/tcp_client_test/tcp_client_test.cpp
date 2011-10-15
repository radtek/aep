/**
* @file
* @brief TcpClientTest类cpp文件.
* @author ruoxi
*
* 实现了TcpClientTest类.
*/

#include "tcp_client_test.h"

/**
* @param testName 测试名.
* @param client 测试用TCP客户端.
*
* TcpClientTest构造函数. 接受测试名及一个测试用TCP客户端对象.
*/
TcpClientTest::TcpClientTest(const char *testName, TestTcpClient *client)
:
NetworkTest(testName),
m_Client(client)
{
}

TcpClientTest::~TcpClientTest()
{
}

/**
* @return 结果代码.
*
* 用于测试用TCP客户端的测试运行函数.
* 初始化客户端, 连接至远程服务端,
* 运行客户端程序,
* 最后清理客户端.
*/
RC TcpClientTest::Run()
{
    RC rc;

    CHECK_RC(m_Client->Init());

    CHECK_RC(m_Client->Connect());

    CHECK_RC(m_Client->Run());

    CHECK_RC(m_Client->Shut());

    return rc;
}
