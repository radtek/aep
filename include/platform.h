/**
* @file
* @brief ƽ̨ͷ�ļ�.
* @author ruoxi
*
* ������ƽ̨��.
*/

// FIXME: ����ƽ̨���Ƽ�ͼ���Ҫ��.

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "interfaces.h"
#include "algorithm.h"
#include "internal_algorithm.h"

/**
* @class Platform
* @brief Platformƽ̨��.
*
* Platformƽ̨��������ƽ̨��ȫ������,
* ������ʼ��, �ر�, ����ӿ�, ���, �㷨�ȵ�.
* �������Ʋ����˵�̬ģʽ(singleton), �ڴ�����汣֤����ֻ����һ��ʵ��.
*/
class Platform
{
public:
    // ƽ̨��ʼ�����ر�
    /** @brief ƽ̨��ʼ��. */
    RC Init();
    /** @brief ƽ̨�ر�. */
    RC Shut();

public:
    // ƽ̨����
    RC ValidateModel(bool &result);
    RC RunModel();

public:
    /** @brief ����ⲿ�ӿ������б�. */
    InterfaceTypeMap &GetInterfaceTypeMap();

    /** @brief �����������б�. */
    ComponentTypeMap &GetComponentTypeMap();
    /** @brief ������ʵ���б�. */
    ComponentList &GetComponentList();

    /** @brief ����㷨�б�. */
    AlgorithmList &GetAlgorithmList();

    /** @brief ����ڲ��㷨�б�. */
    InternalAlgorithmMap &GetInternalAlgorithmMap();

    /** @brief ������ID��ʼֵ. */
    UINT32 GetComponentIdStart();

private:
    // ƽ̨��������
    RC LoadComponentDll();
    RC RegisterInterfaceType();
    /** @brief ע�������������. */
    RC RegisterComponentType();
    RC RegisterGetComponentListFuncToComponent();
    /** @brief �ͷ��ⲿ���DLL�ļ�. */
    RC UnloadComponentDll();

    /** @brief ��ʼ���㷨���л���. */
    RC InitAlgorithm();
    /** @brief �ر��㷨���л���. */
    RC ShutAlgorithm();
    RC RegisterAlgorithm();

    /** @brief ע���ڲ��㷨. */
    RC RegisterInternalAlgorithm();
    RC UploadAlgorithm();

private:
    /** @brief �ⲿ�ӿ������б�. */
    InterfaceTypeMap m_InterfaceTypeMap;

    /** @brief �ⲿ��������б�. */
    ComponentTypeMap m_ComponentTypeMap;
    /** @brief ���ʵ���б�. */
    ComponentList m_ComponentList;

    /** @brief �㷨�б�. */
    AlgorithmList m_AlgorithmList;

    /** @brief �ڲ��㷨�б�. */
    InternalAlgorithmMap m_InternalAlgorithmMap;

    /** @brief �ⲿ���DLL���. */
    HINSTANCE m_ComponentDllHandle;

private:
    wstring m_ComponentDllFileName;
    /** @brief �ⲿ��������ļ���, ���ڴ�������ⲿ���DLL�ļ���. */
    wstring m_ComponentCfgFileName;
    /** @brief �㷨�����ļ���. */
    wstring m_AlgorithmCfgFileName;

public:
    /** @brief ���ƽ̨��ʵ��. */
    static Platform &GetInstance();

private:
    /** @brief ƽ̨˽��Ĭ�Ϲ��캯��. */
    Platform();
    /** @brief ���ڴ洢ƽ̨��Ψһʵ����ָ��. */
    static Platform *s_Instance;
    /** @brief ���ڼ�¼ƽ̨���Ψһʵ���Ƿ��ѱ�����. */
    static bool s_Initialized;

    /** @brief ƽ̨�����ļ���. */
    static LPCWSTR s_CfgFileName;
    /** @brief ������ƽ̨�����ļ��в����ⲿ��������ļ����Ĺؼ���. */
    static LPCWSTR s_ComponentDllFileNameKey;
    /** @brief ������ƽ̨�����ļ��в����ⲿ��������ļ����Ĺؼ���. */
    static LPCWSTR s_ComponentCfgFileNameKey;
    /** @brief ������ƽ̨�����ļ��в����㷨�����ļ����Ĺؼ���. */
    static LPCWSTR s_AlgorithmCfgFileNameKey;
};

#endif // __PLATFORM_H__
