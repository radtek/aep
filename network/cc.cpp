/**
* @file
* @brief ���������cpp�ļ�.
* @author ruoxi
*
* ʵ�����������CC.
*/

#include "cc.h"
#include <map>

using namespace std;

/** @brief ���������������Ϣ�Ķ�Ӧmap. */
static map<INT32, LPCWSTR> MakeCommandMap()
{
    map<INT32, LPCWSTR> commandMap;
    #undef DEFINE_COMMAND
    /** @brief �ض����������������DEFINE_ERROR. */
    #define DEFINE_COMMAND(c) commandMap[CC::c] = TEXT(#c);
    /** @brief ���������������errors.hͷ�ļ��Ŀ���. */
    #define __USE_COMMANDS__
    #include "commands.h"
    return commandMap;
}

/** @brief ȫ�������������Ϣ�Ķ�Ӧmap. */
static map<INT32, LPCWSTR> CommandMap = MakeCommandMap();

/**
*
* CCĬ�Ϲ��캯��, ��ʼ��Ϊδ֪����.
*/
CC::CC()
{
    Set(UNKNOWN_COMMAND);
}

/**
* @param cc �������ֵ.
*
* ����һ��INT32������CC���캯��. ��ʼ��Ϊcc��ֵ.
* ����ʵ�ִ�INT32��CC����ʽ����ת��.
*/
CC::CC(INT32 cc)
{
    Set(cc);
}

/**
* @param cc �������ֵ.
*
* CC�������캯��.
*/
CC::CC(const CC &cc)
{
    Set(cc.Get());
}

/**
* @param cc �������ֵ.
*
* ����������ֵΪδ֪����.
*/
void CC::Clear()
{
    m_Cc = UNKNOWN_COMMAND;
}

/**
* @param cc �������ֵ.
*
* ��һ��INT32���͸�ֵ��CC�ĸ�ֵ�����.
* ����ʵ��ֱ�ӽ�һ��INT32���͸�ֵ��һ��CC����.
*/
const CC & CC::operator=(INT32 cc)
{
    Set(cc);
    return *this;
}

/**
* @param cc �������ֵ.
*
* ��һ��CC���͸�ֵ��CC�ĸ�ֵ�����.
*/
const CC & CC::operator=(const CC &cc)
{
    Set(cc);
    return *this;
}

INT32 CC::Get() const
{
    return m_Cc;
}

/**
*
* ת����INT32���͵�ǿ��ת�������.
* ����ʵ��ֱ�ӽ�һ��CC����ת����INT32����.
*/
CC::operator INT32() const
{
    return m_Cc;
}

LPCWSTR CC::Message() const
{
    return CommandMap[m_Cc];
}

/**
* @param cc Ҫ���õ��������ֵ.
*/
void CC::Set(INT32 cc)
{
    m_Cc = cc;
}
