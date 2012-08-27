//
// MATLAB Compiler: 4.8 (R2008a)
// Date: Fri Jun 29 20:34:03 2012
// Arguments: "-B" "macro_default" "-W" "cpplib:transfer" "-T" "link:lib"
// "transfer" 
//

#ifndef __transfer_h
#define __transfer_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
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

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_transfer
#define PUBLIC_transfer_CPP_API __declspec(dllexport)
#else
#define PUBLIC_transfer_CPP_API __declspec(dllimport)
#endif

#define LIB_transfer_CPP_API PUBLIC_transfer_CPP_API

#else

#if !defined(LIB_transfer_CPP_API)
#if defined(LIB_transfer_C_API)
#define LIB_transfer_CPP_API LIB_transfer_C_API
#else
#define LIB_transfer_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_transfer_CPP_API void MW_CALL_CONV transfer(int nargout, mwArray& f1
                                                       , mwArray& f2
                                                       , mwArray& f3
                                                       , mwArray& f4
                                                       , mwArray& f5
                                                       , const mwArray& a
                                                       , const mwArray& b
                                                       , const mwArray& c1
                                                       , const mwArray& c2
                                                       , const mwArray& c3
                                                       , const mwArray& c4
                                                       , const mwArray& c5);

#endif

#endif
