/**
* @file
* @brief Evaluate�ͻ�����cpp�ļ�.
* @author ruoxi
*
* ʵ����Evaluate�ͻ�����.
*/

#include "evaluate.h"

#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

/**
* @return Evaluate���Ψһʵ��.
*
* �û�ֻ��ͨ���ú������Evaluate���Ψһʵ��.
* ��Evaluate�໹δ����ʼ��, �򴴽�Ψһ��Evaluate�����,
* ����ֱ�ӷ��ظö���.
*/
Evaluate &Evaluate::GetInstance()
{
    if (!s_Initialized)
    {
        s_Instance = new Evaluate;
        s_Initialized = true;
    }
    return *s_Instance;
}

void Evaluate::DestroyInstance()
{
    if (s_Initialized)
    {
        delete s_Instance;
        s_Instance = NULL;
        s_Initialized = false;
    }
}

/**
* ��Evaluate���Ψһ���캯������Ϊ˽��,
* ���Ա�֤������������������������캯��,
* ���Ҹ��಻������ʽ��ʵ����.
* �ù��캯��������ɾ���ĳ�ʼ��,
* ��ʼ������ͨ��Init���������.
*/
Evaluate::Evaluate()
: m_RootPath(TEXT("."))
, m_FileServerHostName("localhost")
, m_FileServerPort(10086)
, m_ModelHostName("localhost")
, m_ModelPort(10087)
{
}

Evaluate *Evaluate::s_Instance = NULL;

bool Evaluate::s_Initialized = false;

/**
* Evaluate�����������.
* ����������������ɾ��������,
* ���ٹ���ͨ��Shut���������.
*/
Evaluate::~Evaluate()
{
}

/**
* @return �������.
*
* ���Evaluate����ĳ�ʼ��.
* ����Socket�������г�ʼ��,
* ��ƽ̨���г�ʼ��,
* ��TcpSocket������г�ʼ��.
* �������ú�Ĭ�ϵķ�����������ַ�Ͷ˿�.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Evaluate::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    if (!(m_Engine = engOpen(NULL)))
    {
        return RC::MODEL_MATLAB_ENGINE_ERROR;
    }

    CHECK_RC(Algorithm::Init());

    m_FileServerFS.Init(m_RootPath.c_str(), m_FileServerHostName.c_str(), m_FileServerPort);
    m_ModelFS.Init(m_RootPath.c_str(), m_ModelHostName.c_str(), m_ModelPort);

    return rc;
}

/**
* @return �������.
*
* ���Evaluate���������.
* ��������TcpSocket����,
* Ȼ������ƽ̨,
* �������Socket����.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC Evaluate::Shut()
{
    RC rc;

    m_FileServerFS.Shut();
    m_ModelFS.Shut();

    CHECK_RC(Socket::Shut());

    return rc;
}

RC Evaluate::SetRootPath(LPCWSTR rootPath)
{
    RC rc;

    m_RootPath = rootPath;

    return rc;
}

/**
* @param hostName ���������������ַ.
*/
RC Evaluate::SetFileServerHostName(const char *hostName)
{
    RC rc;

    m_FileServerHostName = hostName;

    return rc;
}

/**
* @param port �����������˿�.
*/
RC Evaluate::SetFileServerPort(int port)
{
    RC rc;

    m_FileServerPort = port;

    return rc;
}

/**
* @param hostName ���������������ַ.
*/
RC Evaluate::SetModelHostName(const char *hostName)
{
    RC rc;

    m_ModelHostName = hostName;

    return rc;
}

/**
* @param port �����������˿�.
*/
RC Evaluate::SetModelPort(int port)
{
    RC rc;

    m_ModelPort = port;

    return rc;
}

RC Evaluate::DoEvaluate(const vector<AlgorithmRuntime> &algorithms, const vector<Factor> &factors, vector<AlgorithmRuntimeResult> &algorithmResults, vector<FactorResult> &factorResults)
{
    RC rc;

    for (UINT32 i = 0; i < algorithms.size(); ++i)
    {
        const AlgorithmRuntime &algorithm = algorithms[i];
        algorithmResults.push_back(EvaluateAlgorithmRuntime(algorithm));
    }

    for (UINT32 i = 0; i < factors.size(); ++i)
    {
        const Factor &factor = factors[i];
        factorResults.push_back(EvaluateFactor(factor));
    }

    for (UINT32 i = 0; i < algorithms.size(); ++i)
    {
        DrawAlgorithmRuntime(algorithms[i], algorithmResults[i]);
    }

    for (UINT32 i = 0; i < factors.size(); ++i)
    {
        DrawFactor(factors[i], factorResults[i]);
    }

    return rc;
}

