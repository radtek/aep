#ifndef __U32_TEST_SERVER_H__
#define __U32_TEST_SERVER_H__

#include "test_tcp_server.h"

class U32TestServer : public TestTcpServer
{
public:
    U32TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U32_TEST_SERVER_H__
