/**
* @file
* @brief U08TestClient��ͷ�ļ�.
* @author ruoxi
*
* ������U08TestClient��.
*/

#ifndef __U08_TEST_CLIENT_H__
#define __U08_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class U08TestClient
* @brief �����շ�8λ�޷������͵�TCP�ͻ���.
*
* U08TestClient�������������շ�8λ�޷������͵Ŀͻ���.
* �����˻����շ�һ��8λ�޷�����.
*/
class U08TestClient : public TestTcpClient
{
public:
    U08TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U08_TEST_CLIENT_H__
