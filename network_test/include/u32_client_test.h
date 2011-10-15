/**
* @file
* @brief U32ClientTest类头文件.
* @author ruoxi
*
* 定义了U32ClientTest类.
*/

#ifndef __U32_CLIENT_TEST_H__
#define __U32_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class U32ClientTest
* @brief TCP客户端收发32位无符号类型测试类.
*
* U32ClientTest类用来测试TCP客户端收发32位无符号类型功能.
* 操作一个收发32位无符号类型用客户端与服务端收发数据.
*/
class U32ClientTest : public TcpClientTest
{
public:
    U32ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U32_CLIENT_TEST_H__
