/**
* @file
* @brief �㷨��غ���ͷ�ļ�.
* @author ruoxi
*
* �������㷨��غ���.
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
    /** @brief ��ʼ��MatLab����ʱ����. */
    static RC Init();

    /** @brief �ر�MatLab����ʱ����. */
    static RC Shut();

    typedef bool (*InitializeFunc)(void);
    static LPCSTR InitializeFuncPrefix;

    typedef bool (*Func)(int, mxArray**, mxArray*, mxArray*);
    static LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    static LPCSTR TerminateFuncPrefix;

public:
    Algorithm(wstring name, wstring dllFileName, wstring funcName, wstring iconFileName);
    /** @brief ����һ���㷨. */
    RC Run();

public:
    /** @brief �õ��㷨����. */
    wstring GetName() const;
    /** @brief �õ��㷨DLL�ļ���. */
    wstring GetDllFileName() const;
    /** @brief �õ��㷨��ں�����. */
    wstring GetFuncName() const;
    /** @brief �õ��㷨ͼ���ļ���. */
    wstring GetIconFileName() const;

private:
    /** @brief �㷨����. */
    wstring m_Name;
    /** @brief �㷨DLL�ļ���. */
    wstring m_DllFileName;
    /** @brief �㷨��ں�������. */
    wstring m_FuncName;
    /** @brief �㷨ͼ���ļ���. */
    wstring m_IconFileName;
};

typedef vector<Algorithm> AlgorithmList;

#endif // __ALGORITHM_H__
