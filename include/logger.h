/**
* @file
* @brief Logger��־�ӿ���.
* @author ruoxi
*
* ��������־�ӿ���.
*/

#ifndef __LOGGER_H__
#define __LOGGER_H__

class Logger
{
public:
    virtual void Log(LPCWSTR msg) = 0;
};

#endif // __LOGGER_H__
