#ifndef __U64_CLIENT_TEST_H__
#define __U64_CLIENT_TEST_H__

#include "tcp_client_test.h"

class U64ClientTest : public TcpClientTest
{
public:
    U64ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U64_CLIENT_TEST_H__
