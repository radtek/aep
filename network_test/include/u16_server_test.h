/**
* @file
* @brief U16ServerTest��ͷ�ļ�.
* @author ruoxi
*
* ������U16ServerTest��.
*/

#ifndef __U16_SERVER_TEST_H__
#define __U16_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class U16ServerTest
* @brief TCP������շ�16λ�޷������Ͳ�����.
*
* U16ServerTest����������TCP������շ�16λ�޷������͹���.
* ����һ���շ�16λ�޷��������÷������ͻ����շ�����.
*/
class U16ServerTest : public TcpServerTest
{
public:
    U16ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U16_SERVER_TEST_H__
