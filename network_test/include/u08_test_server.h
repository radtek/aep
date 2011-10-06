#ifndef __U08_TEST_SERVER_H__
#define __U08_TEST_SERVER_H__

#include "test_tcp_server.h"

class U08TestServer : public TestTcpServer
{
public:
    U08TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U08_TEST_SERVER_H__
