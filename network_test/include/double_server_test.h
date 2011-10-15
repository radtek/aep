/**
* @file
* @brief DoubleServerTest类头文件.
* @author ruoxi
*
* 定义了DoubleServerTest类.
*/

#ifndef __DOUBLE_SERVER_TEST_H__
#define __DOUBLE_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class DoubleServerTest
* @brief TCP服务端收发双精度浮点类型测试类.
*
* DoubleServerTest类用来测试TCP服务端收发双精度浮点类型功能.
* 操作一个收发双精度浮点类型用服务端与客户端收发数据.
*/
class DoubleServerTest : public TcpServerTest
{
public:
    DoubleServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __DOUBLE_SERVER_TEST_H__
