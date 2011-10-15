/**
* @file
* @brief DoubleTestServer类头文件.
* @author ruoxi
*
* 定义了DoubleTestServer类.
*/

#ifndef __DOUBLE_TEST_SERVER_H__
#define __DOUBLE_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class DoubleTestServer
* @brief 测试收发双精度浮点类型的TC服务端.
*
* DoubleTestServer类是用来测试TCP收发双精度浮点类型功能的服务端.
* 与客户端互相收发一组双精度浮点数.
*/
class DoubleTestServer : public TestTcpServer
{
public:
    DoubleTestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __DOUBLE_TEST_SERVER_H__
