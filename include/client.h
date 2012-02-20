/**
* @file
* @brief Client�ͻ�����ͷ�ļ�.
* @author ruoxi
*
* ������Client�ͻ�����.
*/

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "platform.h"
#include "tcp_socket.h"

/**
* @class Client
* @brief Client�ͻ�����.
*
* Client�ͻ����������˹��ڿͻ��˵ĸ��ֲ���,
* ������ʼ��, �ر�, ����, �Ͽ�, ��½, ע��, ����ģ���ļ��ȹ���.
* ����Ϊ�ͻ��˹�����, ���������ͻ��˱�ʾ��(��ͼ�ν���).
* �������Ʋ����˵�̬ģʽ(singleton), �ڴ�����汣֤����ֻ����һ��ʵ��.
*/
class Client
{
public:
    /** @brief Client��������. */
    ~Client();

    /** @brief Client��ʼ��. */
    RC Init();
    /** @brief Client�ر�. */
    RC Shut();

    /** @brief ���÷�������������ַ. */
    RC SetHostName(const char *hostName);
    /** @brief ���÷���������˿�. */
    RC SetPort(int port);

    /** @brief ���ӷ�����. */
    RC Connect();
    /** @brief �Ͽ��������������. */
    RC Disconnect();
    /** @brief �ж��Ƿ���������������. */
    bool IsConnected();

    /** @brief �û���½. */
    RC Login(const wstring &name, const wstring &password);
    /** @brief �ж��Ƿ��ѵ�½��������. */
    bool IsLogined();
    /** @brief �û��˳�. */
    RC Logout();

    /** @brief �û�ע��. */
    RC Register(const wstring &name, const wstring &password);

    /** @brief ����ģ���ļ�. */
    RC SendModelFile(LPCWSTR fileName);

    /** @brief �ϴ��ļ�(��ʾ��). */
    RC UploadFile(const wstring &fileName);
    /** @brief ����û����ϴ����ļ��б�(��ʾ��). */
    RC GetFileList(vector<wstring> &fileList);
    /** @brief �����ļ�(��ʾ��). */
    RC DownLoadFile(const wstring &fileName, const wstring &pathName);

private:
    /** @brief ƽ̨����, ��������ƽ̨����. */
    Platform &m_Platform;
    /** @brief TcpSocket����, ������������. */
    TcpSocket m_Socket;
    /** @brief ������������. */
    string m_HostName;
    /** @brief �����������˿�. */
    int m_Port;
    /** @brief �Ƿ�������. */
    bool m_IsConnected;
    /** @brief �Ƿ��ѵ�¼. */
    bool m_IsLogined;

public:
    /** @brief ���Client��ʵ��. */
    static Client &GetInstance();
    /** @brief ����Client��ʵ��. */
    static void DestroyInstance();

private:
    /** @brief Client˽��Ĭ�Ϲ��캯��. */
    Client();
    /** @brief ���ڴ洢Client��Ψһʵ����ָ��. */
    static Client *s_Instance;
    /** @brief ���ڼ�¼Client���Ψһʵ���Ƿ��ѱ�����. */
    static bool s_Initialized;
};

#endif // __CLIENT_H__
