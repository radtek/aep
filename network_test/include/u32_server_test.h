/**
* @file
* @brief U32ServerTest类头文件.
* @author ruoxi
*
* 定义了U32ServerTest类.
*/

#ifndef __U32_SERVER_TEST_H__
#define __U32_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class U32ServerTest
* @brief TCP服务端收发32位无符号类型测试类.
*
* U32ServerTest类用来测试TCP服务端收发32位无符号类型功能.
* 操作一个收发32位无符号类型用服务端与客户端收发数据.
*/
class U32ServerTest : public TcpServerTest
{
public:
    U32ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U32_SERVER_TEST_H__
