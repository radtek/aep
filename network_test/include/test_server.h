#ifndef __TEST_SERVER_H__
#define __TEST_SERVER_H__

#include "net_socket.h"

class TestServer
{
public:
    TestServer();
    ~TestServer();

    int Initialize();
    int Shutdown();

    int Service(int port);
    void Stop();
    bool IsListening();

    static DWORD WINAPI ServiceThread(LPVOID lparam);
    static void Print(NetSocket *socket);

private:
    Socket *m_ListenSocket;
    bool m_Continue;
    bool m_Listening;
};

#endif // __TEST_SERVER_H__
