#ifndef __TCP_SERVER_TEST_H__
#define __TCP_SERVER_TEST_H__

#include "network_test.h"
#include "test_tcp_server.h"

class TcpServerTest : public NetworkTest
{
public:
    TcpServerTest(const char *testName, TestTcpServer *server);
    virtual ~TcpServerTest();

    virtual RC Run();
    virtual TestResult Check() = 0;

protected:
    TestTcpServer *m_Server;
};

#define MAKE_SERVER_TEST(serverClass, testClass, testName, maxClientNum) \
int main(int argc,char* argv[]) \
{ \
    int port = atoi(argv[1]); \
    serverClass server(port, #testName".log", maxClientNum); \
    testClass test(#testName, &server); \
    MASSERT(test.Run() == OK); \
    MASSERT(test.Check() == NetworkTest::PASS); \
    return 0; \
}

#endif // __TCP_SERVER_TEST_H__
