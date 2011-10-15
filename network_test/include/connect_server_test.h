/**
* @file
* @brief ConnectServerTest类头文件.
* @author ruoxi
*
* 定义了ConnectClientTest类.
*/

#ifndef __CONNECT_SERVER_TEST_H__
#define __CONNECT_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class ConnectServerTest
* @brief TCP服务端连接测试类.
*
* ConnectServerTest类用来测试TCP服务端连接功能.
* 操作一个连接用服务端接受远程客户端连接.
*/
class ConnectServerTest : public TcpServerTest
{
public:
    ConnectServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __CONNECT_SERVER_TEST_H__
