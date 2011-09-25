#include "connect_test_client.h"

ConnectTestClient::ConnectTestClient(UINT32 id)
:
m_Id(id)
{
}

RC ConnectTestClient::Run()
{
    printf("[Client] Client %u executing...\n", m_Id);

    string question = "Am I connected?";
    printf("[Client] %u - Asking server: %s\n", m_Id, question.c_str());
    m_TcpSocket->SendString(question.c_str());
    string answer;
    m_TcpSocket->RecvString(answer);
    printf("[Client] %u - Server said: %s\n", m_Id, answer.c_str());
    if (answer == "Yes!")
    {
        printf("[Client] %u - I am connected.\n", m_Id);
    }
    else
    {
        printf("[Client] %u - I am not connected.\n", m_Id);
    }
    return OK;
}
