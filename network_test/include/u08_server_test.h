#ifndef __U08_SERVER_TEST_H__
#define __U08_SERVER_TEST_H__

#include "tcp_server_test.h"

class U08ServerTest : public TcpServerTest
{
public:
    U08ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U08_SERVER_TEST_H__
