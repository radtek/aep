/**
* @file
* @brief 算法相关函数头文件.
* @author ruoxi
*
* 定义了算法相关函数.
*/

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <objbase.h>
#include <string>
#include <vector>
#include "rc.h"

#include "mclmcrrt.h"
#include "mclcppclass.h"

using namespace std;

class Algorithm
{
public:
    /** @brief 初始化MatLab运行时环境. */
    static RC Init();

    /** @brief 关闭MatLab运行时环境. */
    static RC Shut();

    typedef bool (*InitializeFunc)(void);
    static LPCSTR InitializeFuncPrefix;

    typedef bool (*Func)(int, mxArray**, mxArray*, mxArray*);
    static LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    static LPCSTR TerminateFuncPrefix;

public:
    Algorithm(wstring name, wstring dllFileName, wstring funcName, wstring iconFileName);
    /** @brief 运行一个算法. */
    RC Run();

public:
    /** @brief 得到算法名称. */
    wstring GetName() const;
    /** @brief 得到算法DLL文件名. */
    wstring GetDllFileName() const;
    /** @brief 得到算法入口函数名. */
    wstring GetFuncName() const;
    /** @brief 得到算法图标文件名. */
    wstring GetIconFileName() const;

private:
    /** @brief 算法名称. */
    wstring m_Name;
    /** @brief 算法DLL文件名. */
    wstring m_DllFileName;
    /** @brief 算法入口函数名称. */
    wstring m_FuncName;
    /** @brief 算法图标文件名. */
    wstring m_IconFileName;
};

typedef vector<Algorithm> AlgorithmList;

#endif // __ALGORITHM_H__
