/**
* @file
* @brief FileServerTest类头文件.
* @author ruoxi
*
* 定义了FileServerTest类.
*/

#ifndef __FILE_SERVER_TEST_H__
#define __FILE_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class FileServerTest
* @brief TCP服务端收发文件测试类.
*
* FileServerTest类用来测试TCP服务端收发文件功能.
* 操作一个收发文件用服务端与客户端收发数据.
*/
class FileServerTest : public TcpServerTest
{
public:
    FileServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __FILE_SERVER_TEST_H__
