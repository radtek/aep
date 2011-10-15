/**
* @file
* @brief U08ServerTest类头文件.
* @author ruoxi
*
* 定义了U08ServerTest类.
*/

#ifndef __U08_SERVER_TEST_H__
#define __U08_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class U08ServerTest
* @brief TCP服务端收发8位无符号类型测试类.
*
* U08ServerTest类用来测试TCP服务端收发8位无符号类型功能.
* 操作一个收发8位无符号类型用服务端与客户端收发数据.
*/
class U08ServerTest : public TcpServerTest
{
public:
    U08ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U08_SERVER_TEST_H__
