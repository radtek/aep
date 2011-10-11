#include "u32_client_test.h"

U32ClientTest::U32ClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult U32ClientTest::Check()
{
    return PASS;
}
