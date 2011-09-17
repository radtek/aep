#include "socket.h"

Socket::Socket()
:
m_ErrorHandler(NULL)
{
}

UINT08 Socket::Recv08()
{
    UINT08 data = 0;
    Recv(&data, 1);
    return data;
}

void Socket::Send08(UINT08 data)
{
    Send(&data, 1);
}

UINT16 Socket::Recv16()
{
    UINT08 bytes[2] = { 0, };
    UINT16 data;
    Recv(bytes, sizeof(bytes));
    data  = bytes[0];
    data |= bytes[1] << 8;
    return data;
}

void Socket::Send16(UINT16 data)
{
    UINT08 bytes[2];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)(data >> 8);
    Send(bytes, sizeof(bytes));
}

UINT32 Socket::Recv32()
{
    UINT08 bytes[4] = { 0, };
    UINT32 data;
    Recv(bytes, sizeof(bytes));
    data  = bytes[0];
    data |= bytes[1] << 8;
    data |= bytes[2] << 16;
    data |= bytes[3] << 24;
    return data;
}

void Socket::Send32(UINT32 data)
{
    UINT08 bytes[4];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)((data >> 8) & 0xFF);
    bytes[2] = (UINT08)((data >> 16) & 0xFF);
    bytes[3] = (UINT08)(data >> 24);
    Send(bytes, sizeof(bytes));
}

UINT64 Socket::Recv64()
{
    UINT08 bytes[8] = { 0, };
    UINT64 data;
    Recv(bytes, sizeof(bytes));
    data  = (UINT64)bytes[0];
    data |= (UINT64)bytes[1] << 8;
    data |= (UINT64)bytes[2] << 16;
    data |= (UINT64)bytes[3] << 24;
    data |= (UINT64)bytes[4] << 32;
    data |= (UINT64)bytes[5] << 40;
    data |= (UINT64)bytes[6] << 48;
    data |= (UINT64)bytes[7] << 56;
    return data;
}

void Socket::Send64(UINT64 data)
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
    Send(bytes, sizeof(bytes));
}

double Socket::RecvDouble()
{
    UINT64 data = Recv64();
    return *(double *)&data;
}

void Socket::SendDouble(double data)
{
    Send64(*(UINT64 *)&data);
}

// We could use null-terminated strings, but sending the length is more
// efficient for the receiver.
string Socket::RecvString()
{
    UINT32 length = Recv32();
    string str;
    str.resize(length);
    Recv(&str[0], length);
    return str;
}

void Socket::SendString(const char *str)
{
    UINT32 length = (UINT32)strlen(str);
    Send32(length);
    Send(str, length);
}

void Socket::InstallErrorHandler(ErrorHandlerFunc func, void *args)
{
    m_ErrorHandler = func;
    m_ErrorHandlerArgs = args;
}

void Socket::CallErrorHandler()
{
    if (m_ErrorHandler)
        m_ErrorHandler(m_ErrorHandlerArgs);
}
