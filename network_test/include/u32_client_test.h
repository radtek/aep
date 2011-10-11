#ifndef __U32_CLIENT_TEST_H__
#define __U32_CLIENT_TEST_H__

#include "tcp_client_test.h"

class U32ClientTest : public TcpClientTest
{
public:
    U32ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U32_CLIENT_TEST_H__
