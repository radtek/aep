/**
* @file
* @brief DoubleServerTest��ͷ�ļ�.
* @author ruoxi
*
* ������DoubleServerTest��.
*/

#ifndef __DOUBLE_SERVER_TEST_H__
#define __DOUBLE_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class DoubleServerTest
* @brief TCP������շ�˫���ȸ������Ͳ�����.
*
* DoubleServerTest����������TCP������շ�˫���ȸ������͹���.
* ����һ���շ�˫���ȸ��������÷������ͻ����շ�����.
*/
class DoubleServerTest : public TcpServerTest
{
public:
    DoubleServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __DOUBLE_SERVER_TEST_H__
