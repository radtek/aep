/**
* @file
* @brief ConnectTestServer类头文件.
* @author ruoxi
*
* 定义了ConnectTestServer类.
*/

#ifndef __CONNECT_TEST_SERVER_H__
#define __CONNECT_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class ConnectTestServer
* @brief 测试连接的TC服务端.
*
* ConnectTestServer类是用来测试TCP连接功能的服务端.
* 接受连接进的TCP客户端并收发一小段消息.
*/
class ConnectTestServer : public TestTcpServer
{
public:
    ConnectTestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __CONNECT_TEST_SERVER_H__
