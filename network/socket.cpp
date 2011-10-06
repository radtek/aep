#include "socket.h"
#include "massert.h"
#include <winsock2.h>

RC Socket::Init()
{
    WSADATA wsaData;
    if (SOCKET_ERROR == WSAStartup(MAKEWORD(2,2), &wsaData))
    {
        return RC::WINSOCK_INIT_ERROR;
    }
    return OK;
}

RC Socket::Shut()
{
    if (SOCKET_ERROR == WSACleanup())
    {
        return RC::WINSOCK_SHUT_ERROR;
    }
    return OK;
}

Socket::Socket()
{
}

Socket::~Socket()
{
}

RC Socket::Recv08(UINT08 &data)
{
    return Recv(&data, 1);
}

RC Socket::Send08(UINT08 data)
{
    return Send(&data, 1);
}

RC Socket::Recv16(UINT16 &data)
{
    RC rc;
    UINT08 bytes[2] = { 0, };
    CHECK_RC(Recv(bytes, sizeof(bytes)));
    data  = bytes[0];
    data |= bytes[1] << 8;
    return rc;
}

RC Socket::Send16(UINT16 data)
{
    UINT08 bytes[2];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)(data >> 8);
    return Send(bytes, sizeof(bytes));
}

RC Socket::Recv32(UINT32 &data)
{
    RC rc;
    UINT08 bytes[4] = { 0, };
    CHECK_RC(Recv(bytes, sizeof(bytes)));
    data  = bytes[0];
    data |= bytes[1] << 8;
    data |= bytes[2] << 16;
    data |= bytes[3] << 24;
    return rc;
}

RC Socket::Send32(UINT32 data)
{
    UINT08 bytes[4];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)((data >> 8) & 0xFF);
    bytes[2] = (UINT08)((data >> 16) & 0xFF);
    bytes[3] = (UINT08)(data >> 24);
    return Send(bytes, sizeof(bytes));
}

RC Socket::Recv64(UINT64 &data)
{
    RC rc;
    UINT08 bytes[8] = { 0, };
    CHECK_RC(Recv(bytes, sizeof(bytes)));
    data  = (UINT64)bytes[0];
    data |= (UINT64)bytes[1] << 8;
    data |= (UINT64)bytes[2] << 16;
    data |= (UINT64)bytes[3] << 24;
    data |= (UINT64)bytes[4] << 32;
    data |= (UINT64)bytes[5] << 40;
    data |= (UINT64)bytes[6] << 48;
    data |= (UINT64)bytes[7] << 56;
    return rc;
}

RC Socket::Send64(UINT64 data)
{
    UINT08 bytes[8];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)((data >> 8) & 0xFF);
    bytes[2] = (UINT08)((data >> 16) & 0xFF);
    bytes[3] = (UINT08)((data >> 24) & 0xFF);
    bytes[4] = (UINT08)((data >> 32) & 0xFF);
    bytes[5] = (UINT08)((data >> 40) & 0xFF);
    bytes[6] = (UINT08)((data >> 48) & 0xFF);
    bytes[7] = (UINT08)(data >> 56);
    return Send(bytes, sizeof(bytes));
}

RC Socket::RecvDouble(double &data)
{
    RC rc;
    UINT64 temp;
    CHECK_RC(Recv64(temp));
    data = static_cast<double>(temp);
}

RC Socket::SendDouble(double data)
{
    UINT64 temp = static_cast<UINT64>(data);
    return Send64(temp);
}

RC Socket::RecvString(string &str)
{
    RC rc;
    UINT32 length;
    CHECK_RC(Recv32(length));
    str.resize(length);
    return Recv(&str[0], length);
}

RC Socket::SendString(const char *str)
{
    RC rc;
    MASSERT(str != 0);
    UINT32 length = (UINT32)strlen(str);
    CHECK_RC(Send32(length));
    CHECK_RC(Send(str, length));
}

int Socket::GetLastError()
{
    return WSAGetLastError();
}
