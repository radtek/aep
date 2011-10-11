#ifndef __TEST_TCP_SERVER_H__
#define __TEST_TCP_SERVER_H__

#include "tcp_socket.h"
#include <fstream>

using namespace std;

class TestTcpServer
{
public:
    TestTcpServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    ~TestTcpServer();

    RC Init();
    RC Shut();

    RC Listen();
    RC Hold();

    const char *GetLogFileName();

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
    UINT32 m_MaxClientNum;
    volatile UINT32 m_RunningClientNum;
    const char *m_LogFileName;
    ofstream m_Logger;
};

#endif // __TEST_TCP_SERVER_H__