AlgorithmRuntimeResult Evaluate::EvaluateAlgorithmRuntime(const AlgorithmRuntime &algorithm)
{
    AlgorithmRuntimeResult result;
    result.CpuPercentage = 0;
    result.MemoryUsageKB = 0;
    result.NS = 0;
    if (OK != m_ModelFS.DownloadFile(algorithm.FilePath.c_str()))
    {
        return result;
    }
    wifstream ifs(algorithm.FilePath.c_str());
    if (!ifs)
    {
        return result;
    }
    ifs >> result.CpuPercentage >> result.MemoryUsageKB >> result.NS;
    ifs.close();
    return result;
}

FactorResult Evaluate::EvaluateFactor(const Factor &factor)
{
    FactorResult result;
    result.Result = NULL;
    vector<Array *> output(1);
    vector<Array *> input;

    vector<Array *> algorithmOutputArray;
    for (UINT32 i = factor.AlgorithmOutputStart; i <= factor.AlgorithmOutputEnd; ++i)
    {
        wstring filePath = Utility::InsertNumToFileName(factor.AlgorithmOutput, i);
        if (OK != m_ModelFS.DownloadFile(filePath.c_str()))
        {
            return result;
        }
        Array *a = mxCreateString(Utility::Wstring2String(filePath).c_str());
        algorithmOutputArray.push_back(a);
    }
    mwSize algorithmOutputDim[1];
    algorithmOutputDim[0] = algorithmOutputArray.size();
    Array *algorithmOutput = mxCreateCellArray(1, algorithmOutputDim);
    for (UINT32 i = 0; i < algorithmOutputArray.size(); ++i)
    {
        mxSetCell(algorithmOutput, i, algorithmOutputArray[i]);
    }
    input.push_back(algorithmOutput);

    vector<Array *> originArray;
    for (UINT32 i = factor.OriginStart; i <= factor.OriginEnd; ++i)
    {
        wstring filePath = Utility::InsertNumToFileName(factor.Origin, i);
        if (OK != m_FileServerFS.DownloadFile(filePath.c_str()))
        {
            return result;
        }
        Array *a = mxCreateString(Utility::Wstring2String(filePath).c_str());
        originArray.push_back(a);
    }
    mwSize originDim[1];
    originDim[0] = originArray.size();
    Array *origin = mxCreateCellArray(1, originDim);
    for (UINT32 i = 0; i < originArray.size(); ++i)
    {
        mxSetCell(origin, i, originArray[i]);
    }
    input.push_back(origin);

    if (OK != MatLabHelper::RunFunc(factor.DllPath, TEXT("evaluate"), output, input))
    {
        return result;
    }

    result.Result = output[0];

    return result;
}

void Evaluate::DrawAlgorithmRuntime(const AlgorithmRuntime &algorithm, const AlgorithmRuntimeResult &algorithmResult)
{
}

void Evaluate::DrawFactor(const Factor &factor, const FactorResult &factorResult)
{
    mwSize size = factor.AlgorithmOutputEnd - factor.AlgorithmOutputStart + 1;
    Array *x = mxCreateDoubleMatrix(1, size, mxREAL);

    double *p = mxGetPr(x);
    for (UINT32 i = factor.AlgorithmOutputStart; i <= factor.AlgorithmOutputEnd; ++i)
    {
        p[i - factor.AlgorithmOutputStart] = i;
    }

    engPutVariable(m_Engine, "X", x);
    engPutVariable(m_Engine, "Y", factorResult.Result);

    engEvalString(m_Engine, "plot(X, Y);");
    engEvalString(m_Engine, "xlabel('X');");
    engEvalString(m_Engine, "ylabel('Y');");

    mxDestroyArray(x);
    mxDestroyArray(factorResult.Result);
}
