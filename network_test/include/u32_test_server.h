/**
* @file
* @brief U32TestServer类头文件.
* @author ruoxi
*
* 定义了U32TestServer类.
*/

#ifndef __U32_TEST_SERVER_H__
#define __U32_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class U32TestServer
* @brief 测试收发32位无符号类型的TC服务端.
*
* U32TestServer类是用来测试TCP收发32位无符号类型功能的服务端.
* 与客户端互相收发一组32位无符号数.
*/
class U32TestServer : public TestTcpServer
{
public:
    U32TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U32_TEST_SERVER_H__
