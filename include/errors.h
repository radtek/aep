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
DEFINE_ERROR(FILE_DELETE_ERROR, "File delete failed.")
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
DEFINE_ERROR(COMPONENT_GETINTERFACE_ERROR, "Component get interface failed.")
DEFINE_ERROR(COMPONENT_GETATTRIBUTE_ERROR, "Component get attribute failed.")
DEFINE_ERROR(COMPONENT_ATTRIBUTEUNSET_ERROR, "Component unset attribute failed.")
DEFINE_ERROR(COMPONENT_SETATTRIBUTE_ERROR, "Component set attribute failed.")
DEFINE_ERROR(PLATFORM_LOADDLL_ERROR, "Platform load dll failed.")
DEFINE_ERROR(PLATFORM_REGISTERCOMPONENTINFO_ERROR, "Platform register component failed.")
DEFINE_ERROR(PLATFORM_REGISTERINTERFACEINFO_ERROR, "Platform register interface failed.")
DEFINE_ERROR(PLATFORM_REGISTERALGORITHM_ERROR, "Platform register algorithm failed.")
DEFINE_ERROR(PLATFORM_REGISTERGETCOMPONENTLISTFUNC_ERROR, "Platform register GetComponentList function failed.")
DEFINE_ERROR(PLATFORM_VALIDATEMODEL_ERROR, "Platform validate model failed.")
DEFINE_ERROR(PLATFORM_RUNMODEL_ERROR, "Platform run model failed.")
DEFINE_ERROR(PLATFORM_UNLOADDLL_ERROR, "Platform unload dll failed.")
DEFINE_ERROR(ALGORITHM_INIT_ERROR, "Algorithm initialize failed.")
DEFINE_ERROR(ALGORITHM_SHUT_ERROR, "Algorithm shut dll failed.")
DEFINE_ERROR(ALGORITHM_LOADDLL_ERROR, "Algorithm load dll failed.")
DEFINE_ERROR(ALGORITHM_UNLOADDLL_ERROR, "Algorithm unload dll failed.")
DEFINE_ERROR(ALGORITHM_GETPROC_ERROR, "Algorithm get proc failed.")
DEFINE_ERROR(ALGORITHM_RUN_INITIALIZE_ERROR, "Algorithm run initialize failed.")
DEFINE_ERROR(ALGORITHM_RUN_ERROR, "Algorithm run failed.")
DEFINE_ERROR(ALGORITHM_GETPARAMLIST_ERROR, "Algorithm get param list failed.")
DEFINE_ERROR(ALGORITHM_OVERMAXINPUTNUM_ERROR, "Input number exceeded the max value.")
DEFINE_ERROR(ALGORITHM_OVERMAXOUTPUTNUM_ERROR, "Output number exceeded the max value.")
DEFINE_ERROR(ALGORITHM_PARAMMISSING_ERROR, "Some parameter missed for an algorithm.")
DEFINE_ERROR(ALGORITHM_INSERT_ERROR, "Algorithm insert failed.")
DEFINE_ERROR(ALGORITHM_REMOVE_ERROR, "Algorithm remove failed.")

DEFINE_ERROR(ALGORITHM_INPUT_ERROR, "Algorithm input error.")

DEFINE_ERROR(THREAD_CREATE_ERROR, "Create thread failed.")

DEFINE_ERROR(USER_EXISTED_ERROR, "User already existed.")
DEFINE_ERROR(USER_BAD_NAME_ERROR, "Invalid user name.")
DEFINE_ERROR(USER_BAD_PASSWORD_ERROR, "Invalid user password.")
DEFINE_ERROR(USER_UNEXISTS_USER_ERROR, "User unexistes.")
DEFINE_ERROR(USER_WRONG_PASSWORD_ERROR, "Wrong password.")

DEFINE_ERROR(LOGIN_ALREADY_LOGIN_ERROR, "Already login.")

DEFINE_ERROR(DOC_EXPORT_MODEL_CONNECTOR_ERROR, "Connection error.")
DEFINE_ERROR(MODEL_LOAD_COMPONENT_ERROR, "Load component error.")
DEFINE_ERROR(MODEL_CONNECT_COMPONENT_ERROR, "Connect component error.")
DEFINE_ERROR(MODEL_MATLAB_ENGINE_ERROR, "Matlab engine error.")
DEFINE_ERROR(MODEL_NO_PARAM_ERROR, "No param component.")

DEFINE_ERROR(MODEL_GET_ENTRY_ALGORITHM_ERROR, "No entry algorithm.")
DEFINE_ERROR(MODEL_NO_ENTRANCE_ALGORITHM_ERROR, "No entrance algorithm.")
DEFINE_ERROR(MODEL_MULTI_ENTRANCE_ALGORITHM_ERROR, "Multi entrance algorithm.")
DEFINE_ERROR(MODEL_MULTI_NEXT_ALGORITHM_ERROR, "Multi next algorithm.")
DEFINE_ERROR(MODEL_ALGORITHM_INPUT_ERROR, "Invalid algorithm input.")
DEFINE_ERROR(MODEL_ALGORITHM_OUTPUT_ERROR, "Invalid algorithm output.")

DEFINE_ERROR(COMPONENT_SETINPUT_ERROR, "Set component input error.")
DEFINE_ERROR(COMPONENT_GETOUTPUT_ERROR, "Get component output error.")

DEFINE_ERROR(DOWNLOAD_UNEXISTEFD_FILE_ERROR, "File unexists.")

DEFINE_ERROR(BATCH_PARSE_FILE_ERROR, "Invalid batch file format.")
DEFINE_ERROR(BATCH_CONFIG_MODEL_ERROR, "Couldn't find component in model.")
DEFINE_ERROR(BATCH_CONFIG_COMPONENT_ERROR, "Couldn't find attribute in component.")

DEFINE_ERROR(UTILITY_SAVE_IMAGE_ERROR, "Save image error.")

DEFINE_ERROR(FILE_DIRECTORY_NOT_EXIST, "Directory not exists.")
