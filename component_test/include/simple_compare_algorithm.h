/**
* @file
* @brief �򵥱Ƚ��㷨��ͷ�ļ�.
* @author ruoxi
*
* �����˼򵥱Ƚ��㷨��.
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
