/*
 * MATLAB Compiler: 4.9 (R2008b)
 * Date: Thu May 10 04:17:40 2012
 * Arguments: "-B" "macro_default" "-W" "lib:AddFunc" "-T" "link:lib" "AddFunc" 
 */

#ifndef __AddFunc_h
#define __AddFunc_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_AddFunc
#define PUBLIC_AddFunc_C_API __global
#else
#define PUBLIC_AddFunc_C_API /* No import statement needed. */
#endif

#define LIB_AddFunc_C_API PUBLIC_AddFunc_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_AddFunc
#define PUBLIC_AddFunc_C_API __declspec(dllexport)
#else
#define PUBLIC_AddFunc_C_API __declspec(dllimport)
#endif

#define LIB_AddFunc_C_API PUBLIC_AddFunc_C_API


#else

#define LIB_AddFunc_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_AddFunc_C_API 
#define LIB_AddFunc_C_API /* No special import/export declaration */
#endif

extern LIB_AddFunc_C_API 
bool MW_CALL_CONV AddFuncInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                mclOutputHandlerFcn print_handler);

extern LIB_AddFunc_C_API 
bool MW_CALL_CONV AddFuncInitialize(void);

extern LIB_AddFunc_C_API 
void MW_CALL_CONV AddFuncTerminate(void);



extern LIB_AddFunc_C_API 
void MW_CALL_CONV AddFuncPrintStackTrace(void);


extern LIB_AddFunc_C_API 
bool MW_CALL_CONV mlxAddFunc(int nlhs, mxArray *plhs[],
                             int nrhs, mxArray *prhs[]);

extern LIB_AddFunc_C_API 
long MW_CALL_CONV AddFuncGetMcrID() ;



extern LIB_AddFunc_C_API bool MW_CALL_CONV mlfAddFunc(int nargout, mxArray** f
                                                      , mxArray* a, mxArray* b);

#ifdef __cplusplus
}
#endif

#endif
