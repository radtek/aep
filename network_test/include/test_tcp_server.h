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
    bool IsListening();
    void Stop();

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
    bool m_Continue;
    bool m_Listening;
};

#endif // __TEST_TCP_SERVER_H__
