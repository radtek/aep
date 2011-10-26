/**
* @file
* @brief 结果代码类头文件.
* @author ruoxi
*
* 定义结果代码类RC.
*/

#ifndef __RC_H__
#define __RC_H__

/** @brief 将结果代码0定义为OK. */
const INT32 OK = 0;

/**
* @class RC
* @brief 结果代码类.
*
* 结果代码类.
* 表示函数运行结果的代码及对应信息, 并定义了所有错误代码及对应信息.
*/
class RC
{
public:
    /** @brief 所有结果代码的定义枚举. */
    enum
    {
        OK = ::OK,
        #undef DEFINE_ERROR
        /** @brief 重定义结果代码的外包宏DEFINE_ERROR. */
        #define DEFINE_ERROR(e, msg) e,
        /** @brief 用来开启允许包含errors.h头文件的开关. */
        #define __USE_ERRORS__
        #include "errors.h"
    };

    /** @brief RC默认构造函数. */
    RC();
    /** @brief 接受一个INT32参数的RC构造函数. */
    RC(INT32 rc);
    /** @brief RC拷贝构造函数. */
    RC(const RC &rc);

    /** @brief 清除结果代码. */
    void Clear();

    /** @brief 将一个INT32类型赋值给RC的赋值运算符. */
    const RC & operator=(INT32 rc);
    /** @brief 将一个RC类型赋值给RC的赋值运算符. */
    const RC & operator=(const RC &rc);

    /** @brief 得到结果代码. */
    INT32 Get() const;
    /** @brief 转换成INT32类型的强制转换运算符. */
    operator INT32() const;
    /** @brief 得到结果代码所表示的消息. */
    LPCWSTR Message() const;

protected:
    /** @brief 设置结果代码. */
    void Set(INT32 rc);

private:
    /** @brief RC内部的INT32表示真正的结果代码. */
    INT32 m_Rc;
};

/** @brief 检测函数返回的RC是否为错误的宏. */
#define CHECK_RC(f) \
    do \
    { \
        if (OK != (rc = (f))) \
        return rc; \
    } while(0)

#endif // __RC_H__
