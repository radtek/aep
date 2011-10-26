/**
* @file
* @brief 结果代码类cpp文件.
* @author ruoxi
*
* 实现结果代码类RC.
*/

#include "rc.h"
#include <map>

using namespace std;

/** @brief 创建结果代码与消息的对应map. */
static map<INT32, LPCWSTR> MakeErrorMap()
{
    map<INT32, LPCWSTR> errorMap;
    #undef DEFINE_ERROR
    /** @brief 重定义结果代码的外包宏DEFINE_ERROR. */
    #define DEFINE_ERROR(e, msg) errorMap[RC::e] = TEXT(msg);
    /** @brief 用来开启允许包含errors.h头文件的开关. */
    #define __USE_ERRORS__
    #include "errors.h"
    return errorMap;
}

/** @brief 全局结果代码与消息的对应map. */
static map<INT32, LPCWSTR> ErrorMap = MakeErrorMap();

/**
*
* RC默认构造函数, 初始化为OK.
*/
RC::RC()
{
    Set(OK);
}

/**
* @param rc 结果代码值.
*
* 接受一个INT32参数的RC构造函数. 初始化为rc的值.
* 可以实现从INT32至RC的隐式类型转换.
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
* @param rc 结果代码值.
*
* 将一个INT32类型赋值给RC的赋值运算符.
* 可以实现直接将一个INT32类型赋值给一个RC对象.
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
* 转换成INT32类型的强制转换运算符.
* 可以实现直接将一个RC对象转换成INT32类型.
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
* @param rc 要设置的结果代码值.
*/
void RC::Set(INT32 rc)
{
    m_Rc = rc;
}
