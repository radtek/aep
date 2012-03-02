/**
* @file
* @brief Server�������ͷ�ļ�.
* @author ruoxi
*
* ������Server�������.
*/

#ifndef __SERVER_H__
#define __SERVER_H__

#include "platform.h"
#include "tcp_socket.h"
#include "logger.h"

/**
* @class Server
* @brief Server�������.
*
* Server������������˹��ڷ���˵ĸ��ֲ���,
* ������ʼ��, �ر�, ����, �Ͽ�, ��½, ע��, ����ģ���ļ��ȹ���.
* ����Ϊ����˹�����, ������������˱�ʾ��(��ͼ�ν���).
* �������Ʋ����˵�̬ģʽ(singleton), �ڴ�����汣֤����ֻ����һ��ʵ��.
*/
class Server
{
public:
    /** @brief Server��������. */
    ~Server();

    /** @brief Server��ʼ��. */
    RC Init();
    /** @brief Server�ر�. */
    RC Shut();

    /** @brief ����������. */
    RC Listen();

private:
    /** @brief �����ļ���������. */
    RC RealListen();

public:
    /** @brief ���÷���˶˿�. */
    void SetPort(int port);
    /** @brief ������־. */
    void SetLogger(Logger *logger);
    /** @brief ��¼��־. */
    void Log(LPCWSTR msg);

private:
    /** @brief ƽ̨����, ��������ƽ̨����. */
    Platform &m_Platform;

    /**
    * @class ServiceThread
    * @brief ServiceThread����˷����߳���.
    *
    * ServiceThread����˷����߳��������˷���˶���ÿһ���ͻ��˵ľ���ķ������,
    * ����˶���ÿ�����ӵĿͻ���, ������һ�������ķ�����̶߳�����з���,
    * �Դﵽ�����������ͻ���Ŀ��.
    * ������߳���ľ��幦�ܶ�Ӧ�ͻ��˵�ȫ������.
    * ������½, ע��, ����ģ���ļ��ȹ���.
    */
    class ServiceThread
    {
    public:
        /** @brief ServiceThread���캯��. */
        ServiceThread(TcpSocket *clientSocket);
        /** @brief ServiceThread��������. */
        ~ServiceThread();

        /** @brief ���տͻ��˷���������. */
        RC RecvCommand(CC &cc);

    public:
        /** @brief �����û���½����. */
        RC OnLogin();
        /** @brief �����û�ע������. */
        RC OnRegister();
        /** @brief ������ģ���ļ�����. */
        RC OnSendModelFile();
        /** @brief �����ϴ��ļ�����(��ʾ��). */
        RC OnUploadFile();
        /** @brief �������û����ϴ����ļ��б�����(��ʾ��). */
        RC OnGetFileList();
        /** @brief ���������ļ�����(��ʾ��). */
        RC OnDownloadFile();
        /** @brief �����û��˳�����. */
        RC OnLogout();

    protected:
        void Log(LPCWSTR msg);

    private:
        /** @brief ��¼���̷߳�����û���. */
        wstring m_UserName;
        /** @brief ��¼���û��Ƿ��½. */
        bool m_IsLogined;
        /** @brief ��������ͻ��˵�TcpSocket����. */
        TcpSocket *m_ClientSocket;
        /** @brief �����߳�ID. */
        UINT32 m_Id;
        /** @brief �����̼߳���. */
        static UINT32 s_Counter;
    };

    /**
    * @brief �̵߳ļ�������.
    */
    static DWORD WINAPI ThreadListen(LPVOID lparam);

    /**
    * @brief ����˾�̬������.
    */
    static DWORD WINAPI ThreadService(LPVOID lparam);

    /** @brief ������Ӧ�ͻ������ӵ�TcpSocket����. */
    TcpSocket m_Socket;
    /** @brief ����������˿�. */
    int m_Port;
    /** @brief ��־��¼��. */
    Logger *m_Logger;

private:
    /** @brief �û������ļ���. */
    static LPCWSTR s_UserFileName;

public:
    /** @brief ���Server��ʵ��. */
    static Server &GetInstance();
    /** @brief ����Server��ʵ��. */
    static void DestroyInstance();

private:
    /** @brief Server˽��Ĭ�Ϲ��캯��. */
    Server();
    /** @brief ���ڴ洢Server��Ψһʵ����ָ��. */
    static Server *s_Instance;
    /** @brief ���ڼ�¼Server���Ψһʵ���Ƿ��ѱ�����. */
    static bool s_Initialized;
};

#endif // __SERVER_H__
