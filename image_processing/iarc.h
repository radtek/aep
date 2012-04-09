/**
* @file
* @brief 结果代码类头文件.
* @author ruoxi
*
* 定义结果代码类RC.
*/

#ifndef __IARC_H__
#define __IARC_H__

#include "rc.h"

/**
* @class RC
* @brief 结果代码类.
*
* 结果代码类.
* 表示函数运行结果的代码及对应信息, 并定义了所有错误代码及对应信息.
*/
class IARC
{
public:
    /** @brief 所有结果代码的定义枚举. */
    enum
    {
        OK = ::OK,
        #undef DEFINE_IAERROR
        /** @brief 重定义结果代码的外包宏DEFINE_ERROR. */
        #define DEFINE_IAERROR(e, msg) e,
        /** @brief 用来开启允许包含errors.h头文件的开关. */
        #define __USE_IAERRORS__
        #include "iaerrors.h"
    };

    /** @brief RC默认构造函数. */
    IARC();
    /** @brief 接受一个INT32参数的RC构造函数. */
    IARC(INT32 iarc);
    /** @brief RC拷贝构造函数. */
    IARC(const IARC &iarc);

    /** @brief 清除结果代码. */
    void Clear();

    /** @brief 将一个INT32类型赋值给RC的赋值运算符. */
    const IARC & operator=(INT32 iarc);
    /** @brief 将一个RC类型赋值给RC的赋值运算符. */
    const IARC & operator=(const IARC &iarc);

    /** @brief 得到结果代码. */
    INT32 Get() const;
    /** @brief 转换成INT32类型的强制转换运算符. */
    operator INT32() const;
    /** @brief 得到结果代码所表示的消息. */
    LPCWSTR Message() const;

protected:
    /** @brief 设置结果代码. */
    void Set(INT32 iarc);

private:
    /** @brief RC内部的INT32表示真正的结果代码. */
    INT32 m_Iarc;
};

#endif // __IARC_H__
