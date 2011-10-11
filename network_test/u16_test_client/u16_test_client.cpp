#include "u16_test_client.h"

U16TestClient::U16TestClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
TestTcpClient(hostName, port, logFileName, id)
{
}

RC U16TestClient::Run()
{
    RC rc;

    printf("[Client] Client %u executing...\n", m_Id);
    UINT16 min = 0, max = UINT16_MAX;
    UINT16 data = min;
    while (true)
    {
        printf("[Client] %u - Sending UINT16: %u\n", m_Id, data);
        CHECK_RC(m_TcpSocket->Send16(data));
        UINT16 temp;
        CHECK_RC(m_TcpSocket->Recv16(temp));
        printf("[Client] %u - Recieved UINT16: %u\n", m_Id, temp);
        m_Logger<<(UINT32)data<<endl;
        if (data == max)
        {
            break;
        }
        ++data;
    }

    return OK;
}
