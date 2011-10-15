/**
* @file
* @brief U08ClientTest��ͷ�ļ�.
* @author ruoxi
*
* ������U08ClientTest��.
*/

#ifndef __U08_CLIENT_TEST_H__
#define __U08_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class U08ClientTest
* @brief TCP�ͻ����շ�8λ�޷������Ͳ�����.
*
* U08ClientTest����������TCP�ͻ����շ�8λ�޷������͹���.
* ����һ���շ�8λ�޷��������ÿͻ����������շ�����.
*/
class U08ClientTest : public TcpClientTest
{
public:
    U08ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U08_CLIENT_TEST_H__
