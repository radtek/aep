/**
* @file
* @brief ��������ͨ�������ͷ�ļ�.
* @author ruoxi
*
* ���������е�ͨ�������Ӧ����.
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
