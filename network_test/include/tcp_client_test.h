/**
* @file
* @brief TcpClientTest��ͷ�ļ�.
* @author ruoxi
*
* ������TcpClientTest��.
*/

#ifndef __TCP_CLIENT_TEST_H__
#define __TCP_CLIENT_TEST_H__

#include "network_test.h"
#include "test_tcp_client.h"

/**
* @class TcpClientTest
* @brief TCP�ͻ��˵Ĳ�����.
*
* TcpClientTest���ǲ�����TCP�ͻ��˲��ԵĻ���.
* ��������һ��������TCP�ͻ���, ����������־, ������н��.
* �̳���NetworkTest, ���Ա��̳���ʵ�־���Ĳ��Լ���⹦��
*/
class TcpClientTest : public NetworkTest
{
public:
    /** @brief TcpClientTest���캯��. */
    TcpClientTest(const char *testName, TestTcpClient *client);
    /** @brief TcpClientTest��������. */
    virtual ~TcpClientTest();

    /** @brief ���ڲ�����TCP�ͻ��˵Ĳ������к���. */
    RC Run();

protected:
    /** @brief ������TCP�ͻ���. */
    TestTcpClient *m_Client;
};

/**
* @brief ���ڶ���һ���ͻ��˲��Գ����������ĺ�.
* @param clientClass �ͻ��˵�����.
* @param testClass �ͻ��˲��Ե�����.
* @param testName ������.
* @param id �ͻ���ID.
*
* ����һ���ͻ��˲��Գ���������.
* �������Կͻ��˼��ͻ��˲��Զ���, �������к����������.
*/
#define MAKE_CLIENT_TEST(clientClass, testClass, testName, id) \
int main(int argc,char* argv[]) \
{ \
    const char *hostName = argv[1]; \
    int port = atoi(argv[2]); \
    clientClass client(hostName, port, #testName".log", id); \
    testClass test(#testName, &client); \
    MASSERT(test.Run() == OK); \
    MASSERT(test.Check() == NetworkTest::PASS); \
    return 0; \
}

#endif // __TCP_CLIENT_TEST_H__
