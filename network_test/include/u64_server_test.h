/**
* @file
* @brief U64ServerTest类头文件.
* @author ruoxi
*
* 定义了U64ServerTest类.
*/

#ifndef __U64_SERVER_TEST_H__
#define __U64_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class U64ServerTest
* @brief TCP服务端收发64位无符号类型测试类.
*
* U64ServerTest类用来测试TCP服务端收发64位无符号类型功能.
* 操作一个收发64位无符号类型用服务端与客户端收发数据.
*/
class U64ServerTest : public TcpServerTest
{
public:
    U64ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U64_SERVER_TEST_H__
