/*
 * NVIDIA_COPYRIGHT_BEGIN
 *
 * Copyright 1999-2011 by NVIDIA Corporation.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 *
 * NVIDIA_COPYRIGHT_END
 */

#include "sockchip.h"
#include "socket.h"
#include <string.h>

Socket::Socket()
: ErrorHandler(NULL)
{
}

SockChipCommand Socket::RecvCommand()
{
    return (SockChipCommand)Recv16();
}

void Socket::SendCommand(SockChipCommand Command)
{
    Send16(Command);
}

NvU008 Socket::Recv08()
{
    NvU008 Data = 0;
    Recv(&Data, 1);
    return Data;
}

void Socket::Send08(NvU008 Data)
{
    Send(&Data, 1);
}

NvU016 Socket::Recv16()
{
    NvU008 Bytes[2] = { 0, };
    NvU016 Data;
    Recv(Bytes, sizeof(Bytes));
    Data  = Bytes[0];
    Data |= Bytes[1] << 8;
    return Data;
}

void Socket::Send16(NvU016 Data)
{
    NvU008 Bytes[2];
    Bytes[0] = (NvU008)(Data & 0xFF);
    Bytes[1] = (NvU008)(Data >> 8);
    Send(Bytes, sizeof(Bytes));
}

NvU032 Socket::Recv32()
{
    NvU008 Bytes[4] = { 0, };
    NvU032 Data;
    Recv(Bytes, sizeof(Bytes));
    Data  = Bytes[0];
    Data |= Bytes[1] << 8;
    Data |= Bytes[2] << 16;
    Data |= Bytes[3] << 24;
    return Data;
}

void Socket::Send32(NvU032 Data)
{
    NvU008 Bytes[4];
    Bytes[0] = (NvU008)(Data & 0xFF);
    Bytes[1] = (NvU008)((Data >> 8) & 0xFF);
    Bytes[2] = (NvU008)((Data >> 16) & 0xFF);
    Bytes[3] = (NvU008)(Data >> 24);
    Send(Bytes, sizeof(Bytes));
}

NvU064 Socket::Recv64()
{
    NvU008 Bytes[8] = { 0, };
    NvU064 Data;
    Recv(Bytes, sizeof(Bytes));
    Data  = (NvU064)Bytes[0];
    Data |= (NvU064)Bytes[1] << 8;
    Data |= (NvU064)Bytes[2] << 16;
    Data |= (NvU064)Bytes[3] << 24;
    Data |= (NvU064)Bytes[4] << 32;
    Data |= (NvU064)Bytes[5] << 40;
    Data |= (NvU064)Bytes[6] << 48;
    Data |= (NvU064)Bytes[7] << 56;
    return Data;
}

void Socket::Send64(NvU064 Data)
{
    NvU008 Bytes[8];
    Bytes[0] = (NvU008)(Data & 0xFF);
    Bytes[1] = (NvU008)((Data >> 8) & 0xFF);
    Bytes[2] = (NvU008)((Data >> 16) & 0xFF);
    Bytes[3] = (NvU008)((Data >> 24) & 0xFF);
    Bytes[4] = (NvU008)((Data >> 32) & 0xFF);
    Bytes[5] = (NvU008)((Data >> 40) & 0xFF);
    Bytes[6] = (NvU008)((Data >> 48) & 0xFF);
    Bytes[7] = (NvU008)(Data >> 56);
    Send(Bytes, sizeof(Bytes));
}

double Socket::RecvDouble()
{
    NvU064 Data = Recv64();
    return *(double *)&Data;
}

void Socket::SendDouble(double Data)
{
    Send64(*(NvU064 *)&Data);
}

// We could use null-terminated strings, but sending the length is more
// efficient for the receiver.
string Socket::RecvString()
{
    NvU032 Length = Recv32();
    string Str;
    Str.resize(Length);
    Recv(&Str[0], Length);
    return Str;
}

void Socket::SendString(const char *Str)
{
    NvU032 Length = (NvU032)strlen(Str);
    Send32(Length);
    Send(Str, Length);
}

void Socket::InstallErrorHandler(ErrorHandlerFunc Function, void *Args)
{
    ErrorHandler = Function;
    ErrorHandlerArgs = Args;
}

void Socket::CallErrorHandler()
{
    if (ErrorHandler)
        ErrorHandler(ErrorHandlerArgs);
}
