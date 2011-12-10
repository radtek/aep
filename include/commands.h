/**
* @file
* @brief 包含所有通信命令的头文件.
* @author ruoxi
*
* 定义了所有的通信命令及对应含义.
*/

#ifndef __USE_COMMANDS__
#error commands.h is wrongly included.
#endif // __USE_COMMANDS__
#undef __USE_COMMANDS__

DEFINE_COMMAND(UNKNOWN_COMMAND)
DEFINE_COMMAND(LOGIN_COMMAND)
DEFINE_COMMAND(REGISTER_COMMAND)
DEFINE_COMMAND(SEND_MODEL_FILE_COMMAND)
DEFINE_COMMAND(EXIT_COMMAND)
