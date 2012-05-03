/**
* @file
* @brief 包含所有错误代码的头文件.
* @author ruoxi
*
* 定义了所有的错误代码及对应消息.
*/

#ifndef __USE_IAERRORS__
#error iaerrors.h is wrongly included.
#endif // __USE_IAERRORS__
#undef __USE_IAERRORS__

DEFINE_IAERROR(UNKNOWN_ERROR, "Unknown error occured.")
DEFINE_IAERROR(ALGORITHM_INPUT_ERROR, "Algorithm input error.")
