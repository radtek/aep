#ifndef __TEST_TCP_CLIENT_H__
#define __TEST_TCP_CLIENT_H__

#include "tcp_socket.h"
#include <fstream>

using namespace std;

class TestTcpClient
{
public:
    TestTcpClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    ~TestTcpClient();

    RC Init();
    RC Shut();

    RC Connect();

    virtual RC Run() = 0;

protected:
    TcpSocket *m_TcpSocket;
    const char *m_HostName;
    int m_Port;
    ofstream m_Logger;
    UINT32 m_Id;
};

#endif // __TEST_TCP_CLIENT_H__
