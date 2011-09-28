#ifndef __TCP_CLIENT_TEST_H__
#define __TCP_CLIENT_TEST_H__

#include "network_test.h"
#include "test_tcp_client.h"

class TcpClientTest : public NetworkTest
{
public:
    TcpClientTest(const char *testName, TestTcpClient *client);
    virtual ~TcpClientTest();

    virtual RC Run();
    virtual TestResult Check();

protected:
    TestTcpClient *m_Client;
};

#define MAKE_CLIENT_TEST(clientClass, testName, id) \
int main(int argc,char* argv[]) \
{ \
    const char *hostName = argv[1]; \
    int port = atoi(argv[2]); \
    clientClass client(hostName, port, #testName".log", id); \
    TcpClientTest test(#testName, &client); \
    MASSERT(test.Run() == OK); \
    MASSERT(test.Check() == NetworkTest::PASS); \
    return 0; \
}

#endif // __TCP_CLIENT_TEST_H__
