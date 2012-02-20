/**
* @file
* @brief Client客户端类头文件.
* @author ruoxi
*
* 定义了Client客户端类.
*/

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "platform.h"
#include "tcp_socket.h"

/**
* @class Client
* @brief Client客户端类.
*
* Client客户端类抽象出了关于客户端的各种操作,
* 包括初始化, 关闭, 连接, 断开, 登陆, 注册, 发送模型文件等功能.
* 该类为客户端功能类, 并不包含客户端表示层(即图形界面).
* 该类的设计采用了单态模式(singleton), 在代码层面保证了它只能有一个实例.
*/
class Client
{
public:
    /** @brief Client析构函数. */
    ~Client();

    /** @brief Client初始化. */
    RC Init();
    /** @brief Client关闭. */
    RC Shut();

    /** @brief 设置服务端主机名或地址. */
    RC SetHostName(const char *hostName);
    /** @brief 设置服务端主机端口. */
    RC SetPort(int port);

    /** @brief 连接服务器. */
    RC Connect();
    /** @brief 断开与服务器的连接. */
    RC Disconnect();
    /** @brief 判断是否已连接至服务器. */
    bool IsConnected();

    /** @brief 用户登陆. */
    RC Login(const wstring &name, const wstring &password);
    /** @brief 判断是否已登陆至服务器. */
    bool IsLogined();
    /** @brief 用户退出. */
    RC Logout();

    /** @brief 用户注册. */
    RC Register(const wstring &name, const wstring &password);

    /** @brief 发送模型文件. */
    RC SendModelFile(LPCWSTR fileName);

    /** @brief 上传文件(演示用). */
    RC UploadFile(const wstring &fileName);
    /** @brief 获得用户已上传的文件列表(演示用). */
    RC GetFileList(vector<wstring> &fileList);
    /** @brief 下载文件(演示用). */
    RC DownLoadFile(const wstring &fileName, const wstring &pathName);

private:
    /** @brief 平台对象, 用来调用平台功能. */
    Platform &m_Platform;
    /** @brief TcpSocket对象, 用来发送数据. */
    TcpSocket m_Socket;
    /** @brief 服务器主机名. */
    string m_HostName;
    /** @brief 服务器主机端口. */
    int m_Port;
    /** @brief 是否已连接. */
    bool m_IsConnected;
    /** @brief 是否已登录. */
    bool m_IsLogined;

public:
    /** @brief 获得Client类实例. */
    static Client &GetInstance();
    /** @brief 销毁Client类实例. */
    static void DestroyInstance();

private:
    /** @brief Client私有默认构造函数. */
    Client();
    /** @brief 用于存储Client类唯一实例的指针. */
    static Client *s_Instance;
    /** @brief 用于记录Client类的唯一实例是否已被创建. */
    static bool s_Initialized;
};

#endif // __CLIENT_H__
