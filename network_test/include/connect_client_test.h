#ifndef __CONNECT_CLIENT_TEST_H__
#define __CONNECT_CLIENT_TEST_H__

#include "tcp_client_test.h"

class ConnectClientTest : public TcpClientTest
{
public:
    ConnectClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __CONNECT_CLIENT_TEST_H__