/*
 * MATLAB Compiler: 4.9 (R2008b)
 * Date: Mon Aug 27 23:51:19 2012
 * Arguments: "-B" "macro_default" "-T" "link:lib" "-W" "lib:transfer"
 * "transfer" 
 */

#ifndef __transfer_h
#define __transfer_h 1

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

#ifdef EXPORTING_transfer
#define PUBLIC_transfer_C_API __global
#else
#define PUBLIC_transfer_C_API /* No import statement needed. */
#endif

#define LIB_transfer_C_API PUBLIC_transfer_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_transfer
#define PUBLIC_transfer_C_API __declspec(dllexport)
#else
#define PUBLIC_transfer_C_API __declspec(dllimport)
#endif

#define LIB_transfer_C_API PUBLIC_transfer_C_API


#else

#define LIB_transfer_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_transfer_C_API 
#define LIB_transfer_C_API /* No special import/export declaration */
#endif

extern LIB_transfer_C_API 
bool MW_CALL_CONV transferInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                 mclOutputHandlerFcn print_handler);

extern LIB_transfer_C_API 
bool MW_CALL_CONV transferInitialize(void);

extern LIB_transfer_C_API 
void MW_CALL_CONV transferTerminate(void);



extern LIB_transfer_C_API 
void MW_CALL_CONV transferPrintStackTrace(void);


extern LIB_transfer_C_API 
bool MW_CALL_CONV mlxTransfer(int nlhs, mxArray *plhs[],
                              int nrhs, mxArray *prhs[]);

extern LIB_transfer_C_API 
long MW_CALL_CONV transferGetMcrID() ;



extern LIB_transfer_C_API bool MW_CALL_CONV mlfTransfer(int nargout
                                                        , mxArray** f1
                                                        , mxArray** f2
                                                        , mxArray** f3
                                                        , mxArray** f4
                                                        , mxArray** f5
                                                        , mxArray* a, mxArray* b
                                                        , mxArray* c1
                                                        , mxArray* c2
                                                        , mxArray* c3
                                                        , mxArray* c4
                                                        , mxArray* c5);

#ifdef __cplusplus
}
#endif

#endif
