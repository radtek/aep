/**
* @file
* @brief Socket接口类头文件.
* @author ruoxi
*
* 定义了Socket接口类.
*/

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "rc.h"
#include <string>

using namespace std;

/**
* @class Socket
* @brief Socket接口类.
*
* Socket接口类抽象出了关于Socket的各种操作,
* 包括初始化, 清理, 字节流的收发及特定数据类型的收发等等.
* 其中字节流的收发将由实现该接口的类负责实现,
* 特定数据类型的收发使用抽象的字节流收发在本类中实现.
* 收发双方均使用该接口即可避免传输过程中的大小端不一致问题.
*/
class Socket
{
public:
    /** @brief Socket构造函数. */
    Socket();
    /** @brief Socket析构函数. */
    virtual ~Socket();

    /** @brief Socket环境初始化. */
    static RC Init();
    /** @brief Socket环境清理. */
    static RC Shut();

    /**
    * @brief 抽象的字节流接收函数.
    * @param buf 要接收的数据缓冲区指针.
    * @param size 要接收的数据字节数.
    * @return 结果代码.
    *
    * 抽象的字节流接收函数, 纯虚函数.
    * 任何Socket实现类必须给出该函数的一个具体实现,
    * 以完成真正的字节流接收功能.
    */
    virtual RC Recv(void *buf, size_t size) = 0;
    /**
    * @brief 抽象的字节流发送函数.
    * @param buf 要发送的数据缓冲区指针.
    * @param size 要发送的数据字节数.
    * @return 结果代码.
    *
    * 抽象的字节流发送函数, 纯虚函数.
    * 任何Socket实现类必须给出该函数的一个具体实现,
    * 以完成真正的字节流发送功能.
    */
    virtual RC Send(const void *buf, size_t size) = 0;

    /** @brief 接收一个8位的无符号整形. */
    RC Recv08(UINT08 &data);
    /** @brief 发送一个8位的无符号整形. */
    RC Send08(UINT08 data);

    /** @brief 接收一个16位的无符号整形. */
    RC Recv16(UINT16 &data);
    /** @brief 发送一个16位的无符号整形. */
    RC Send16(UINT16 data);

    /** @brief 接收一个32位的无符号整形. */
    RC Recv32(UINT32 &data);
    /** @brief 发送一个32位的无符号整形. */
    RC Send32(UINT32 data);

    /** @brief 接收一个64位的无符号整形. */
    RC Recv64(UINT64 &data);
    /** @brief 发送一个64位的无符号整形. */
    RC Send64(UINT64 data);

    /** @brief 接收一个64位的双精度浮点数. */
    RC RecvDouble(double &data);
    /** @brief 发送一个64位的双精度浮点数. */
    RC SendDouble(double data);

    /** @brief 接收一个不定长的字符串. */
    RC RecvString(string &str);
    /** @brief 发送一个不定长的字符串. */
    RC SendString(const char *str);

    /** @brief 返回Socket调用中的最后一个错误. */
    static int GetLastError();
};

#endif // __SOCKET_H__
