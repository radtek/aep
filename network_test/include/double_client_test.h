#ifndef __DOUBLE_CLIENT_TEST_H__
#define __DOUBLE_CLIENT_TEST_H__

#include "tcp_client_test.h"

class DoubleClientTest : public TcpClientTest
{
public:
    DoubleClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __DOUBLE_CLIENT_TEST_H__
