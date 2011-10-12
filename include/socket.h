/*
 * @file
 * @brief Socket接口类
 * @author ruoxi
 * @date
 * @version
 * @note
 * 定义了Socket的基本接口，包括初始化、关闭、收发特定类型的数据以及查询错误等功能
 */

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "rc.h"
#include <string>

using namespace std;

//--------------------------------------------------------------------
//! \brief Container for a series of actions
//!
//! This container holds a series of actions.  It's the PolicyManager
//! equivalent of a subroutine.  An action block get executed as the
//! result of a trigger.
//!
//! Every PmActionBlock should be owned by the PmEventManager, and
//! automatically gets deleted with the PmEventManager.
//!
class Socket
{
public:
    Socket();
    virtual ~Socket();

    static RC Init();
    static RC Shut();

    virtual RC Recv(void *buf, size_t size) = 0;
    virtual RC Send(const void *buf, size_t size) = 0;

    RC Recv08(UINT08 &data);
    RC Send08(UINT08 data);

    RC Recv16(UINT16 &data);
    RC Send16(UINT16 data);

    RC Recv32(UINT32 &data);
    RC Send32(UINT32 data);

    RC Recv64(UINT64 &data);
    RC Send64(UINT64 data);

    RC RecvDouble(double &data);
    RC SendDouble(double data);

    RC RecvString(string &str);
    RC SendString(const char *str);

    static int GetLastError();
};

#endif // __SOCKET_H__
