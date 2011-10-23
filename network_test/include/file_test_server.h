/**
* @file
* @brief FileTestServer类头文件.
* @author ruoxi
*
* 定义了U64TestServer类.
*/

#ifndef __FILE_TEST_SERVER_H__
#define __FILE_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class FileTestServer
* @brief 测试收发文件的TCP服务端.
*
* FileTestServer类是用来测试TCP收发文件功能的服务端.
* 与客户端互相收发一组64位无符号数.
*/
class FileTestServer : public TestTcpServer
{
public:
    FileTestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __FILE_TEST_SERVER_H__
