/**
* @file
* @brief Server�������cpp�ļ�.
* @author ruoxi
*
* ʵ����Server�������.
*/

#include "server.h"
#include "utility.h"
#include "user_data_file.h"
#include "model.h"

LPCWSTR Server::s_UserFileName = TEXT("user.dat");

/**
* @return Server���Ψһʵ��.
*
* �û�ֻ��ͨ���ú������Server���Ψһʵ��.
* ��Server�໹δ����ʼ��, �򴴽�Ψһ��Server�����,
* ����ֱ�ӷ��ظö���.
*/
Server &Server::GetInstance()
{
    if (!s_Initialized)
    {
        s_Instance = new Server;
        s_Initialized = true;
    }
    return *s_Instance;
}

void Server::DestroyInstance()
{
    if (s_Initialized)
    {
        delete s_Instance;
        s_Instance = NULL;
        s_Initialized = false;
    }
}

/**
* ��Server���Ψһ���캯������Ϊ˽��,
* ���Ա�֤������������������������캯��,
* ���Ҹ��಻������ʽ��ʵ����.
* �ù��캯��������ɾ���ĳ�ʼ��,
* ��ʼ������ͨ��Init���������.
*/
Server::Server()
:
m_Platform(Platform::GetInstance()),
m_Logger(NULL)
{
}

Server *Server::s_Instance = NULL;

bool Server::s_Initialized = false;

Server::~Server()
{
}

/**
* @return �������.
*
* ���Server����ĳ�ʼ��.
* ����Socket�������г�ʼ��,
* ��ƽ̨���г�ʼ��,
* ��TcpSocket������г�ʼ��.
* �������ú�Ĭ�ϵķ���˶˿�.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Server::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_Platform.Init());
    CHECK_RC(m_Socket.Init());

    m_Port = 10086;

    Log(TEXT("��������ʼ�����."));

    return rc;
}

/**
* @return �������.
*
* ���Server���������.
* ��������TcpSocket����,
* Ȼ������ƽ̨,
* �������Socket����.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Server::Shut()
{
    RC rc;

    CHECK_RC(m_Socket.Shut());
    CHECK_RC(m_Platform.Shut());

    CHECK_RC(Socket::Shut());

    Log(TEXT("�������������."));

    return rc;
}

/**
* @return �������.
*
* ����һ��ϵͳ�߳�ר�Ž��м���,
* ��ʹ�������ܹ�ͬʱ��Ӧ�û�����,
* �������.
*/
RC Server::Listen()
{
    RC rc;

    HANDLE handle;
    handle = CreateThread(NULL,
        NULL,
        ThreadListen,
        (LPVOID)this,
        0,
        0);

    if(handle == NULL)
    {
        return RC::THREAD_CREATE_ERROR;
    }

    return OK;
}

/**
* @return �������.
*
* ������������������״̬. �ܹ�����������1�����ͻ���.
* ���пͻ�������, ��������, �õ��ͻ���Socket.
* ����һ��ServiceThread����, ���ͻ���Socket�����ʼ����ServiceThread����.
* ��ͨ��ϵͳ���ô�����һ�������߳����ڷ���ÿͻ���,
* �߳�����ThreadService����, ����ServiceThread������Ϊ��������.
* ����ķ������̺߳���Service�����.
*/
RC Server::RealListen()
{
    RC rc;

    CHECK_RC(m_Socket.Listen(m_Port));

    Log(TEXT("����ʼ����."));

    while (true)
    {
        TcpSocket *clientSocket = new TcpSocket();

        CHECK_RC(m_Socket.Accept(*clientSocket));

        Log(TEXT("���յ�һ��������."));
        ServiceThread *thread = new ServiceThread(clientSocket);

        HANDLE handle;
        handle = CreateThread(NULL,
            NULL,
            ThreadService,
            (LPVOID)thread,
            0,
            0);
        if(handle == NULL)
        {
            return RC::THREAD_CREATE_ERROR;
        }
    }
    return OK;
}

/**
* @param port ����˶˿�.
*/
void Server::SetPort(int port)
{
    m_Port = port;
}

/**
* @param logger �ӷ����Ӧ�ó���������־��¼��.
*/
void Server::SetLogger(Logger *logger)
{
    m_Logger = logger;
}

/**
* @param msg Ҫд����־����Ϣ.
*/
void Server::Log(LPCWSTR msg)
{
    if (m_Logger == NULL)
    {
        return;
    }
    m_Logger->Log(msg);
}

/**
* @param clientSocket �ͻ���Socket.
*
* ����һ���ͻ���Socket�����ʼ�������̶߳���.
* ��m_IsLogined��ʼ��Ϊfalse.
* ����ʼ����������ͻ��˵�TcpSocket����.
*/
Server::ServiceThread::ServiceThread(TcpSocket *clientSocket)
:
m_IsLogined(false),
m_ClientSocket(clientSocket),
m_Id(s_Counter++)
{
    Log(TEXT("��ʼ����."));
}

