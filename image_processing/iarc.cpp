/**
* @file
* @brief ���������cpp�ļ�.
* @author ruoxi
*
* ʵ�ֽ��������RC.
*/

#include "iarc.h"
#include <map>

using namespace std;

/** @brief ���������������Ϣ�Ķ�Ӧmap. */
static map<INT32, LPCWSTR> MakeIaerrorMap()
{
    map<INT32, LPCWSTR> iaerrorMap;
    #undef DEFINE_IAERROR
    /** @brief �ض���������������DEFINE_ERROR. */
    #define DEFINE_IAERROR(e, msg) iaerrorMap[IARC::e] = TEXT(msg);
    /** @brief ���������������iaerrors.hͷ�ļ��Ŀ���. */
    #define __USE_IAERRORS__
    #include "iaerrors.h"
    return iaerrorMap;
}

/** @brief ȫ�ֽ����������Ϣ�Ķ�Ӧmap. */
static map<INT32, LPCWSTR> IaerrorMap = MakeIaerrorMap();

/**
*
* RCĬ�Ϲ��캯��, ��ʼ��ΪOK.
*/
IARC::IARC()
{
    Set(OK);
}

/**
* @param rc �������ֵ.
*
* ����һ��INT32������RC���캯��. ��ʼ��Ϊrc��ֵ.
* ����ʵ�ִ�INT32��RC����ʽ����ת��.
*/
IARC::IARC(INT32 iarc)
{
    Set(iarc);
}

/**
* @param rc �������ֵ.
*
* RC�������캯��.
*/
IARC::IARC(const IARC &iarc)
{
    Set(iarc.Get());
}

/**
* @param rc �������ֵ.
*
* ����������ֵΪOK.
*/
void IARC::Clear()
{
    m_Iarc = OK;
}

/**
* @param rc �������ֵ.
*
* ��һ��INT32���͸�ֵ��RC�ĸ�ֵ�����.
* ����ʵ��ֱ�ӽ�һ��INT32���͸�ֵ��һ��RC����.
*/
const IARC & IARC::operator=(INT32 iarc)
{
    Set(iarc);
    return *this;
}

/**
* @param rc �������ֵ.
*
* ��һ��RC���͸�ֵ��RC�ĸ�ֵ�����.
*/
const IARC & IARC::operator=(const IARC &iarc)
{
    Set(iarc);
    return *this;
}

INT32 IARC::Get() const
{
    return m_Iarc;
}

/**
*
* ת����INT32���͵�ǿ��ת�������.
* ����ʵ��ֱ�ӽ�һ��RC����ת����INT32����.
*/
IARC::operator INT32() const
{
    return m_Iarc;
}

LPCWSTR IARC::Message() const
{
    return IaerrorMap[m_Iarc];
}

/**
* @param rc Ҫ���õĽ������ֵ.
*/
void IARC::Set(INT32 iarc)
{
    m_Iarc = iarc;
}
