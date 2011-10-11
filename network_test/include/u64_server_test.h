#ifndef __U64_SERVER_TEST_H__
#define __U64_SERVER_TEST_H__

#include "tcp_server_test.h"

class U64ServerTest : public TcpServerTest
{
public:
    U64ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U64_SERVER_TEST_H__