Server::ServiceThread::~ServiceThread()
{
    m_ClientSocket->Shut();
    delete m_ClientSocket;
    Log(TEXT("�˳�����."));
}

RC Server::ServiceThread::RecvCommand(CC &cc)
{
    return m_ClientSocket->RecvCommand(cc);
}

/**
* @return �������.
*
* �����û��ĵ�¼����.
* �ӿͻ���Socket����һ���û���������,
* ��ѯ�û������ļ�, �ж��û��������Ƿ���ȷ,
* �����Ͷ�Ӧ�Ľ�������֮�ͻ���.
* ����½�ɹ�, ������m_IsLoginedΪtrue, ��ʾ�Ѿ���¼.
*/
RC Server::ServiceThread::OnLogin()
{
    RC rc;

    wstring name, password;
    CHECK_RC(m_ClientSocket->RecvWString(name));
    CHECK_RC(m_ClientSocket->RecvWString(password));

    UserDataFile userDataFile(s_UserFileName);
    CHECK_RC(userDataFile.Parse());

    RC _rc = userDataFile.QueryUser(name, password);
    if (_rc == OK)
    {
        m_IsLogined = true;
        m_UserName = name;
    }
    CHECK_RC(m_ClientSocket->SendRC(_rc));

    wstring pathName = TEXT(".//") + m_UserName;
    if (!Utility::DirectoryExists(pathName.c_str()))
    {
        CreateDirectory(pathName.c_str(), NULL);
    }

    wstring msg = TEXT("�û�") + m_UserName + TEXT("�ѵ�¼.");
    Log(msg.c_str());

    return rc;
}

/**
* @return �������.
*
* �����û���ע������.
* �ӿͻ���Socket����һ���û���, ���뼰ȷ������.
* ��ѯ�û������ļ�, �ж��û��Ƿ��Ѵ���,
* �����Ͷ�Ӧ�Ľ�������֮�ͻ���.
* ��ע��ɹ�, ������û������ļ�, ���µ��û����������.
* ֮��Ϊ���û��������û��ڷ������ϵĹ���Ŀ¼,
* ���ڴ���û��ϴ���ģ�ͻ������ļ�, �Լ��㷨���в��������ݽ���ļ�.
*/
RC Server::ServiceThread::OnRegister()
{
    RC rc;

    wstring name, password;
    CHECK_RC(m_ClientSocket->RecvWString(name));
    CHECK_RC(m_ClientSocket->RecvWString(password));

    UserDataFile userDataFile(s_UserFileName);

    RC _rc = userDataFile.InsertUser(name, password);
    CHECK_RC(m_ClientSocket->SendRC(_rc));

    wstring msg = TEXT("ע���û�") + m_UserName + TEXT("�ɹ�.");
    Log(msg.c_str());

    return rc;
}

/**
* @return �������.
*
* �����û��ķ���ģ���ļ�����.
* �����û���+.mod��ģ���ļ�������û��Ĺ���Ŀ¼��.
* Ȼ�����ƽ̨����, ������ģ���ļ�,
* �ڷ�����ؽ�����ģ��, �������㷨���и�ģ��(FIXME),
* ֮�󽫲����������ļ����ͻؿͻ���.
* ����ͽ������,
* ��ǰ�����趼������, �򷵻�OK.
* �����Ͷ�Ӧ�Ĵ�����Ϣ��֪�û�.
*/
RC Server::ServiceThread::OnSendModelFile()
{
    RC rc;

    wstring fileName = m_UserName + TEXT(".mod");
    RC _rc = m_ClientSocket->RecvFile(fileName.c_str());

    if (_rc == OK)
    {
        CFile modFile(fileName.c_str(), CFile::modeRead);
        CArchive ar(&modFile, CArchive::load);
        Model model;
        if (OK == model.Load(ar))
        {
            Utility::PromptMessage(TEXT("ģ���ļ������ɹ�."));
            wstring datFileName = m_UserName + TEXT(".dat");
            wofstream os(datFileName.c_str());
            model.Run(os);
            os.close();
            _rc = m_ClientSocket->SendFile(datFileName.c_str());
            if (_rc == OK)
            {
                Utility::PromptMessage(TEXT("�����ļ����ͳɹ�."));
            }
            else
            {
                Utility::PromptMessage(TEXT("�����ļ�����ʧ��."));
            }
        }
        else
        {
            Utility::PromptErrorMessage(TEXT("ģ���ļ�����ʧ��."));
        }
    }

    CHECK_RC(m_ClientSocket->SendRC(_rc));

    wstring msg = TEXT("�����û�") + m_UserName + TEXT("ģ���ļ��ɹ�.");
    Log(msg.c_str());

    return rc;
}

