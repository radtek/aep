/**
* @file
* @brief Server服务端类头文件.
* @author ruoxi
*
* 定义了Server服务端类.
*/

#ifndef __SERVER_H__
#define __SERVER_H__

#include "platform.h"
#include "tcp_socket.h"
#include "logger.h"

/**
* @class Server
* @brief Server服务端类.
*
* Server服务端类抽象出了关于服务端的各种操作,
* 包括初始化, 关闭, 连接, 断开, 登陆, 注册, 发送模型文件等功能.
* 该类为服务端功能类, 并不包含服务端表示层(即图形界面).
* 该类的设计采用了单态模式(singleton), 在代码层面保证了它只能有一个实例.
*/
class Server
{
public:
    /** @brief Server析构函数. */
    ~Server();

    /** @brief Server初始化. */
    RC Init();
    /** @brief Server关闭. */
    RC Shut();

    /** @brief 监听服务函数. */
    RC Listen();

private:
    /** @brief 真正的监听服务函数. */
    RC RealListen();

public:
    /** @brief 设置服务端端口. */
    void SetPort(int port);
    /** @brief 设置日志. */
    void SetLogger(Logger *logger);
    /** @brief 记录日志. */
    void Log(LPCWSTR msg);

private:
    /** @brief 平台对象, 用来调用平台功能. */
    Platform &m_Platform;

    /**
    * @class ServiceThread
    * @brief ServiceThread服务端服务线程类.
    *
    * ServiceThread服务端服务线程类抽象出了服务端对于每一个客户端的具体的服务操作,
    * 服务端对于每个连接的客户端, 均创建一个独立的服务端线程对象进行服务,
    * 以达到并发服务多个客户的目的.
    * 服务端线程类的具体功能对应客户端的全部功能.
    * 包括登陆, 注册, 发送模型文件等功能.
    */
    class ServiceThread
    {
    public:
        /** @brief ServiceThread构造函数. */
        ServiceThread(TcpSocket *clientSocket);
        /** @brief ServiceThread析构函数. */
        ~ServiceThread();

        /** @brief 接收客户端发来的命令. */
        RC RecvCommand(CC &cc);

    public:
        /** @brief 服务用户登陆请求. */
        RC OnLogin();
        /** @brief 服务用户注册请求. */
        RC OnRegister();
        /** @brief 服务发送模型文件请求. */
        RC OnSendModelFile();
        /** @brief 服务上传文件请求(演示用). */
        RC OnUploadFile();
        /** @brief 服务获得用户已上传的文件列表请求(演示用). */
        RC OnGetFileList();
        /** @brief 服务下载文件请求(演示用). */
        RC OnDownloadFile();
        /** @brief 服务用户退出请求. */
        RC OnLogout();

    protected:
        void Log(LPCWSTR msg);

    private:
        /** @brief 记录该线程服务的用户名. */
        wstring m_UserName;
        /** @brief 记录该用户是否登陆. */
        bool m_IsLogined;
        /** @brief 用来服务客户端的TcpSocket对象. */
        TcpSocket *m_ClientSocket;
        /** @brief 服务线程ID. */
        UINT32 m_Id;
        /** @brief 服务线程计数. */
        static UINT32 s_Counter;
    };

    /**
    * @brief 线程的监听函数.
    */
    static DWORD WINAPI ThreadListen(LPVOID lparam);

    /**
    * @brief 服务端静态服务函数.
    */
    static DWORD WINAPI ThreadService(LPVOID lparam);

    /** @brief 用来响应客户端连接的TcpSocket对象. */
    TcpSocket m_Socket;
    /** @brief 服务端主机端口. */
    int m_Port;
    /** @brief 日志记录器. */
    Logger *m_Logger;

private:
    /** @brief 用户数据文件名. */
    static LPCWSTR s_UserFileName;

public:
    /** @brief 获得Server类实例. */
    static Server &GetInstance();
    /** @brief 销毁Server类实例. */
    static void DestroyInstance();

private:
    /** @brief Server私有默认构造函数. */
    Server();
    /** @brief 用于存储Server类唯一实例的指针. */
    static Server *s_Instance;
    /** @brief 用于记录Server类的唯一实例是否已被创建. */
    static bool s_Initialized;
};

#endif // __SERVER_H__
