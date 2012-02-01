/**
* @file
* @brief ���������ͷ�ļ�.
* @author ruoxi
*
* �������������CC.
*/

#ifndef __CC_H__
#define __CC_H__

/**
* @class CC
* @brief ���������.
*
* ���������.
* ��ʾ��������ͻ���ͨ������.
*/
class CC
{
public:
    /** @brief �����������Ķ���ö��. */
    enum
    {
        #undef DEFINE_COMMAND
        /** @brief �ض������������������DEFINE_ERROR. */
        #define DEFINE_COMMAND(c) c,
        /** @brief ���������������commands.hͷ�ļ��Ŀ���. */
        #define __USE_COMMANDS__
        #include "commands.h"
    };

    /** @brief CCĬ�Ϲ��캯��. */
    CC();
    /** @brief ����һ��INT32������CC���캯��. */
    CC(INT32 cc);
    /** @brief CC�������캯��. */
    CC(const CC &cc);

    /** @brief ����������. */
    void Clear();

    /** @brief ��һ��INT32���͸�ֵ��CC�ĸ�ֵ�����. */
    const CC & operator=(INT32 cc);
    /** @brief ��һ��CC���͸�ֵ��CC�ĸ�ֵ�����. */
    const CC & operator=(const CC &cc);

    /** @brief �õ��������. */
    INT32 Get() const;
    /** @brief ת����INT32���͵�ǿ��ת�������. */
    operator INT32() const;
    /** @brief �õ������������ʾ����Ϣ. */
    LPCWSTR Message() const;

protected:
    /** @brief �����������. */
    void Set(INT32 cc);

private:
    /** @brief CC�ڲ���INT32��ʾ�������������. */
    INT32 m_Cc;
};

#endif // __CC_H__
