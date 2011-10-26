/**
* @file
* @brief ���������cpp�ļ�.
* @author ruoxi
*
* ʵ�ֽ��������RC.
*/

#include "rc.h"
#include <map>

using namespace std;

/** @brief ���������������Ϣ�Ķ�Ӧmap. */
static map<INT32, LPCWSTR> MakeErrorMap()
{
    map<INT32, LPCWSTR> errorMap;
    #undef DEFINE_ERROR
    /** @brief �ض���������������DEFINE_ERROR. */
    #define DEFINE_ERROR(e, msg) errorMap[RC::e] = TEXT(msg);
    /** @brief ���������������errors.hͷ�ļ��Ŀ���. */
    #define __USE_ERRORS__
    #include "errors.h"
    return errorMap;
}

/** @brief ȫ�ֽ����������Ϣ�Ķ�Ӧmap. */
static map<INT32, LPCWSTR> ErrorMap = MakeErrorMap();

/**
*
* RCĬ�Ϲ��캯��, ��ʼ��ΪOK.
*/
RC::RC()
{
    Set(OK);
}

/**
* @param rc �������ֵ.
*
* ����һ��INT32������RC���캯��. ��ʼ��Ϊrc��ֵ.
* ����ʵ�ִ�INT32��RC����ʽ����ת��.
*/
RC::RC(INT32 rc)
{
    Set(rc);
}

RC::RC(const RC &rc)
{
    Set(rc.Get());
}

void RC::Clear()
{
    m_Rc = OK;
}

/**
* @param rc �������ֵ.
*
* ��һ��INT32���͸�ֵ��RC�ĸ�ֵ�����.
* ����ʵ��ֱ�ӽ�һ��INT32���͸�ֵ��һ��RC����.
*/
const RC & RC::operator=(INT32 rc)
{
    Set(rc);
    return *this;
}

const RC & RC::operator=(const RC &rc)
{
    Set(rc);
    return *this;
}

INT32 RC::Get() const
{
    return m_Rc;
}

/**
*
* ת����INT32���͵�ǿ��ת�������.
* ����ʵ��ֱ�ӽ�һ��RC����ת����INT32����.
*/
RC::operator INT32() const
{
    return m_Rc;
}

LPCWSTR RC::Message() const
{
    return ErrorMap[m_Rc];
}

/**
* @param rc Ҫ���õĽ������ֵ.
*/
void RC::Set(INT32 rc)
{
    m_Rc = rc;
}
