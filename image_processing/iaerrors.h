/**
* @file
* @brief �������д�������ͷ�ļ�.
* @author ruoxi
*
* ���������еĴ�����뼰��Ӧ��Ϣ.
*/

#ifndef __USE_IAERRORS__
#error iaerrors.h is wrongly included.
#endif // __USE_IAERRORS__
#undef __USE_IAERRORS__

DEFINE_IAERROR(UNKNOWN_ERROR, "Unknown error occured.")
DEFINE_IAERROR(ALGORITHM_INPUT_ERROR, "Algorithm input error.")
