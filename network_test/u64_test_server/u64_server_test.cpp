#include "u64_server_test.h"

U64ServerTest::U64ServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult U64ServerTest::Check()
{
    return PASS;
}
