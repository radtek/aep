/**
* @file
* @brief Com类头文件.
* @author ruoxi
*
* 定义了Com类.
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

/**
* @class Component
* @brief 组件接口类.
*
* 组件接口类抽象出了关于组件的各种操作,
* 包括得到组件类型, 名字.
* FIXME
*/
class Component
{
public:
    /** @brief 组件类主版本号. */
    static UINT32 MajorVersion = 1;
    /** @brief 组件类副版本号. */
    static UINT32 MinorVersion = 1;

public:
    /**
    * @brief 得到组件类型.
    * @return 组件类型字符串.
    */
    const char *Type() = 0;
    /**
    * @brief 得到组件名字.
    * @return 组件名字字符串.
    */
    const char *Name() = 0;
};

#endif // __COMPONENT_H__
