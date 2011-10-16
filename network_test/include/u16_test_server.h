/**
* @file
* @brief U16TestServer类头文件.
* @author ruoxi
*
* 定义了U16TestServer类.
*/

#ifndef __U16_TEST_SERVER_H__
#define __U16_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class U16TestServer
* @brief 测试收发16位无符号类型的TCP服务端.
*
* U16TestServer类是用来测试TCP收发16位无符号类型功能的服务端.
* 与客户端互相收发一组16位无符号数.
*/
class U16TestServer : public TestTcpServer
{
public:
    U16TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U16_TEST_SERVER_H__
