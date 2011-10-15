/**
* @file
* @brief U64ClientTest类头文件.
* @author ruoxi
*
* 定义了U64ClientTest类.
*/

#ifndef __U64_CLIENT_TEST_H__
#define __U64_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class U64ClientTest
* @brief TCP客户端收发64位无符号类型测试类.
*
* U64ClientTest类用来测试TCP客户端收发64位无符号类型功能.
* 操作一个收发64位无符号类型用客户端与服务端收发数据.
*/
class U64ClientTest : public TcpClientTest
{
public:
    U64ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U64_CLIENT_TEST_H__
