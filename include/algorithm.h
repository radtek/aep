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

/*
// �㷨���ֽӿ�
interface IAlgorithm;

typedef vector<IAlgorithm *> AlgorithmList;

interface IAlgorithm
{
    virtual RC _stdcall GetName(LPWSTR *name) = 0;
    virtual RC _stdcall Run() = 0;
};
*/

typedef struct
{
    LPCWSTR name;
    LPCWSTR dllFileName;
    LPCSTR funcName;
    void *iconHandle;
} AlgorithmInfo;

typedef vector<AlgorithmInfo> AlgorithmInfoList;

namespace Algorithm
{
    /** @brief ��ʼ��MatLab����ʱ����. */
    RC Init();

    /** @brief �ر�MatLab����ʱ����. */
    RC Shut();

    /** @brief �������ļ����õ��㷨�б�. */
    RC RegisterAlgorithm(LPCWSTR algorithmCfgFileName,
        AlgorithmInfoList &algorithmInfoList);

    /** @brief ��һ���㷨��ӵ������ļ���. */
    RC AddAlgorithm(const AlgorithmInfo &algorithmInfo);

    /** @brief ����һ���㷨. */
    RC RunAlgorithm(const AlgorithmInfo &algorithmInfo);

    typedef bool (*InitializeFunc)(void);
    extern LPCSTR InitializeFuncPrefix;

    typedef bool (*Func)(int, mxArray**, mxArray*, mxArray*);
    extern LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    extern LPCSTR TerminateFuncPrefix;
};

#endif // __ALGORITHM_H__
