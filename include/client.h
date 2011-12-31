#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "platform.h"
#include "tcp_socket.h"

class Client
{
public:
    ~Client();

    RC Init();
    RC Shut();

    RC SetHostName(const char *hostName);
    RC SetPort(int port);

    RC Connect();
    RC Disconnect();
    bool IsConnected();

    RC Login(const wstring &name, const wstring &password);
    bool IsLogined();

    RC Register(const wstring &name, const wstring &password);

    RC SendModelFile(LPCWSTR fileName);

    RC UploadFile(const wstring &fileName);
    RC GetFileList(vector<wstring> &fileList);
    RC DownLoadFile(const wstring &fileName, const wstring &pathName);

private:
    Platform &m_Platform;
    TcpSocket m_Socket;
    string m_HostName;
    int m_Port;
    bool m_IsConnected;
    bool m_IsLogined;

public:
    static Client &GetInstance();
    static void DestroyInstance();

private:
    Client();
    static Client *s_Instance;
    static bool s_Initialized;
};

#endif // __CLIENT_H__
