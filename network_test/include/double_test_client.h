/**
* @file
* @brief DoubleTestClient类头文件.
* @author ruoxi
*
* 定义了DoubleTestClient类.
*/

#ifndef __DOUBLE_TEST_CLIENT_H__
#define __DOUBLE_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class DoubleTestClient
* @brief 测试收发双精度浮点类型的TCP客户端.
*
* DoubleTestClient类是用来测试收发双精度浮点类型的客户端.
* 与服务端互相收发一组双精度浮点数.
*/
class DoubleTestClient : public TestTcpClient
{
public:
    DoubleTestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __DOUBLE_TEST_CLIENT_H__
