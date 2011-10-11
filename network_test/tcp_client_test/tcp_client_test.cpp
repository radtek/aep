#include "tcp_client_test.h"

TcpClientTest::TcpClientTest(const char *testName, TestTcpClient *client)
:
NetworkTest(testName),
m_Client(client)
{
}

TcpClientTest::~TcpClientTest()
{
}

RC TcpClientTest::Run()
{
    RC rc;

    CHECK_RC(m_Client->Init());

    CHECK_RC(m_Client->Connect());

    CHECK_RC(m_Client->Run());

    CHECK_RC(m_Client->Shut());

    return rc;
}
