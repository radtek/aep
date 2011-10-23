/**
* @file
* @brief FileTestClient类头文件.
* @author ruoxi
*
* 定义了FileTestClient类.
*/

#ifndef __U64_TEST_CLIENT_H__
#define __U64_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class FileTestClient
* @brief 测试收发文件的TCP客户端.
*
* U64TestClient类是用来测试收发文件的客户端.
* 与服务端互相收发一个文件.
*/
class FileTestClient : public TestTcpClient
{
public:
    FileTestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U64_TEST_CLIENT_H__
