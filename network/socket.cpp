#include "socket.h"
#include "massert.h"
#include <winsock2.h>

/**
* @return �������.
*
* Socket������ʼ��.
* ����winsock�ĳ�ʼ������. ��Ҫ��winsock�汾2.
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
* @return �������.
*
* Socket��������.
* ����winsock��������.
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
* @param data �����洢���յ���8λ�޷�������.
* @return �������.
*
* ����һ��8λ���޷�������.
* ���䲻������Recv�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Recv��ʵ��,
* ������1���ֽڵ�����.
*/
RC Socket::Recv08(UINT08 &data)
{
    return Recv(&data, 1);
}

/**
* @param data Ҫ���͵�8λ�޷�������.
* @return �������.
*
* ����һ��8λ���޷�������.
* ���䲻������Send�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Send��ʵ��,
* ������1���ֽڵ�����.
*/
RC Socket::Send08(UINT08 data)
{
    return Send(&data, 1);
}

/**
* @param data �����洢���յ���16λ�޷�������.
* @return �������.
*
* ����һ��16λ���޷�������.
* ���䲻������Recv�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Recv��ʵ��,
* ������2���ֽڵ�����.
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
* @param data Ҫ���͵�16λ�޷�������.
* @return �������.
*
* ����һ��16λ���޷�������.
* ���䲻������Send�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Send��ʵ��,
* ������2���ֽڵ�����.
*/
RC Socket::Send16(UINT16 data)
{
    UINT08 bytes[2];
    bytes[0] = (UINT08)(data & 0xFF);
    bytes[1] = (UINT08)(data >> 8);
    return Send(bytes, sizeof(bytes));
}

/**
* @param data �����洢���յ���32λ�޷�������.
* @return �������.
*
* ����һ��32λ���޷�������.
* ���䲻������Recv�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Recv��ʵ��,
* ������4���ֽڵ�����.
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
* @param data Ҫ���͵�32λ�޷�������.
* @return �������.
*
* ����һ��32λ���޷�������.
* ���䲻������Send�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Send��ʵ��,
* ������4���ֽڵ�����.
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
* @param data �����洢���յ���64λ�޷�������.
* @return �������.
*
* ����һ��64λ���޷�������.
* ���䲻������Recv�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Recv��ʵ��,
* ������8���ֽڵ�����.
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
* @param data Ҫ���͵�64λ�޷�������.
* @return �������.
*
* ����һ��64λ���޷�������.
* ���䲻������Send�����ľ���ʵ��,
* �ʶ�����ֱ�Ӳ��������Send��ʵ��,
* ������8���ֽڵ�����.
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
* @param data �����洢���յ���64λ˫���ȸ�����.
* @return �������.
*
* ����һ��64λ��˫���ȸ�����.
* ֱ��ʹ��Recv64��ʵ��.
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
* @param data Ҫ���͵�64λ˫���ȸ�����.
* @return �������.
*
* ����һ��64λ��˫���ȸ�����.
* ֱ��ʹ��Recv64��ʵ��.
*/
RC Socket::SendDouble(double data)
{
    UINT64 temp = static_cast<UINT64>(data);
    return Send64(temp);
}

/**
* @param str �����洢���յ��Ĳ������ַ���.
* @return �������.
*
* ����һ�����������ַ���.
* �Ƚ���һ��32λ�޷������α�ʾ�ַ�������,
* �ٸ��ݳ��Ƚ���ʵ�ʵ��ַ�������.
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
* @param str Ҫ���͵Ĳ������ַ���.
* @return �������.
*
* ����һ�����������ַ���.
* �ȷ���һ��32λ�޷������α�ʾ�ַ�������,
* �ٸ��ݳ��ȷ���ʵ�ʵ��ַ�������.
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
* @return winsock�������.
*
* ����Socket�����е����һ������.
* ����winsock�Ķ�Ӧ����.
*/
int Socket::GetLastError()
{
    return WSAGetLastError();
}
