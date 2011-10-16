/**
* @file
* @brief U64TestServer��ͷ�ļ�.
* @author ruoxi
*
* ������U64TestServer��.
*/

#ifndef __U64_TEST_SERVER_H__
#define __U64_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class U64TestServer
* @brief �����շ�64λ�޷������͵�TCP�����.
*
* U64TestServer������������TCP�շ�64λ�޷������͹��ܵķ����.
* ��ͻ��˻����շ�һ��64λ�޷�����.
*/
class U64TestServer : public TestTcpServer
{
public:
    U64TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U64_TEST_SERVER_H__
