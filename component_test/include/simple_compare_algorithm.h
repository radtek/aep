/**
* @file
* @brief 简单比较算法类头文件.
* @author ruoxi
*
* 定义了简单比较算法类.
*/

#ifndef __SIMPLE_COMPARE_ALGORITHM_H__
#define __SIMPLE_COMPARE_ALGORITHM_H__

#include "interfaces.h"

class SimpleCompareAlgorithm : public IAlgorithm
{
public:
    virtual RC _stdcall GetName(LPWSTR *name);
    virtual RC _stdcall Run();

public:
    LPWSTR m_Name;

public:
    static LPCWSTR SimpleCompareAlgorithmName;
};

#endif // __SIMPLE_COMPARE_ALGORITHM_H__
