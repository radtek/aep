#include "socket.h"
#include "massert.h"
#include <winsock2.h>

/**
* @return 结果代码.
*
* Socket环境初始化.
* 调用winsock的初始化函数. 并要求winsock版本2.
*/
RC Socket::Init()
{
    WSADATA wsaData;
    if (SOCKET_ERROR == WSAStartup(MAKEWORD(2,2), &wsaData))
    {
        return RC::WINSOCK_INIT_ERROR;
    }
    return OK;
}

/**
* @return 结果代码.
*
* Socket环境清理.
* 调用winsock的清理函数.
*/
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

/**
* @param data 用来存储接收到的8位无符号整形.
* @return 结果代码.
*
* 接收一个8位的无符号整形.
* 因其不依赖于Recv函数的具体实现,
* 故而可以直接操作抽象的Recv来实现,
* 即接收1个字节的数据.
*/
RC Socket::Recv08(UINT08 &data)
{
    return Recv(&data, 1);
}

/**
* @param data 要发送的8位无符号整形.
* @return 结果代码.
*
* 发送一个8位的无符号整形.
* 因其不依赖于Send函数的具体实现,
* 故而可以直接操作抽象的Send来实现,
* 即发送1个字节的数据.
*/
RC Socket::Send08(UINT08 data)
{
    return Send(&data, 1);
}

/**
* @param data 用来存储接收到的16位无符号整形.
* @return 结果代码.
*
* 接收一个16位的无符号整形.
* 因其不依赖于Recv函数的具体实现,
* 故而可以直接操作抽象的Recv来实现,
* 即接收2个字节的数据.
*/
RC Socket::Recv16(UINT16 &data)
{
    RC rc;
    UINT08 bytes[2] = { 0, };
    CHECK_RC(Recv(bytes, sizeof(bytes)));
    data  = bytes[0];
    data |= bytes[1] << 8;
    return rc;
}

/**
* @param data 要发送的16位无符号整形.
* @return 结果代码.
*
* 发送一个16位的无符号整形.
* 因其不依赖于Send函数的具体实现,
* 故而可以直接操作抽象的Send来实现,
* 即发送2个字节的数据.
*/
RC Socket::Send16(UINT16 data)
{
    UINT08 bytes[2];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)(data >> 8);
    return Send(bytes, sizeof(bytes));
}

/**
* @param data 用来存储接收到的32位无符号整形.
* @return 结果代码.
*
* 接收一个32位的无符号整形.
* 因其不依赖于Recv函数的具体实现,
* 故而可以直接操作抽象的Recv来实现,
* 即接收4个字节的数据.
*/
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

/**
* @param data 要发送的32位无符号整形.
* @return 结果代码.
*
* 发送一个32位的无符号整形.
* 因其不依赖于Send函数的具体实现,
* 故而可以直接操作抽象的Send来实现,
* 即发送4个字节的数据.
*/
RC Socket::Send32(UINT32 data)
{
    UINT08 bytes[4];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)((data >> 8) & 0xFF);
    bytes[2] = (UINT08)((data >> 16) & 0xFF);
    bytes[3] = (UINT08)(data >> 24);
    return Send(bytes, sizeof(bytes));
}

/**
* @param data 用来存储接收到的64位无符号整形.
* @return 结果代码.
*
* 接收一个64位的无符号整形.
* 因其不依赖于Recv函数的具体实现,
* 故而可以直接操作抽象的Recv来实现,
* 即接收8个字节的数据.
*/
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

/**
* @param data 要发送的64位无符号整形.
* @return 结果代码.
*
* 发送一个64位的无符号整形.
* 因其不依赖于Send函数的具体实现,
* 故而可以直接操作抽象的Send来实现,
* 即发送8个字节的数据.
*/
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

/**
* @param data 用来存储接收到的64位双精度浮点数.
* @return 结果代码.
*
* 接收一个64位的双精度浮点数.
* 直接使用Recv64来实现.
*/
RC Socket::RecvDouble(double &data)
{
    RC rc;
    UINT64 temp;
    CHECK_RC(Recv64(temp));
    data = static_cast<double>(temp);
    return rc;
}

/**
* @param data 要发送的64位双精度浮点数.
* @return 结果代码.
*
* 发送一个64位的双精度浮点数.
* 直接使用Recv64来实现.
*/
RC Socket::SendDouble(double data)
{
    UINT64 temp = static_cast<UINT64>(data);
    return Send64(temp);
}

/**
* @param str 用来存储接收到的不定长字符串.
* @return 结果代码.
*
* 接收一个不定长的字符串.
* 先接收一个32位无符号整形表示字符串长度,
* 再根据长度接收实际的字符串内容.
*/
RC Socket::RecvString(string &str)
{
    RC rc;
    UINT32 length;
    CHECK_RC(Recv32(length));
    str.resize(length);
    return Recv(&str[0], length);
}

/**
* @param str 要发送的不定长字符串.
* @return 结果代码.
*
* 发送一个不定长的字符串.
* 先发送一个32位无符号整形表示字符串长度,
* 再根据长度发送实际的字符串内容.
*/
RC Socket::SendString(const char *str)
{
    RC rc;
    MASSERT(str != 0);
    UINT32 length = (UINT32)strlen(str);
    CHECK_RC(Send32(length));
    CHECK_RC(Send(str, length));
    return rc;
}

/**
* @return winsock错误代码.
*
* 返回Socket调用中的最后一个错误.
* 调用winsock的对应函数.
*/
int Socket::GetLastError()
{
    return WSAGetLastError();
}
