#ifndef __U16_CLIENT_TEST_H__
#define __U16_CLIENT_TEST_H__

#include "tcp_client_test.h"

class U16ClientTest : public TcpClientTest
{
public:
    U16ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U16_CLIENT_TEST_H__
