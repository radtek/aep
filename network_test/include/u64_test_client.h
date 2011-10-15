/**
* @file
* @brief U64TestClient��ͷ�ļ�.
* @author ruoxi
*
* ������U64TestClient��.
*/

#ifndef __U64_TEST_CLIENT_H__
#define __U64_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class U64TestClient
* @brief �����շ�64λ�޷������͵�TCP�ͻ���.
*
* U64TestClient�������������շ�64λ�޷������͵Ŀͻ���.
* �����˻����շ�һ��64λ�޷�����.
*/
class U64TestClient : public TestTcpClient
{
public:
    U64TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U64_TEST_CLIENT_H__
