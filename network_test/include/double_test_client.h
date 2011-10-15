/**
* @file
* @brief DoubleTestClient��ͷ�ļ�.
* @author ruoxi
*
* ������DoubleTestClient��.
*/

#ifndef __DOUBLE_TEST_CLIENT_H__
#define __DOUBLE_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class DoubleTestClient
* @brief �����շ�˫���ȸ������͵�TCP�ͻ���.
*
* DoubleTestClient�������������շ�˫���ȸ������͵Ŀͻ���.
* �����˻����շ�һ��˫���ȸ�����.
*/
class DoubleTestClient : public TestTcpClient
{
public:
    DoubleTestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __DOUBLE_TEST_CLIENT_H__
