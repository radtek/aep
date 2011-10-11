#include "u32_server_test.h"

U32ServerTest::U32ServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult U32ServerTest::Check()
{
    return PASS;
}
