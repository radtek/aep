/**
* @file
* @brief Evaluate客户端类头文件.
* @author ruoxi
*
* 定义了Evaluate客户端类.
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
* @brief Evaluate客户端类.
*
* Evaluate客户端类抽象出了关于客户端的各种操作,
* 包括初始化, 关闭, 连接, 断开, 登陆, 注册, 发送模型文件等功能.
* 该类为客户端功能类, 并不包含客户端表示层(即图形界面).
* 该类的设计采用了单态模式(singleton), 在代码层面保证了它只能有一个实例.
*/
class Evaluate
{
public:
    /** @brief Evaluate析构函数. */
    ~Evaluate();

    /** @brief Evaluate初始化. */
    RC Init();
    /** @brief Evaluate关闭. */
    RC Shut();

    RC SetRootPath(LPCWSTR rootPath);

    /** @brief 设置服务端主机名或地址. */
    RC SetFileServerHostName(const char *hostName);
    /** @brief 设置服务端主机端口. */
    RC SetFileServerPort(int port);

    /** @brief 设置服务端主机名或地址. */
    RC SetModelHostName(const char *hostName);
    /** @brief 设置服务端主机端口. */
    RC SetModelPort(int port);

    RC DoEvaluate(const vector<AlgorithmRuntime> &algorithms, const vector<Factor> &factors, vector<AlgorithmRuntimeResult> &algorithmResults, vector<FactorResult> &factorResults);

private:
    AlgorithmRuntimeResult EvaluateAlgorithmRuntime(const AlgorithmRuntime &algorithm);
    FactorResult EvaluateFactor(const Factor &factor);

    void DrawAlgorithmRuntime(const AlgorithmRuntime &algorithm, const AlgorithmRuntimeResult &algorithmResult);
    void DrawFactor(const Factor &factor, const FactorResult &factorResult);

    wstring m_RootPath;

    /** @brief 服务器主机名. */
    string m_FileServerHostName;
    /** @brief 服务器主机端口. */
    int m_FileServerPort;

    /** @brief 服务器主机名. */
    string m_ModelHostName;
    /** @brief 服务器主机端口. */
    int m_ModelPort;

    FileService m_FileServerFS, m_ModelFS;
    Engine *m_Engine;

public:
    /** @brief 获得Evaluate类实例. */
    static Evaluate &GetInstance();
    /** @brief 销毁Evaluate类实例. */
    static void DestroyInstance();

private:
    /** @brief Evaluate私有默认构造函数. */
    Evaluate();
    /** @brief 用于存储Evaluate类唯一实例的指针. */
    static Evaluate *s_Instance;
    /** @brief 用于记录Evaluate类的唯一实例是否已被创建. */
    static bool s_Initialized;
};

#endif // __EVALUATE_H__
