/**
* @file
* @brief U08ClientTest类头文件.
* @author ruoxi
*
* 定义了U08ClientTest类.
*/

#ifndef __U08_CLIENT_TEST_H__
#define __U08_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class U08ClientTest
* @brief TCP客户端收发8位无符号类型测试类.
*
* U08ClientTest类用来测试TCP客户端收发8位无符号类型功能.
* 操作一个收发8位无符号类型用客户端与服务端收发数据.
*/
class U08ClientTest : public TcpClientTest
{
public:
    U08ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U08_CLIENT_TEST_H__
