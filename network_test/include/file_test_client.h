/**
* @file
* @brief FileTestClient��ͷ�ļ�.
* @author ruoxi
*
* ������FileTestClient��.
*/

#ifndef __U64_TEST_CLIENT_H__
#define __U64_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class FileTestClient
* @brief �����շ��ļ���TCP�ͻ���.
*
* U64TestClient�������������շ��ļ��Ŀͻ���.
* �����˻����շ�һ���ļ�.
*/
class FileTestClient : public TestTcpClient
{
public:
    FileTestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U64_TEST_CLIENT_H__
