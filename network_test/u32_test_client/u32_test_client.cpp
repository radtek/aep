#include "u08_test_client.h"

U08TestClient::U08TestClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
TestTcpClient(hostName, port, logFileName, id)
{
}

RC U08TestClient::Run()
{
    RC rc;

    printf("[Client] Client %u executing...\n", m_Id);
    UINT08 min = 0, max = UINT08_MAX;
    UINT08 data = min;
    while (true)
    {
        printf("[Client] %u - Sending UINT08: %u\n", m_Id, data);
        CHECK_RC(m_TcpSocket->Send08(data));
        UINT08 temp;
        CHECK_RC(m_TcpSocket->Recv08(temp));
        printf("[Client] %u - Recieved UINT08: %u\n", m_Id, temp);
        m_Logger<<data<<endl;
        if (data == max)
        {
            break;
        }
        ++data;
    }

    return OK;
}
