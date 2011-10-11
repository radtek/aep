#ifndef __U32_SERVER_TEST_H__
#define __U32_SERVER_TEST_H__

#include "tcp_server_test.h"

class U32ServerTest : public TcpServerTest
{
public:
    U32ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U32_SERVER_TEST_H__
