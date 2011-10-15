/**
* @file
* @brief TcpServerTest��ͷ�ļ�.
* @author ruoxi
*
* ������TcpServerTest��.
*/

#ifndef __TCP_SERVER_TEST_H__
#define __TCP_SERVER_TEST_H__

#include "network_test.h"
#include "test_tcp_server.h"

/**
* @class TcpServerTest
* @brief TCP����˵Ĳ�����.
*
* TcpServerTest���ǲ�����TCP����˲��ԵĻ���.
* ��������һ��������TCP�����, ����������־, ������н��.
* �̳���NetworkTest, ���Ա��̳���ʵ�־���Ĳ��Լ���⹦��
*/
class TcpServerTest : public NetworkTest
{
public:
    /** @brief TcpServerTest���캯��. */
    TcpServerTest(const char *testName, TestTcpServer *server);
    /** @brief TcpServerTest��������. */
    virtual ~TcpServerTest();

    /** @brief ���ڲ�����TCP����˵Ĳ������к���. */
    virtual RC Run();

protected:
    /** @brief ������TCP�����. */
    TestTcpServer *m_Server;
};

/**
* @brief ���ڶ���һ������˲��Գ����������ĺ�.
* @param serverClass ����˵�����.
* @param testClass ����˲��Ե�����.
* @param testName ������.
* @param maxClientNum �ɷ�������ͻ�����.
*
* ����һ������˲��Գ���������.
* �������Է���˼�����˲��Զ���, �������к����������.
*/
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
