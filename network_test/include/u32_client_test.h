/**
* @file
* @brief U32ClientTest��ͷ�ļ�.
* @author ruoxi
*
* ������U32ClientTest��.
*/

#ifndef __U32_CLIENT_TEST_H__
#define __U32_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class U32ClientTest
* @brief TCP�ͻ����շ�32λ�޷������Ͳ�����.
*
* U32ClientTest����������TCP�ͻ����շ�32λ�޷������͹���.
* ����һ���շ�32λ�޷��������ÿͻ����������շ�����.
*/
class U32ClientTest : public TcpClientTest
{
public:
    U32ClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U32_CLIENT_TEST_H__
