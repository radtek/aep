#ifndef __TEST_TCP_SERVER_H__
#define __TEST_TCP_SERVER_H__

#include "tcp_socket.h"

class TestTcpServer
{
public:
    TestTcpServer();
    ~TestTcpServer();

    RC Init();
    RC Shut();

    RC Listen(int port);

protected:
    struct ThreadInfo
    {
        DWORD ThreadId;
        TestTcpServer *Server;
        TcpSocket *ClientSocket;
    };
    static DWORD WINAPI Dispatch(LPVOID lparam);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0) = 0;

    TcpSocket *m_TcpSocket;
    int m_Port;
};

#endif // __TEST_TCP_SERVER_H__
