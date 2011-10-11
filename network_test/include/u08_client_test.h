#ifndef __U08_CLIENT_TEST_H__
#define __U08_CLIENT_TEST_H__

#include "tcp_client_test.h"

class U08ClientTest : public TcpClientTest
{
public:
    U08ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U08_CLIENT_TEST_H__
