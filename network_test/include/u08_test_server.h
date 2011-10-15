/**
* @file
* @brief U08TestServer类头文件.
* @author ruoxi
*
* 定义了U08TestServer类.
*/

#ifndef __U08_TEST_SERVER_H__
#define __U08_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class U08TestServer
* @brief 测试收发8位无符号类型的TC服务端.
*
* U08TestServer类是用来测试TCP收发8位无符号类型功能的服务端.
* 与客户端互相收发一组8位无符号数.
*/
class U08TestServer : public TestTcpServer
{
public:
    U08TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U08_TEST_SERVER_H__