RC Server::ServiceThread::OnUploadFile()
{
    RC rc;

    wstring pathName = TEXT(".//") + m_UserName + TEXT("//");

    wstring fileName;
    CHECK_RC(m_ClientSocket->RecvWString(fileName));
    fileName = pathName + fileName;
    CHECK_RC(m_ClientSocket->RecvFile(fileName.c_str()));

    wstring msg = TEXT("��Ӧ�û�") + m_UserName + TEXT("�ϴ��ļ��ɹ�.");
    Log(msg.c_str());

    return rc;
}

RC Server::ServiceThread::OnDownloadFile()
{
    RC rc;

    wstring fileName;
    CHECK_RC(m_ClientSocket->RecvWString(fileName));

    fileName = TEXT(".//") + m_UserName + TEXT("//") + fileName;

    RC _rc;
    if (!Utility::FileExists(fileName.c_str()))
    {
        _rc = RC::DOWNLOAD_UNEXISTEFD_FILE_ERROR;
        CHECK_RC(m_ClientSocket->SendRC(_rc));
        return _rc;
    }
    CHECK_RC(m_ClientSocket->SendRC(_rc));

    CHECK_RC(m_ClientSocket->SendFile(fileName.c_str()));

    wstring msg = TEXT("��Ӧ�û�")+ m_UserName + TEXT("�����ļ��ɹ�.");
    Log(msg.c_str());

    return rc;
}

RC Server::ServiceThread::OnGetFileList()
{
    RC rc;

    CFileFind fileFind;
    wstring path = TEXT(".//") + m_UserName + TEXT("//*.*");
    BOOL found = fileFind.FindFile(path.c_str());
    while(found)  
    {  
        found = fileFind.FindNextFile();
        if (!fileFind.IsDots() &&
            !fileFind.IsDirectory())
        {
            wstring fileName(fileFind.GetFileName());
            CHECK_RC(m_ClientSocket->SendWString(fileName.c_str()));
        }
    }
    CHECK_RC(m_ClientSocket->SendWString(TEXT(" ")));

    return rc;
}

RC Server::ServiceThread::OnLogout()
{
    RC rc;

    RC _rc;
    CHECK_RC(m_ClientSocket->SendRC(_rc));

    wstring msg = TEXT("�û�") + m_UserName + TEXT("���˳�.");
    Log(msg.c_str());

    return rc;
}

void Server::ServiceThread::Log(LPCWSTR msg)
{
    CString realMsg = TEXT("�����߳�");
    realMsg.AppendFormat(TEXT("%u: %s."), m_Id, msg);
    Server &server = Server::GetInstance();
    server.Log(realMsg);
}

UINT32 Server::ServiceThread::s_Counter = 0;

/**
* @param lparam ʵ������ΪServer�����ָ��, ��һ������ķ����ʵ��.
*
* ͨ�������Server����ִ�������ļ�������.
*/
DWORD WINAPI Server::ThreadListen(LPVOID lparam)
{
    Server *server = (Server *)lparam;

    server->RealListen();

    return 0;
}

/**
* @param lparam ʵ������ΪServiceThread, ��һ������ķ����̶߳���.
*
* ÿ��������̶߳�ͨ���ú�������һ���ض��ķ����̶߳���,
* ������һ������Ŀͻ���.
* �ú������Ͻ��տͻ��˷����ķ�����������,
* ������������ö�Ӧ�Ĺ��ܷ�����,
* ���½, ע��ȵ�.
* ֱ���ͻ��˷����˳�����, �ú����˳�,
* ͬʱ�߳̽�����ʹ��.
*/
DWORD WINAPI Server::ThreadService(LPVOID lparam)
{
    ServiceThread *thread = (ServiceThread *)lparam;

    CC cc;
    while (true)
    {
        RC rc;
        CHECK_RC_MSG_NR(thread->RecvCommand(cc));
        if (OK != rc)
        {
            delete thread;
            return 1;
        }
        switch (cc.Get())
        {
        case CC::LOGIN_COMMAND:
            thread->OnLogin();
            break;
        case CC::REGISTER_COMMAND:
            thread->OnRegister();
            break;
        case CC::SEND_MODEL_FILE_COMMAND:
            thread->OnSendModelFile();
            break;
        case CC::UPLOAD_FILE_COMMAND:
            thread->OnUploadFile();
            break;
        case CC::GET_FILE_LIST_COMMAND:
            thread->OnGetFileList();
            break;
        case CC::DOWNLOAD_FILE_COMMAND:
            thread->OnDownloadFile();
            break;
        case CC::LOGOUT_COMMAND:
            thread->OnLogout();
            break;
        default:
            break;
        }
        if (CC::LOGOUT_COMMAND == cc.Get())
        {
            delete thread;
            break;
        }
    }

    return 0;
}
