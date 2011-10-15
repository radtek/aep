/**
* @file
* @brief ConnectClientTest类头文件.
* @author ruoxi
*
* 定义了ConnectClientTest类.
*/

#ifndef __CONNECT_CLIENT_TEST_H__
#define __CONNECT_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class ConnectClientTest
* @brief TCP客户端连接测试类.
*
* ConnectClientTest类用来测试TCP客户端连接功能.
* 操作一个连接用客户端连接至远程服务端.
*/
class ConnectClientTest : public TcpClientTest
{
public:
    ConnectClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __CONNECT_CLIENT_TEST_H__
