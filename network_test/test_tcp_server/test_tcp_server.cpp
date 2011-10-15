/**
* @file
* @brief TestTcpServer类cpp文件.
* @author ruoxi
*
* 实现了TestTcpServer类.
*/

#include "test_tcp_server.h"

/**
* @param port 服务端主机端口.
* @param logFileName 日志文件名.
* @param maxClientNum 可服务的最大客户端数, 默认值为1.
*
* TestTcpServer构造函数. 接受服务端主机端口, 日志文件名及可服务的最大客户端数.
*/
TestTcpServer::TestTcpServer(int port, const char *logFileName, UINT32 maxClientNum)
:
m_Port(port),
m_LogFileName(logFileName),
m_Logger(logFileName),
m_MaxClientNum(maxClientNum),
m_RunningClientNum(0)
{
    m_TcpSocket = new TcpSocket;
}

TestTcpServer::~TestTcpServer()
{
}

/**
* @return 结果代码.
*
* TestTcpServer初始化. 初始化Socket环境, 初始化服务端用TcpSocket.
*/
RC TestTcpServer::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_TcpSocket->Init());

    return rc;
}

/**
* @return 结果代码.
*
* TestTcpServer清理. 清理服务端用TcpSocket, 清理Socket环境.
*/
RC TestTcpServer::Shut()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Shut());

    CHECK_RC(Socket::Shut());

    m_Logger.close();

    return rc;
}

/**
* @return 结果代码.
*
* 进入监听服务状态. 能够监听并服务1或多个客户端.
* 当有客户端连入, 接受连接, 得到客户端Socket.
* 然后创建一个服务线程信息ThreadInfo, 将线程ID, 服务端及客户端Socket填充好.
* 再通过系统调用创建出一个服务线程用于服务该客户端.
* 该线程运行函数Dispatch, 并将ThreadInfo作为参入传入Dispatch函数.
* 并由Dispatch函数完成最终对服务端程序运行函数Service的调用, 服务该客户端.
* 在服务了的客户端打到可服务的最大客户端数后, 函数退出.
*/
RC TestTcpServer::Listen()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Listen(m_Port));

    UINT32 clientNum = 0;

    while (clientNum < m_MaxClientNum)
    {
        TcpSocket *clientSocket = new TcpSocket();

        CHECK_RC(m_TcpSocket->Accept(*clientSocket));

        HANDLE thread;
        ThreadInfo *info = new ThreadInfo;
        info->ThreadId = 0;
        info->Server = this;
        info->ClientSocket = clientSocket;
        m_RunningClientNum++;
        thread = CreateThread(NULL,
            NULL,
            Dispatch,
            (LPVOID)info,
            0,
            &info->ThreadId);
        if(thread == NULL)
        {
            return RC::THREAD_CREATE_ERROR;
        }
        ++clientNum;
    }
    return OK;
}

/**
* @return 结果代码.
*
* 等待全部服务线程退出.
* 在服务端主线程完成Listen监听函数后, 通常会自动退出..
* 而其他服务线程因为是该主线程的子线程, 会一并中止并退出, 这样会有服务未完成的情况发生.
* 该函数实现了让主线程等待所有服务线程完成服务.
* 通过记录并维护当前正在服务的客户端数, 当客户端数为0时, 函数结束.
* 这时主线程可安全退出.
*/
RC TestTcpServer::Hold()
{
    while (m_RunningClientNum > 0);
    return OK;
}

/**
* @return 日志文件名.
*/
const char *TestTcpServer::GetLogFileName()
{
    return m_LogFileName;
}

/**
* @param lparam 实际类型应为ThreadInfo, 服务线程信息.
*
* 服务线程派发函数. 实际为真正的服务端程序运行函数Service的包装函数.
* 因Windows系统的线程函数必须为全局函数或静态函数, 因此类成员函数Service不能直接作为线程函数传入线程创建函数.
* 不过可以通过将实际的this指针作为参数传入该包装函数, 完成对真正的成员函数的调用.
* 该函数参数ThreadInfo中的Server成员即为此this指针.
* 这样仍然可以通过只改写虚函数Service来实现具体的服务端服务功能.
*/
DWORD WINAPI TestTcpServer::Dispatch(LPVOID lparam)
{
    ThreadInfo *info = (ThreadInfo *)lparam;

    info->Server->Service(info->ClientSocket, info->ThreadId);

    info->Server->m_RunningClientNum--;

    delete info->ClientSocket;
    delete info;

    return 0;
}
