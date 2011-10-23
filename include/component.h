/**
* @file
* @brief Com��ͷ�ļ�.
* @author ruoxi
*
* ������Com��.
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

/**
* @class Component
* @brief ����ӿ���.
*
* ����ӿ��������˹�������ĸ��ֲ���,
* �����õ��������, ����.
* FIXME
*/
class Component
{
public:
    /** @brief ��������汾��. */
    static UINT32 MajorVersion = 1;
    /** @brief ����ั�汾��. */
    static UINT32 MinorVersion = 1;

public:
    /**
    * @brief �õ��������.
    * @return ��������ַ���.
    */
    const char *Type() = 0;
    /**
    * @brief �õ��������.
    * @return ��������ַ���.
    */
    const char *Name() = 0;
};

#endif // __COMPONENT_H__
