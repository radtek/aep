#include "tcp_server_test.h"

TcpServerTest::TcpServerTest(const char *testName, TestTcpServer *server)
:
NetworkTest(testName),
m_Server(server)
{
}

TcpServerTest::~TcpServerTest()
{
}

RC TcpServerTest::Run()
{
    RC rc;

    CHECK_RC(m_Server->Init());

    CHECK_RC(m_Server->Listen());

    CHECK_RC(m_Server->Hold());

    CHECK_RC(m_Server->Shut());

    return rc;
}

NetworkTest::TestResult TcpServerTest::Check()
{
    return PASS;
}
