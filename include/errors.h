/**
* @file
* @brief 包含所有错误代码的头文件.
* @author ruoxi
*
* 定义了所有的错误代码及对应消息.
*/

#ifndef __USE_ERRORS__
#error errors.h is wrongly included.
#endif // __USE_ERRORS__
#undef __USE_ERRORS__

DEFINE_ERROR(UNKNOWN_ERROR, "Unknown error occured.")
DEFINE_ERROR(FILE_OPEN_ERROR, "File open failed.")
DEFINE_ERROR(FILE_WRITE_ERROR, "File write failed.")
DEFINE_ERROR(WINSOCK_INIT_ERROR, "Winsock initialize failed.")
DEFINE_ERROR(WINSOCK_SHUT_ERROR, "Winsock cleanup failed.")
DEFINE_ERROR(SOCK_CREATE_ERROR, "Socket create failed.")
DEFINE_ERROR(SOCK_NODELAY_ERROR, "Socket set no delay failed.")
DEFINE_ERROR(SOCK_CLOSE_ERROR, "Socket close failed.")
DEFINE_ERROR(SOCK_BIND_ERROR, "Socket bind address and port failed.")
DEFINE_ERROR(SOCK_LISTEN_ERROR, "Socket listen failed.")
DEFINE_ERROR(SOCK_GETHOSTBYNAME_ERROR, "Socket get host by name failed.")
DEFINE_ERROR(SOCK_CONNECT_ERROR, "Socket connect failed.")
DEFINE_ERROR(SOCK_ACCEPT_ERROR, "Socket accept failed.")
DEFINE_ERROR(SOCK_RECV_ERROR, "Socket recieve data failed.")
DEFINE_ERROR(SOCK_SEND_ERROR, "Socket send data failed.")
DEFINE_ERROR(SOCK_SEND_FILE_ERROR, "Socket send file failed.")
DEFINE_ERROR(COMPONENT_GETINTERFACE_ERROR, "Component get interface error.")
DEFINE_ERROR(COMPONENT_GETATTRIBUTE_ERROR, "Component get attribute error.")
DEFINE_ERROR(COMPONENT_ATTRIBUTEUNSET_ERROR, "Component unset attribute error.")
DEFINE_ERROR(COMPONENT_SETATTRIBUTE_ERROR, "Component set attribute error.")

#ifdef __NETWORK_TEST__
DEFINE_ERROR(THREAD_CREATE_ERROR, "Create thread failed.")
#endif
