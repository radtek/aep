#ifndef __USE_ERRORS__
#error errors.h is wrongly included.
#endif // __USE_ERRORS__
#undef __USE_ERRORS__

DEFINE_ERROR(UNKNOWN_ERROR, "Unknown error occured.")
DEFINE_ERROR(RECV_ERROR, "Recieve data failed.")
DEFINE_ERROR(SEND_ERROR, "Send data failed.")
DEFINE_ERROR(WINSOCK_INIT_ERROR, "Winsock initialize failed.")
DEFINE_ERROR(WINSOCK_SHUT_ERROR, "Winsock cleanup failed.")
