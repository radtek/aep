/**
* @file
* @brief Client客户端类cpp文件.
* @author ruoxi
*
* 实现了Client客户端类.
*/

#include "client.h"

#include "utility.h"

/**
* @return Client类的唯一实例.
*
* 用户只能通过该函数获得Client类的唯一实例.
* 若Client类还未被初始化, 则创建唯一的Client类对象,
* 否则直接返回该对象.
*/
Client &Client::GetInstance()
{
    if (!s_Initialized)
    {
        s_Instance = new Client;
        s_Initialized = true;
    }
    return *s_Instance;
}

void Client::DestroyInstance()
{
    if (s_Initialized)
    {
        delete s_Instance;
        s_Instance = NULL;
        s_Initialized = false;
    }
}

/**
* 将Client类的唯一构造函数声明为私有,
* 可以保证编译器不会帮助生成其他构造函数,
* 并且该类不可以显式的实例化.
* 该构造函数并不完成具体的初始化,
* 初始化工作通过Init函数来完成.
*/
Client::Client()
:
m_Platform(Platform::GetInstance()),
m_IsConnected(false),
m_IsLogined(false)
{
}

Client *Client::s_Instance = NULL;

bool Client::s_Initialized = false;

/**
* Client类的析构函数.
* 该析构函数并不完成具体的销毁,
* 销毁工作通过Shut函数来完成.
*/
Client::~Client()
{
}

/**
* @return 结果代码.
*
* 完成Client对象的初始化.
* 它对Socket环境进行初始化,
* 对平台进行初始化,
* 对TcpSocket对象进行初始化.
* 并且设置好默认的服务器主机地址和端口.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
*/
RC Client::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_Platform.Init());
    CHECK_RC(m_Socket.Init());

    m_HostName = "localhost";
    m_Port = 10086;

    return rc;
}

/**
* @return 结果代码.
*
* 完成Client对象的销毁.
* 它先销毁TcpSocket对象,
* 然后销毁平台,
* 最后清理Socket环境.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
*/
RC Client::Shut()
{
    RC rc;

    CHECK_RC(m_Socket.Shut());
    CHECK_RC(m_Platform.Shut());

    CHECK_RC(Socket::Shut());

    return rc;
}

/**
* @param hostName 服务器主机名或地址.
*/
RC Client::SetHostName(const char *hostName)
{
    RC rc;

    m_HostName = hostName;

    return rc;
}

/**
* @param port 服务器主机端口.
*/
RC Client::SetPort(int port)
{
    RC rc;

    m_Port = port;

    return rc;
}

/**
* @return 结果代码.
*
* 连接至服务器.
* 使用TcpSocket对象连接至服务器.
* 若连接失败则返回错误代码.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
*/
RC Client::Connect()
{
    RC rc;

    CHECK_RC(m_Socket.Connect(m_HostName.c_str(), m_Port));

    m_IsConnected = true;

    return rc;
}

/**
* @return 结果代码.
*
* 断开与服务器的连接.
* 使用的方法是先关闭TcpSocket对象,
* 然后再重新调用其初始化,
* 保持TcpSocket对象可供下次连接使用.
* 连接成功则设置m_IsConnected为true.
* 返回OK.
*/
RC Client::Disconnect()
{
    RC rc;

    CHECK_RC(m_Socket.Shut());
    CHECK_RC(m_Socket.Init());

    m_IsConnected = false;

    return rc;
}

bool Client::IsConnected()
{
    return m_IsConnected;
}

/**
* @param name 用户名.
* @param password 密码.
* @return 结果代码.
*
* 将用户名与密码发送至服务器进行登录.
* 用户名密码均不能含有空格,
* 但该函数并不做判断,
* 这一点将由调用该函数的上层函数来保证.
* 接收服务器返回的结果.
* 若登陆失败, 则返回错误信息.
* 否则将设置m_IsLogined为true,
* 表示已经登陆.
*/
RC Client::Login(const wstring &name, const wstring &password)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::LOGIN_COMMAND));

    CHECK_RC(m_Socket.SendWString(name.c_str()));
    CHECK_RC(m_Socket.SendWString(password.c_str()));

    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));
    if (OK == _rc)
    {
        m_IsLogined = true;
    }

    return _rc;
}

bool Client::IsLogined()
{
    return m_IsLogined;
}

RC Client::Logout()
{
    RC rc;

    if (!m_IsLogined)
    {
        return rc;
    }

    CHECK_RC(m_Socket.SendCommand(CC::LOGOUT_COMMAND));
    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));
    if (OK == _rc)
    {
        m_IsLogined = false;
    }

    return _rc;
}

/**
* @param name 用户名.
* @param password 密码.
* @return 结果代码.
*
* 将用户名与密码发送至服务器进行注册.
* 用户名密码均不能含有空格,
* 但该函数并不做判断,
* 这一点将由调用该函数的上层函数来保证.
* 接收服务器返回的结果.
* 若注册失败, 则返回错误信息.
* 否则返回OK.
*/
RC Client::Register(const wstring &name, const wstring &password)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::REGISTER_COMMAND));

    CHECK_RC(m_Socket.SendWString(name.c_str()));
    CHECK_RC(m_Socket.SendWString(password.c_str()));

    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));

    return _rc;
}

/**
* @param fileName 要发送的文件路径.
* @return 结果代码.
*
* 将模型文件发送至服务器.
* 接收服务器返回的结果.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
*/
RC Client::SendModelFile(LPCWSTR fileName)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::SEND_MODEL_FILE_COMMAND));
    RC _rc = m_Socket.SendFile(fileName);

    if (OK == _rc)
    {
        CHECK_RC(m_Socket.RecvRC(_rc));
        if (OK == _rc)
        {
            wstring datFileName = fileName;
            datFileName += TEXT(".dat");
            CHECK_RC(m_Socket.RecvFile(datFileName.c_str()));
        }
    }

    return _rc;
}

RC Client::UploadFile(const wstring &fileName)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::UPLOAD_FILE_COMMAND));

    wstring fileNameWithoutPath = Utility::StripFilePath(fileName.c_str());
    CHECK_RC(m_Socket.SendWString(fileNameWithoutPath.c_str()));
    CHECK_RC(m_Socket.SendFile(fileName.c_str()));

    return rc;
}

RC Client::GetFileList(vector<wstring> &fileList)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::GET_FILE_LIST_COMMAND));

    wstring fileName;
    CHECK_RC(m_Socket.RecvWString(fileName));
    while (fileName != TEXT(" "))
    {
        fileList.push_back(fileName);
        CHECK_RC(m_Socket.RecvWString(fileName));
    }

    return rc;
}

RC Client::DownLoadFile(const wstring &fileName, const wstring &pathName)
{
    RC rc;

    CHECK_RC(m_Socket.SendCommand(CC::DOWNLOAD_FILE_COMMAND));

    CHECK_RC(m_Socket.SendWString(fileName.c_str()));
    
    RC _rc;
    CHECK_RC(m_Socket.RecvRC(_rc));
    CHECK_RC(_rc);

    CHECK_RC(m_Socket.RecvFile(pathName.c_str()));

    return rc;
}
