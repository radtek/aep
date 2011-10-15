/**
* @file
* @brief ConnectTestClient类cpp文件.
* @author ruoxi
*
* 实现了ConnectTestClient类.
*/

#include "connect_test_client.h"

ConnectTestClient::ConnectTestClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
TestTcpClient(hostName, port, logFileName, id)
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
        m_Logger<<"Yes!"<<endl;
        printf("[Client] %u - I am connected.\n", m_Id);
    }
    else
    {
        printf("[Client] %u - I am not connected.\n", m_Id);
    }
    return OK;
}
