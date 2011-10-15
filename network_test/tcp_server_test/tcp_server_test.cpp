/**
* @file
* @brief TcpServerTest类cpp文件.
* @author ruoxi
*
* 实现了TcpServerTest类.
*/

#include "tcp_server_test.h"

/**
* @param testName 测试名.
* @param server 测试用TCP服务端.
*
* TestTcpServer构造函数. 接受测试名及一个测试用TCP服务端对象.
*/
TcpServerTest::TcpServerTest(const char *testName, TestTcpServer *server)
:
NetworkTest(testName),
m_Server(server)
{
}

TcpServerTest::~TcpServerTest()
{
}

/**
* @return 结果代码.
*
* 用于测试用TCP服务端的测试运行函数.
* 初始化服务端, 进入监听状态开始服务,
* 待客户端数打到可服务的最大客户端数后结束监听,
* 之后等待所有服务线程结束,
* 最后清理服务端.
*/
RC TcpServerTest::Run()
{
    RC rc;

    CHECK_RC(m_Server->Init());

    CHECK_RC(m_Server->Listen());

    CHECK_RC(m_Server->Hold());

    CHECK_RC(m_Server->Shut());

    return rc;
}
