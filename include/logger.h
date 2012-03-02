/**
* @file
* @brief Logger日志接口类.
* @author ruoxi
*
* 定义了日志接口类.
*/

#ifndef __LOGGER_H__
#define __LOGGER_H__

class Logger
{
public:
    virtual void Log(LPCWSTR msg) = 0;
};

#endif // __LOGGER_H__
