#include "tcp_socket.h"

#include <vector>

using namespace std;

class FileService
{
public:
    FileService();
    virtual ~FileService();

    RC Init(LPCWSTR rootPath, const char *remoteHost, int port);

    RC Shut();

    RC Listen();

private:
    RC RealListen();

public:
    RC DownloadFile(LPCWSTR filePath);

    class ServiceThread
    {
    public:
        ServiceThread(TcpSocket *clientSocket);
        ~ServiceThread();

        RC RealService();

    private:
        TcpSocket *m_ClientSocket;
    };

private:
    wstring m_RootPath;
    string m_RemoteHost;
    int m_Port;
    bool m_IsConnected;

    TcpSocket m_ServerSocket, m_ClientSocket;

    static DWORD WINAPI ThreadListen(LPVOID lparam);

    static DWORD WINAPI ThreadService(LPVOID lparam);

    HANDLE m_ListenThreadHandle;
    vector<HANDLE> m_ServiceThreadHandles;
};
