/**
* @file
* @brief U16ClientTest类头文件.
* @author ruoxi
*
* 定义了U16ClientTest类.
*/

#ifndef __U16_CLIENT_TEST_H__
#define __U16_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class U16ClientTest
* @brief TCP客户端收发16位无符号类型测试类.
*
* U16ClientTest类用来测试TCP客户端收发16位无符号类型功能.
* 操作一个收发16位无符号类型用客户端与服务端收发数据.
*/
class U16ClientTest : public TcpClientTest
{
public:
    U16ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U16_CLIENT_TEST_H__
