#ifndef __CONNECT_TEST_CLIENT_H__
#define __CONNECT_TEST_CLIENT_H__

#include "test_tcp_client.h"

class ConnectTestClient : public TestTcpClient
{
public:
    ConnectTestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
private:
    UINT32 m_Id;
};

#endif // __CONNECT_TEST_CLIENT_H__
