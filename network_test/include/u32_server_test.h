/**
* @file
* @brief U32ServerTest��ͷ�ļ�.
* @author ruoxi
*
* ������U32ServerTest��.
*/

#ifndef __U32_SERVER_TEST_H__
#define __U32_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class U32ServerTest
* @brief TCP������շ�32λ�޷������Ͳ�����.
*
* U32ServerTest����������TCP������շ�32λ�޷������͹���.
* ����һ���շ�32λ�޷��������÷������ͻ����շ�����.
*/
class U32ServerTest : public TcpServerTest
{
public:
    U32ServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __U32_SERVER_TEST_H__
