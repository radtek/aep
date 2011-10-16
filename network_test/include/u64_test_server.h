/**
* @file
* @brief U64TestServer类头文件.
* @author ruoxi
*
* 定义了U64TestServer类.
*/

#ifndef __U64_TEST_SERVER_H__
#define __U64_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class U64TestServer
* @brief 测试收发64位无符号类型的TCP服务端.
*
* U64TestServer类是用来测试TCP收发64位无符号类型功能的服务端.
* 与客户端互相收发一组64位无符号数.
*/
class U64TestServer : public TestTcpServer
{
public:
    U64TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U64_TEST_SERVER_H__
