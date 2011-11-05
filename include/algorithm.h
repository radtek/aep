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
#include <vector>
#include "rc.h"

using namespace std;

// 算法部分接口
interface IAlgorithm;

typedef vector<IAlgorithm *> AlgorithmList;

interface IAlgorithm
{
    virtual RC _stdcall GetName(LPWSTR *name) = 0;
    virtual RC _stdcall Run() = 0;
};

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
    /** @brief 初始化MatLab运行时环境. */
    RC Init();

    /** @brief 从配置文件中拿到算法列表. */
    RC RegisterAlgorithm(AlgorithmInfoList &algorithmInfoList);

    /** @brief 将一个算法添加到配置文件中. */
    RC AddAlgorithm(const AlgorithmInfo &algorithmInfo);

    /** @brief 运行一个算法. */
    RC RunAlgorithm(const AlgorithmInfo &algorithmInfo);

    /** @brief 算法列表配置文件名. */
    extern LPCWSTR AlgorithmListFileName;
};

#endif // __ALGORITHM_H__
