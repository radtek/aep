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
    Algorithm(LPCWSTR name, LPCWSTR dllFileName, LPCSTR funcName, LPCWSTR iconFileName);
    /** @brief ����һ���㷨. */
    RC Run();

public:
    /** @brief �õ��㷨����. */
    LPCWSTR GetName();

private:
    /** @brief �㷨����. */
    LPCWSTR m_Name;
    /** @brief �㷨DLL�ļ���. */
    LPCWSTR m_DllFileName;
    /** @brief �㷨��ں�������. */
    LPCSTR m_FuncName;
    /** @brief �㷨ͼ����. */
    LPCWSTR m_IconFileName;
};

typedef vector<Algorithm> AlgorithmList;

#endif // __ALGORITHM_H__
