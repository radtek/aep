/**
* @file
* @brief Evaluate客户端类cpp文件.
* @author ruoxi
*
* 实现了Evaluate客户端类.
*/

#include "evaluate.h"

#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

/**
* @return Evaluate类的唯一实例.
*
* 用户只能通过该函数获得Evaluate类的唯一实例.
* 若Evaluate类还未被初始化, 则创建唯一的Evaluate类对象,
* 否则直接返回该对象.
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
* 将Evaluate类的唯一构造函数声明为私有,
* 可以保证编译器不会帮助生成其他构造函数,
* 并且该类不可以显式的实例化.
* 该构造函数并不完成具体的初始化,
* 初始化工作通过Init函数来完成.
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
* Evaluate类的析构函数.
* 该析构函数并不完成具体的销毁,
* 销毁工作通过Shut函数来完成.
*/
Evaluate::~Evaluate()
{
}

/**
* @return 结果代码.
*
* 完成Evaluate对象的初始化.
* 它对Socket环境进行初始化,
* 对平台进行初始化,
* 对TcpSocket对象进行初始化.
* 并且设置好默认的服务器主机地址和端口.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
*/
RC Evaluate::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(Algorithm::Init());

    m_FileServerFS.Init(m_RootPath.c_str(), m_FileServerHostName.c_str(), m_FileServerPort);
    m_ModelFS.Init(m_RootPath.c_str(), m_ModelHostName.c_str(), m_ModelPort);

    return rc;
}

/**
* @return 结果代码.
*
* 完成Evaluate对象的销毁.
* 它先销毁TcpSocket对象,
* 然后销毁平台,
* 最后清理Socket环境.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
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
* @param hostName 服务器主机名或地址.
*/
RC Evaluate::SetFileServerHostName(const char *hostName)
{
    RC rc;

    m_FileServerHostName = hostName;

    return rc;
}

/**
* @param port 服务器主机端口.
*/
RC Evaluate::SetFileServerPort(int port)
{
    RC rc;

    m_FileServerPort = port;

    return rc;
}

/**
* @param hostName 服务器主机名或地址.
*/
RC Evaluate::SetModelHostName(const char *hostName)
{
    RC rc;

    m_ModelHostName = hostName;

    return rc;
}

/**
* @param port 服务器主机端口.
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

    return rc;
}

RC Evaluate::DoSingleEvaluate(const vector<AlgorithmRuntime> &algorithms, const vector<Factor> &factors, vector<AlgorithmRuntimeResult> &algorithmResults, UINT32 i)
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
        CHECK_RC(EvaluateSingleFactor(factor, i));
    }

    return rc;
}

AlgorithmRuntimeResult Evaluate::EvaluateAlgorithmRuntime(const AlgorithmRuntime &algorithm)
{
    AlgorithmRuntimeResult result;
    if (OK != m_ModelFS.DownloadFile(algorithm.FilePath.c_str()))
    {
        return result;
    }
    wifstream ifs(algorithm.FilePath.c_str());
    if (!ifs)
    {
        return result;
    }
    UINT32 n = 0;
    ifs >> n;
    for (UINT32 i = 0; i < n; ++i)
    {
        UINT32 cpuPercentage = 0, memoryUsageKB = 0;
        UINT64 ns = 0;
        ifs >> cpuPercentage >> memoryUsageKB >> ns;
        result.CpuPercentage.push_back(cpuPercentage);
        result.MemoryUsageKB.push_back(memoryUsageKB);
        result.NS.push_back(ns);
    }
    ifs.close();
    return result;
}

RC Evaluate::EvaluateSingleFactor(const Factor &factor, UINT32 i)
{
    RC rc;

    wstring filePath = Utility::InsertNumToFileName(factor.AlgorithmOutput, factor.AlgorithmOutputStart + i);
    CHECK_RC(m_ModelFS.DownloadFile(filePath.c_str()));
    filePath = Utility::InsertNumToFileName(factor.Origin, factor.OriginStart + i);
    CHECK_RC(m_FileServerFS.DownloadFile(filePath.c_str()));

    return rc;
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

    if (OK != m_FileServerFS.DownloadFile(factor.TrueValue.c_str()))
    {
        return result;
    }
    Array *a = mxCreateString(Utility::Wstring2String(factor.TrueValue).c_str());
    input.push_back(a);

    if (OK != m_FileServerFS.DownloadFile(factor.WindowCenter.c_str()))
    {
        return result;
    }
    a = mxCreateString(Utility::Wstring2String(factor.WindowCenter).c_str());
    input.push_back(a);

    wstring funcName = Utility::StripExt(Utility::StripFilePath(factor.DllPath.c_str()));
    if (OK != MatLabHelper::RunFunc(factor.DllPath, funcName, output, input))
    {
        return result;
    }

    result.Result = output[0];

    return result;
}
