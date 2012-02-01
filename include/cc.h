/**
* @file
* @brief 命令代码类头文件.
* @author ruoxi
*
* 定义命令代码类CC.
*/

#ifndef __CC_H__
#define __CC_H__

/**
* @class CC
* @brief 命令代码类.
*
* 命令代码类.
* 表示服务器与客户端通信命令.
*/
class CC
{
public:
    /** @brief 所有命令代码的定义枚举. */
    enum
    {
        #undef DEFINE_COMMAND
        /** @brief 重定义命令代码类的外包宏DEFINE_ERROR. */
        #define DEFINE_COMMAND(c) c,
        /** @brief 用来开启允许包含commands.h头文件的开关. */
        #define __USE_COMMANDS__
        #include "commands.h"
    };

    /** @brief CC默认构造函数. */
    CC();
    /** @brief 接受一个INT32参数的CC构造函数. */
    CC(INT32 cc);
    /** @brief CC拷贝构造函数. */
    CC(const CC &cc);

    /** @brief 清除结果代码. */
    void Clear();

    /** @brief 将一个INT32类型赋值给CC的赋值运算符. */
    const CC & operator=(INT32 cc);
    /** @brief 将一个CC类型赋值给CC的赋值运算符. */
    const CC & operator=(const CC &cc);

    /** @brief 得到命令代码. */
    INT32 Get() const;
    /** @brief 转换成INT32类型的强制转换运算符. */
    operator INT32() const;
    /** @brief 得到命令代码所表示的消息. */
    LPCWSTR Message() const;

protected:
    /** @brief 设置命令代码. */
    void Set(INT32 cc);

private:
    /** @brief CC内部的INT32表示真正的命令代码. */
    INT32 m_Cc;
};

#endif // __CC_H__
