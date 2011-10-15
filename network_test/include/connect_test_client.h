/**
* @file
* @brief ConnectTestClient类头文件.
* @author ruoxi
*
* 定义了ConnectTestClient类.
*/

#ifndef __CONNECT_TEST_CLIENT_H__
#define __CONNECT_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class ConnectTestClient
* @brief 测试连接的TCP客户端.
*
* ConnectTestClient类是用来测试TCP连接功能的客户端.
* 连接至远程TCP服务端并收发一小段消息.
*/
class ConnectTestClient : public TestTcpClient
{
public:
    ConnectTestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
private:
    UINT32 m_Id;
};

#endif // __CONNECT_TEST_CLIENT_H__
