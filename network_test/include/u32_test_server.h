/**
* @file
* @brief U32TestServer��ͷ�ļ�.
* @author ruoxi
*
* ������U32TestServer��.
*/

#ifndef __U32_TEST_SERVER_H__
#define __U32_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class U32TestServer
* @brief �����շ�32λ�޷������͵�TC�����.
*
* U32TestServer������������TCP�շ�32λ�޷������͹��ܵķ����.
* ��ͻ��˻����շ�һ��32λ�޷�����.
*/
class U32TestServer : public TestTcpServer
{
public:
    U32TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U32_TEST_SERVER_H__
