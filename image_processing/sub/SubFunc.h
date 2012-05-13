/*
 * MATLAB Compiler: 4.9 (R2008b)
 * Date: Sat May 12 01:37:12 2012
 * Arguments: "-B" "macro_default" "-T" "link:lib" "-W" "lib:SubFunc" "SubFunc" 
 */

#ifndef __SubFunc_h
#define __SubFunc_h 1

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

#ifdef EXPORTING_SubFunc
#define PUBLIC_SubFunc_C_API __global
#else
#define PUBLIC_SubFunc_C_API /* No import statement needed. */
#endif

#define LIB_SubFunc_C_API PUBLIC_SubFunc_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_SubFunc
#define PUBLIC_SubFunc_C_API __declspec(dllexport)
#else
#define PUBLIC_SubFunc_C_API __declspec(dllimport)
#endif

#define LIB_SubFunc_C_API PUBLIC_SubFunc_C_API


#else

#define LIB_SubFunc_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_SubFunc_C_API 
#define LIB_SubFunc_C_API /* No special import/export declaration */
#endif

extern LIB_SubFunc_C_API 
bool MW_CALL_CONV SubFuncInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                mclOutputHandlerFcn print_handler);

extern LIB_SubFunc_C_API 
bool MW_CALL_CONV SubFuncInitialize(void);

extern LIB_SubFunc_C_API 
void MW_CALL_CONV SubFuncTerminate(void);



extern LIB_SubFunc_C_API 
void MW_CALL_CONV SubFuncPrintStackTrace(void);


extern LIB_SubFunc_C_API 
bool MW_CALL_CONV mlxSubFunc(int nlhs, mxArray *plhs[],
                             int nrhs, mxArray *prhs[]);

extern LIB_SubFunc_C_API 
long MW_CALL_CONV SubFuncGetMcrID() ;



extern LIB_SubFunc_C_API bool MW_CALL_CONV mlfSubFunc(int nargout, mxArray** f
                                                      , mxArray* a, mxArray* b
                                                      , mxArray* c);

#ifdef __cplusplus
}
#endif

#endif
