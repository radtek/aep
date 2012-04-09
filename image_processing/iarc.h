/**
* @file
* @brief ���������ͷ�ļ�.
* @author ruoxi
*
* ������������RC.
*/

#ifndef __IARC_H__
#define __IARC_H__

#include "rc.h"

/**
* @class RC
* @brief ���������.
*
* ���������.
* ��ʾ�������н���Ĵ��뼰��Ӧ��Ϣ, �����������д�����뼰��Ӧ��Ϣ.
*/
class IARC
{
public:
    /** @brief ���н������Ķ���ö��. */
    enum
    {
        OK = ::OK,
        #undef DEFINE_IAERROR
        /** @brief �ض���������������DEFINE_ERROR. */
        #define DEFINE_IAERROR(e, msg) e,
        /** @brief ���������������errors.hͷ�ļ��Ŀ���. */
        #define __USE_IAERRORS__
        #include "iaerrors.h"
    };

    /** @brief RCĬ�Ϲ��캯��. */
    IARC();
    /** @brief ����һ��INT32������RC���캯��. */
    IARC(INT32 iarc);
    /** @brief RC�������캯��. */
    IARC(const IARC &iarc);

    /** @brief ����������. */
    void Clear();

    /** @brief ��һ��INT32���͸�ֵ��RC�ĸ�ֵ�����. */
    const IARC & operator=(INT32 iarc);
    /** @brief ��һ��RC���͸�ֵ��RC�ĸ�ֵ�����. */
    const IARC & operator=(const IARC &iarc);

    /** @brief �õ��������. */
    INT32 Get() const;
    /** @brief ת����INT32���͵�ǿ��ת�������. */
    operator INT32() const;
    /** @brief �õ������������ʾ����Ϣ. */
    LPCWSTR Message() const;

protected:
    /** @brief ���ý������. */
    void Set(INT32 iarc);

private:
    /** @brief RC�ڲ���INT32��ʾ�����Ľ������. */
    INT32 m_Iarc;
};

#endif // __IARC_H__
