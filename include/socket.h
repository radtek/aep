/**
* @file
* @brief Socket�ӿ���ͷ�ļ�.
* @author ruoxi
*
* ������Socket�ӿ���.
*/

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "rc.h"
#include <string>

using namespace std;

/**
* @class Socket
* @brief Socket�ӿ���.
*
* Socket�ӿ��������˹���Socket�ĸ��ֲ���,
* ������ʼ��, ����, �ֽ������շ����ض��������͵��շ��ȵ�.
* �����ֽ������շ�����ʵ�ָýӿڵ��ฺ��ʵ��,
* �ض��������͵��շ�ʹ�ó�����ֽ����շ��ڱ�����ʵ��.
* �շ�˫����ʹ�øýӿڼ��ɱ��⴫������еĴ�С�˲�һ������.
*/
class Socket
{
public:
    /** @brief Socket���캯��. */
    Socket();
    /** @brief Socket��������. */
    virtual ~Socket();

    /** @brief Socket������ʼ��. */
    static RC Init();
    /** @brief Socket��������. */
    static RC Shut();

    /**
    * @brief ������ֽ������պ���.
    * @param buf Ҫ���յ����ݻ�����ָ��.
    * @param size Ҫ���յ������ֽ���.
    * @return �������.
    *
    * ������ֽ������պ���, ���麯��.
    * �κ�Socketʵ�����������ú�����һ������ʵ��,
    * ������������ֽ������չ���.
    */
    virtual RC Recv(void *buf, size_t size) = 0;
    /**
    * @brief ������ֽ������ͺ���.
    * @param buf Ҫ���͵����ݻ�����ָ��.
    * @param size Ҫ���͵������ֽ���.
    * @return �������.
    *
    * ������ֽ������ͺ���, ���麯��.
    * �κ�Socketʵ�����������ú�����һ������ʵ��,
    * ������������ֽ������͹���.
    */
    virtual RC Send(const void *buf, size_t size) = 0;

    /** @brief ����һ��8λ���޷�������. */
    RC Recv08(UINT08 &data);
    /** @brief ����һ��8λ���޷�������. */
    RC Send08(UINT08 data);

    /** @brief ����һ��16λ���޷�������. */
    RC Recv16(UINT16 &data);
    /** @brief ����һ��16λ���޷�������. */
    RC Send16(UINT16 data);

    /** @brief ����һ��32λ���޷�������. */
    RC Recv32(UINT32 &data);
    /** @brief ����һ��32λ���޷�������. */
    RC Send32(UINT32 data);

    /** @brief ����һ��64λ���޷�������. */
    RC Recv64(UINT64 &data);
    /** @brief ����һ��64λ���޷�������. */
    RC Send64(UINT64 data);

    /** @brief ����һ��64λ��˫���ȸ�����. */
    RC RecvDouble(double &data);
    /** @brief ����һ��64λ��˫���ȸ�����. */
    RC SendDouble(double data);

    /** @brief ����һ�����������ַ���. */
    RC RecvString(string &str);
    /** @brief ����һ�����������ַ���. */
    RC SendString(const char *str);

    /** @brief ����Socket�����е����һ������. */
    static int GetLastError();
};

#endif // __SOCKET_H__
