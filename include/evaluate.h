/**
* @file
* @brief Evaluate�ͻ�����ͷ�ļ�.
* @author ruoxi
*
* ������Evaluate�ͻ�����.
*/

#ifndef __EVALUATE_H__
#define __EVALUATE_H__

#include "file_service.h"

#include "interfaces.h"

#include <engine.h>

struct AlgorithmRuntime
{
    wstring Name;
    wstring FilePath;
};

struct AlgorithmRuntimeResult
{
    UINT32 CpuPercentage;
    UINT32 MemoryUsageKB;
    UINT64 NS;
};

struct Factor
{
    wstring Name;
    wstring DllPath;
    wstring AlgorithmOutput;
    UINT32 AlgorithmOutputStart;
    UINT32 AlgorithmOutputEnd;
    wstring Origin;
    UINT32 OriginStart;
    UINT32 OriginEnd;
};

typedef mxArray Array;

struct FactorResult
{
    Array *Result;
};

/**
* @class Evaluate
* @brief Evaluate�ͻ�����.
*
* Evaluate�ͻ����������˹��ڿͻ��˵ĸ��ֲ���,
* ������ʼ��, �ر�, ����, �Ͽ�, ��½, ע��, ����ģ���ļ��ȹ���.
* ����Ϊ�ͻ��˹�����, ���������ͻ��˱�ʾ��(��ͼ�ν���).
* �������Ʋ����˵�̬ģʽ(singleton), �ڴ�����汣֤����ֻ����һ��ʵ��.
*/
class Evaluate
{
public:
    /** @brief Evaluate��������. */
    ~Evaluate();

    /** @brief Evaluate��ʼ��. */
    RC Init();
    /** @brief Evaluate�ر�. */
    RC Shut();

    RC SetRootPath(LPCWSTR rootPath);

    /** @brief ���÷�������������ַ. */
    RC SetFileServerHostName(const char *hostName);
    /** @brief ���÷���������˿�. */
    RC SetFileServerPort(int port);

    /** @brief ���÷�������������ַ. */
    RC SetModelHostName(const char *hostName);
    /** @brief ���÷���������˿�. */
    RC SetModelPort(int port);

    RC DoEvaluate(const vector<AlgorithmRuntime> &algorithms, const vector<Factor> &factors, vector<AlgorithmRuntimeResult> &algorithmResults, vector<FactorResult> &factorResults);

private:
    AlgorithmRuntimeResult EvaluateAlgorithmRuntime(const AlgorithmRuntime &algorithm);
    FactorResult EvaluateFactor(const Factor &factor);

    void DrawAlgorithmRuntime(const AlgorithmRuntime &algorithm, const AlgorithmRuntimeResult &algorithmResult);
    void DrawFactor(const Factor &factor, const FactorResult &factorResult);

    wstring m_RootPath;

    /** @brief ������������. */
    string m_FileServerHostName;
    /** @brief �����������˿�. */
    int m_FileServerPort;

    /** @brief ������������. */
    string m_ModelHostName;
    /** @brief �����������˿�. */
    int m_ModelPort;

    FileService m_FileServerFS, m_ModelFS;
    Engine *m_Engine;

public:
    /** @brief ���Evaluate��ʵ��. */
    static Evaluate &GetInstance();
    /** @brief ����Evaluate��ʵ��. */
    static void DestroyInstance();

private:
    /** @brief Evaluate˽��Ĭ�Ϲ��캯��. */
    Evaluate();
    /** @brief ���ڴ洢Evaluate��Ψһʵ����ָ��. */
    static Evaluate *s_Instance;
    /** @brief ���ڼ�¼Evaluate���Ψһʵ���Ƿ��ѱ�����. */
    static bool s_Initialized;
};

#endif // __EVALUATE_H__
