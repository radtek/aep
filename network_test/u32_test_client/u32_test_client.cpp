/**
* @file
* @brief U32TestClient类cpp文件.
* @author ruoxi
*
* 实现了U32TestClient类.
*/

#include "u32_test_client.h"

U32TestClient::U32TestClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
TestTcpClient(hostName, port, logFileName, id)
{
}

RC U32TestClient::Run()
{
    RC rc;

    printf("[Client] Client %u executing...\n", m_Id);
    UINT32 min = UINT32_MAX - UINT16_MAX, max = UINT32_MAX;
    UINT32 data = min;
    while (true)
    {
        printf("[Client] %u - Sending UINT32: %u\n", m_Id, data);
        CHECK_RC(m_TcpSocket->Send32(data));
        UINT32 temp;
        CHECK_RC(m_TcpSocket->Recv32(temp));
        printf("[Client] %u - Recieved UINT32: %u\n", m_Id, temp);
        m_Logger<<data<<endl;
        if (data == max)
        {
            break;
        }
        ++data;
    }

    return OK;
}
