/*
 * MATLAB Compiler: 4.9 (R2008b)
 * Date: Sat Jun 30 00:13:07 2012
 * Arguments: "-B" "macro_default" "-T" "link:lib" "-W" "lib:median_filter"
 * "median_filter" 
 */

#ifndef __median_filter_h
#define __median_filter_h 1

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

#ifdef EXPORTING_median_filter
#define PUBLIC_median_filter_C_API __global
#else
#define PUBLIC_median_filter_C_API /* No import statement needed. */
#endif

#define LIB_median_filter_C_API PUBLIC_median_filter_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_median_filter
#define PUBLIC_median_filter_C_API __declspec(dllexport)
#else
#define PUBLIC_median_filter_C_API __declspec(dllimport)
#endif

#define LIB_median_filter_C_API PUBLIC_median_filter_C_API


#else

#define LIB_median_filter_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_median_filter_C_API 
#define LIB_median_filter_C_API /* No special import/export declaration */
#endif

extern LIB_median_filter_C_API 
bool MW_CALL_CONV median_filterInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                      mclOutputHandlerFcn print_handler);

extern LIB_median_filter_C_API 
bool MW_CALL_CONV median_filterInitialize(void);

extern LIB_median_filter_C_API 
void MW_CALL_CONV median_filterTerminate(void);



extern LIB_median_filter_C_API 
void MW_CALL_CONV median_filterPrintStackTrace(void);


extern LIB_median_filter_C_API 
bool MW_CALL_CONV mlxMedian_filter(int nlhs, mxArray *plhs[],
                                   int nrhs, mxArray *prhs[]);

extern LIB_median_filter_C_API 
long MW_CALL_CONV median_filterGetMcrID() ;



extern LIB_median_filter_C_API bool MW_CALL_CONV mlfMedian_filter(int nargout
                                                                  , mxArray** MF
                                                                  , mxArray** f2
                                                                  , mxArray** f3
                                                                  , mxArray** f4
                                                                  , mxArray** f5
                                                                  , mxArray* a
                                                                  , mxArray* I
                                                                  , mxArray* filterh
                                                                  , mxArray* filterw
                                                                  , mxArray* c3
                                                                  , mxArray* c4
                                                                  , mxArray* c5);

#ifdef __cplusplus
}
#endif

#endif
