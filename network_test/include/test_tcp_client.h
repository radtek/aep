/**
* @file
* @brief TestTcpClient类头文件.
* @author ruoxi
*
* 定义了TestTcpClient类.
*/

#ifndef __TEST_TCP_CLIENT_H__
#define __TEST_TCP_CLIENT_H__

#include "tcp_socket.h"
#include <fstream>

using namespace std;

/**
* @class TestTcpClient
* @brief 测试用TCP客户端类.
*
* TestTcpClient类是测试用TCP客户端基类.
* 使用TcpSocket, 连接至测试用TCP服务端, 运行一小段客户端程序并记录日志.
*/
class TestTcpClient
{
public:
    /** @brief TestTcpClient构造函数. */
    TestTcpClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    /** @brief TestTcpClient析构函数. */
    virtual ~TestTcpClient();

    /** @brief TestTcpClient初始化. */
    RC Init();
    /** @brief TestTcpClient清理. */
    RC Shut();

    /** @brief 连接至测试用TCP服务端. */
    RC Connect();

    /**
    * @brief 客户端程序运行函数.
    * @return 结果代码.
    *
    * 抽象的客户端程序运行函数.
    * 任何TestTcpClient实现类必须给出该函数的一个具体实现,
    * 以完成真正的客户端测试运行.
    */
    virtual RC Run() = 0;

    /** @brief 得到日志文件名. */
    const char *GetLogFileName();

protected:
    /** @brief 客户端用TcpSocket. */
    TcpSocket *m_TcpSocket;
    /** @brief 测试用TCP服务端主机名. */
    const char *m_HostName;
    /** @brief 测试用TCP服务端主机端口. */
    int m_Port;
    /** @brief 日志文件名. */
    const char *m_LogFileName;
    /** @brief 日志文件流. */
    ofstream m_Logger;
    /** @brief 客户端ID. */
    UINT32 m_Id;
};

#endif // __TEST_TCP_CLIENT_H__
