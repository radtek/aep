/**
* @file
* @brief 命令代码类cpp文件.
* @author ruoxi
*
* 实现命令代码类CC.
*/

#include "cc.h"
#include <map>

using namespace std;

/** @brief 创建命令代码与消息的对应map. */
static map<INT32, LPCWSTR> MakeCommandMap()
{
    map<INT32, LPCWSTR> commandMap;
    #undef DEFINE_COMMAND
    /** @brief 重定义命令代码的外包宏DEFINE_ERROR. */
    #define DEFINE_COMMAND(c) commandMap[CC::c] = TEXT(#c);
    /** @brief 用来开启允许包含errors.h头文件的开关. */
    #define __USE_COMMANDS__
    #include "commands.h"
    return commandMap;
}

/** @brief 全局命令代码与消息的对应map. */
static map<INT32, LPCWSTR> CommandMap = MakeCommandMap();

/**
*
* CC默认构造函数, 初始化为未知命令.
*/
CC::CC()
{
    Set(UNKNOWN_COMMAND);
}

/**
* @param cc 命令代码值.
*
* 接受一个INT32参数的CC构造函数. 初始化为cc的值.
* 可以实现从INT32至CC的隐式类型转换.
*/
CC::CC(INT32 cc)
{
    Set(cc);
}

/**
* @param cc 命令代码值.
*
* CC拷贝构造函数.
*/
CC::CC(const CC &cc)
{
    Set(cc.Get());
}

/**
* @param cc 命令代码值.
*
* 清除结果代码值为未知命令.
*/
void CC::Clear()
{
    m_Cc = UNKNOWN_COMMAND;
}

/**
* @param cc 命令代码值.
*
* 将一个INT32类型赋值给CC的赋值运算符.
* 可以实现直接将一个INT32类型赋值给一个CC对象.
*/
const CC & CC::operator=(INT32 cc)
{
    Set(cc);
    return *this;
}

/**
* @param cc 命令代码值.
*
* 将一个CC类型赋值给CC的赋值运算符.
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
* 转换成INT32类型的强制转换运算符.
* 可以实现直接将一个CC对象转换成INT32类型.
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
* @param cc 要设置的命令代码值.
*/
void CC::Set(INT32 cc)
{
    m_Cc = cc;
}
