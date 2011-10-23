/**
* @file
* @brief FileClientTest类头文件.
* @author ruoxi
*
* 定义了FileClientTest类.
*/

#ifndef __FILE_CLIENT_TEST_H__
#define __FILE_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class FileClientTest
* @brief TCP客户端收发文件测试类.
*
* FileClientTest类用来测试TCP客户端收发文件功能.
* 操作一个收文件用客户端与服务端收发数据.
*/
class FileClientTest : public TcpClientTest
{
public:
    FileClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U64_CLIENT_TEST_H__
