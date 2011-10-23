/**
* @file
* @brief FileTestServer��ͷ�ļ�.
* @author ruoxi
*
* ������U64TestServer��.
*/

#ifndef __FILE_TEST_SERVER_H__
#define __FILE_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class FileTestServer
* @brief �����շ��ļ���TCP�����.
*
* FileTestServer������������TCP�շ��ļ����ܵķ����.
* ��ͻ��˻����շ�һ��64λ�޷�����.
*/
class FileTestServer : public TestTcpServer
{
public:
    FileTestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __FILE_TEST_SERVER_H__
