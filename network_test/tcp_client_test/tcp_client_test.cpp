/**
* @file
* @brief TcpClientTest��cpp�ļ�.
* @author ruoxi
*
* ʵ����TcpClientTest��.
*/

#include "tcp_client_test.h"

/**
* @param testName ������.
* @param client ������TCP�ͻ���.
*
* TcpClientTest���캯��. ���ܲ�������һ��������TCP�ͻ��˶���.
*/
TcpClientTest::TcpClientTest(const char *testName, TestTcpClient *client)
:
NetworkTest(testName),
m_Client(client)
{
}

TcpClientTest::~TcpClientTest()
{
}

/**
* @return �������.
*
* ���ڲ�����TCP�ͻ��˵Ĳ������к���.
* ��ʼ���ͻ���, ������Զ�̷����,
* ���пͻ��˳���,
* �������ͻ���.
*/
RC TcpClientTest::Run()
{
    RC rc;

    CHECK_RC(m_Client->Init());

    CHECK_RC(m_Client->Connect());

    CHECK_RC(m_Client->Run());

    CHECK_RC(m_Client->Shut());

    return rc;
}
