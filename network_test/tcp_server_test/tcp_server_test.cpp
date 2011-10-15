/**
* @file
* @brief TcpServerTest��cpp�ļ�.
* @author ruoxi
*
* ʵ����TcpServerTest��.
*/

#include "tcp_server_test.h"

/**
* @param testName ������.
* @param server ������TCP�����.
*
* TestTcpServer���캯��. ���ܲ�������һ��������TCP����˶���.
*/
TcpServerTest::TcpServerTest(const char *testName, TestTcpServer *server)
:
NetworkTest(testName),
m_Server(server)
{
}

TcpServerTest::~TcpServerTest()
{
}

/**
* @return �������.
*
* ���ڲ�����TCP����˵Ĳ������к���.
* ��ʼ�������, �������״̬��ʼ����,
* ���ͻ������򵽿ɷ�������ͻ��������������,
* ֮��ȴ����з����߳̽���,
* �����������.
*/
RC TcpServerTest::Run()
{
    RC rc;

    CHECK_RC(m_Server->Init());

    CHECK_RC(m_Server->Listen());

    CHECK_RC(m_Server->Hold());

    CHECK_RC(m_Server->Shut());

    return rc;
}
