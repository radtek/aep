/**
* @file
* @brief TestTcpServer类头文件.
* @author ruoxi
*
* 定义了TestTcpServer类.
*/

#ifndef __TEST_TCP_SERVER_H__
#define __TEST_TCP_SERVER_H__

#include "tcp_socket.h"
#include <fstream>

using namespace std;

/**
* @class TestTcpServer
* @brief 测试用TCP服务端类.
*
* TestTcpServer类是测试用TCP服务端基类.
* 使用TcpSocket, 接受测试用TCP客户端的连接, 运行一小段服务端程序并记录日志.
*/
class TestTcpServer
{
public:
    /** @brief TestTcpServer构造函数. */
    TestTcpServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    /** @brief TestTcpServer析构函数. */
    virtual ~TestTcpServer();

    /** @brief TestTcpServer初始化. */
    RC Init();
    /** @brief TestTcpServer清理. */
    RC Shut();

    /** @brief 进入监听服务状态. */
    RC Listen();
    /** @brief 等待全部服务线程退出. */
    RC Hold();

    /** @brief 得到日志文件名. */
    const char *GetLogFileName();

protected:
    /**
    * @class ThreadInfo
    * @brief 服务线程信息.
    *
    * ThreadInfo是传入服务端服务线程的线程信息.
    * 告之服务线程其线程ID, 其所依赖的服务端实例及其所服务的客户端Socket.
    */
    struct ThreadInfo
    {
        /** @brief 线程ID. */
        DWORD ThreadId;
        /** @brief 所依赖的服务端实例. */
        TestTcpServer *Server;
        /** @brief 所服务的客户端Socket. */
        TcpSocket *ClientSocket;
    };
    /** @brief 服务线程派发函数. */
    static DWORD WINAPI Dispatch(LPVOID lparam);
    /**
    * @brief 服务端程序运行函数.
    * @param clientSocket 所服务的客户端Socket.
    * @param threadId 其所在的线程ID.
    * @return 结果代码.
    *
    * 抽象的服务端程序运行函数.
    * 任何TestTcpServer实现类必须给出该函数的一个具体实现,
    * 以完成真正的服务端测试运行.
    */
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0) = 0;

    /** @brief 服务端用TcpSocket. */
    TcpSocket *m_TcpSocket;
    /** @brief 服务端主机端口. */
    int m_Port;
    /** @brief 可服务的最大客户端数. */
    UINT32 m_MaxClientNum;
    /** @brief 当前服务中的客户端数. */
    volatile UINT32 m_RunningClientNum;
    /** @brief 日志文件名. */
    const char *m_LogFileName;
    /** @brief 日志文件流. */
    ofstream m_Logger;
};

#endif // __TEST_TCP_SERVER_H__
