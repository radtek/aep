/**
* @file
* @brief U16ServerTest类头文件.
* @author ruoxi
*
* 定义了U16ServerTest类.
*/

#ifndef __U16_SERVER_TEST_H__
#define __U16_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class U16ServerTest
* @brief TCP服务端收发16位无符号类型测试类.
*
* U16ServerTest类用来测试TCP服务端收发16位无符号类型功能.
* 操作一个收发16位无符号类型用服务端与客户端收发数据.
*/
class U16ServerTest : public TcpServerTest
{
public:
    U16ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U16_SERVER_TEST_H__
