/**
* @file
* @brief FileTestClient类cpp文件.
* @author ruoxi
*
* 实现了FileTestClient类.
*/

#include "file_test_client.h"

extern const char *clientSendFileName;
extern const char *clientRecvFileName;

FileTestClient::FileTestClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
TestTcpClient(hostName, port, logFileName, id)
{
}

RC FileTestClient::Run()
{
    RC rc;

    printf("[Client] Client %u executing...\n", m_Id);
    printf("[Client] %u - Sending file: %s\n", m_Id, clientSendFileName);
    CHECK_RC(m_TcpSocket->SendFile(clientSendFileName));
    printf("[Client] %u - Recieved file: %s\n", m_Id, clientRecvFileName);
    CHECK_RC(m_TcpSocket->RecvFile(clientRecvFileName));

    return OK;
}
