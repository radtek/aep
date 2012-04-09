/**
* @file
* @brief 结果代码类cpp文件.
* @author ruoxi
*
* 实现结果代码类RC.
*/

#include "iarc.h"
#include <map>

using namespace std;

/** @brief 创建结果代码与消息的对应map. */
static map<INT32, LPCWSTR> MakeIaerrorMap()
{
    map<INT32, LPCWSTR> iaerrorMap;
    #undef DEFINE_IAERROR
    /** @brief 重定义结果代码的外包宏DEFINE_ERROR. */
    #define DEFINE_IAERROR(e, msg) iaerrorMap[IARC::e] = TEXT(msg);
    /** @brief 用来开启允许包含iaerrors.h头文件的开关. */
    #define __USE_IAERRORS__
    #include "iaerrors.h"
    return iaerrorMap;
}

/** @brief 全局结果代码与消息的对应map. */
static map<INT32, LPCWSTR> IaerrorMap = MakeIaerrorMap();

/**
*
* RC默认构造函数, 初始化为OK.
*/
IARC::IARC()
{
    Set(OK);
}

/**
* @param rc 结果代码值.
*
* 接受一个INT32参数的RC构造函数. 初始化为rc的值.
* 可以实现从INT32至RC的隐式类型转换.
*/
IARC::IARC(INT32 iarc)
{
    Set(iarc);
}

/**
* @param rc 结果代码值.
*
* RC拷贝构造函数.
*/
IARC::IARC(const IARC &iarc)
{
    Set(iarc.Get());
}

/**
* @param rc 结果代码值.
*
* 清除结果代码值为OK.
*/
void IARC::Clear()
{
    m_Iarc = OK;
}

/**
* @param rc 结果代码值.
*
* 将一个INT32类型赋值给RC的赋值运算符.
* 可以实现直接将一个INT32类型赋值给一个RC对象.
*/
const IARC & IARC::operator=(INT32 iarc)
{
    Set(iarc);
    return *this;
}

/**
* @param rc 结果代码值.
*
* 将一个RC类型赋值给RC的赋值运算符.
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
* 转换成INT32类型的强制转换运算符.
* 可以实现直接将一个RC对象转换成INT32类型.
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
* @param rc 要设置的结果代码值.
*/
void IARC::Set(INT32 iarc)
{
    m_Iarc = iarc;
}
