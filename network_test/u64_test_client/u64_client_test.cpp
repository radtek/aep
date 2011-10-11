#include "u64_client_test.h"

U64ClientTest::U64ClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult U64ClientTest::Check()
{
    return PASS;
}
