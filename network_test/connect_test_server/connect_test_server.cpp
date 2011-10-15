/**
* @file
* @brief ConnectTestServer类cpp文件.
* @author ruoxi
*
* 实现了ConnectTestServer类.
*/

#include "connect_test_server.h"

ConnectTestServer::ConnectTestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC ConnectTestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    printf("[Server] Thread %u executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %u - Client socket is NULL.\n", threadId);
        return OK;
    }
    string question;
    clientSocket->RecvString(question);
    printf("[Server] %u - Client said: %s\n", threadId, question.c_str());
    if (question == "Am I connected?")
    {
        string answer = "Yes!";
        printf("[Server] %u - Answering client: %s\n", threadId, answer.c_str());
        clientSocket->SendString(answer.c_str());
        m_Logger<<answer<<endl;
    }
    else
    {
        string answer = "I don't know what you are asking.\n";
        printf("[Server] %u - Answering client: %s\n", threadId, answer.c_str());
        clientSocket->SendString(answer.c_str());
    }

    clientSocket->Shut();
    return OK;
}
