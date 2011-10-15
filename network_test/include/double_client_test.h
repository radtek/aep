/**
* @file
* @brief DoubleClientTest类头文件.
* @author ruoxi
*
* 定义了DoubleClientTest类.
*/

#ifndef __DOUBLE_CLIENT_TEST_H__
#define __DOUBLE_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class DoubleClientTest
* @brief TCP客户端收发双精度浮点类型测试类.
*
* DoubleClientTest类用来测试TCP客户端收发双精度浮点类型功能.
* 操作一个收发双精度浮点类型用客户端与服务端收发数据.
*/
class DoubleClientTest : public TcpClientTest
{
public:
    DoubleClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __DOUBLE_CLIENT_TEST_H__
