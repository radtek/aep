/**
* @file
* @brief U16TestServer��ͷ�ļ�.
* @author ruoxi
*
* ������U16TestServer��.
*/

#ifndef __U16_TEST_SERVER_H__
#define __U16_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class U16TestServer
* @brief �����շ�16λ�޷������͵�TCP�����.
*
* U16TestServer������������TCP�շ�16λ�޷������͹��ܵķ����.
* ��ͻ��˻����շ�һ��16λ�޷�����.
*/
class U16TestServer : public TestTcpServer
{
public:
    U16TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U16_TEST_SERVER_H__
