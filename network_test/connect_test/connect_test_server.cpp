#include "connect_test_server.h"

RC ConnectTestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    printf("[Server] Thread %ul executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %ul - Client socket is NULL.\n", threadId);
        return OK;
    }
    string question;
    clientSocket->RecvStr(question);
    printf("[Server] %ul - Client said: %s\n", threadId, question.c_str());
    if (question == "Am I connected?")
    {
        string answer = "Yes!";
        printf("[Server] %ul - Answering client: %s.\n", threadId, answer.c_str());
        clientSocket->SendStr(answer.c_str());
    }
    else
    {
        string answer = "I don't know what you are asking.\n";
        printf("[Server] %ul - Answering client: %s.\n", threadId, answer.c_str());
        clientSocket->SendStr(answer.c_str());
    }

    clientSocket->Shut();
    return OK;
}
