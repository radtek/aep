#ifndef __U16_SERVER_TEST_H__
#define __U16_SERVER_TEST_H__

#include "tcp_server_test.h"

class U16ServerTest : public TcpServerTest
{
public:
    U16ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U16_SERVER_TEST_H__
