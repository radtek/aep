/**
* @file
* @brief �㷨��غ���ͷ�ļ�.
* @author ruoxi
*
* �������㷨��غ���.
*/

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "interfaces.h"
#include "rc.h"
#include <string>
#include <vector>

using namespace std;

class Algorithm
{
public:
    /** @brief ��ʼ��MatLab����ʱ����. */
    static RC Init();

    /** @brief �ر�MatLab����ʱ����. */
    static RC Shut();

    typedef vector<wstring> ParamNameList;
    typedef vector<IParam *> ParamList;

public:
    Algorithm(UINT32 id,
        wstring name,
        wstring dllFileName,
        wstring funcName,
        wstring iconFileName,
        ParamNameList paramNameList);
    /** @brief ����һ���㷨. */
    RC Run(ComponentList &componentList);

public:
    /** @brief �õ��㷨ID. */
    UINT32 GetId() const;
    /** @brief �õ��㷨����. */
    wstring GetName() const;
    /** @brief �õ��㷨DLL�ļ���. */
    wstring GetDllFileName() const;
    /** @brief �õ��㷨��ں�����. */
    wstring GetFuncName() const;
    /** @brief �õ��㷨ͼ���ļ���. */
    wstring GetIconFileName() const;

private:
    /** @brief �㷨ID. */
    UINT32 m_Id;
    /** @brief �㷨����. */
    wstring m_Name;
    /** @brief �㷨DLL�ļ���. */
    wstring m_DllFileName;
    /** @brief �㷨��ں�������. */
    wstring m_FuncName;
    /** @brief �㷨ͼ���ļ���. */
    wstring m_IconFileName;
    /** @brief �������б� */
    ParamNameList m_ParamNameList;
};

#endif // __ALGORITHM_H__
