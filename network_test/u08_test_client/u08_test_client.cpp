#include "u08_test_client.h"

U08TestClient::U08TestClient(UINT32 id)
:
m_Id(id)
{
}

RC U08TestClient::Run()
{
    printf("[Client] Client %u executing...\n", m_Id);

    UINT08 min = 0, max = 255;
    UINT08 data = min;
    while (true)
    {
        printf("[Client] %u - Sending UINT08: %u\n", m_Id, data);
        m_TcpSocket->Send08(data);
        UINT08 temp;
        m_TcpSocket->Recv08(temp);
        printf("[Client] %u - Recieved UINT08: %u\n", m_Id, temp);
        if (data == max)
        {
            break;
        }
        ++data;
    }

    return OK;
}
