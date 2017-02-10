/****************************************************************************
*           CTC++, Test Coverage Analyzer for C/C++, Version 8.1            *
*                                                                           *
*                                   CTC.H                                   *
*           (header file for the instrumented file compilations)            *
*                                                                           *
*                    Copyright (c) 1993-2013 Testwell Oy                    *
*             Copyright (c) 2013-2016 Verifysoft Technology GmbH            *
****************************************************************************/

#ifndef CTC_H
#define CTC_H

/*
Uncomment the following macro definition, if you want that counter
incrementation is done by the CTC++ run-time library functions. The
functions also check for counter overflows. This doesn't affect the
counters of CTC_TIMING.

Alternatively, you can define CTC_SAFE on the command line when
instrumenting and compiling the source file(s).
*/
/*
#define CTC_SAFE
*/

/*
Uncomment the following macro definition, if you want that the
instrumentation of case and default labels in a switch statement
is done in a less strict way, where "falling through" from the
previous case/default label is considered acceptable to cause
an execution hit.

Alternatively, you can define CTC_CASE_FALL_THROUGH_LOOSE on the
command line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_CASE_FALL_THROUGH_LOOSE
*/

/*
Uncomment the following macro definition, if you want that the
instrumentation of the conditional operator (? :) is not done.

Alternatively, you can define CTC_COND_OPER_NO_INSTR on the
command line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_COND_OPER_NO_INSTR
*/

/*
Uncomment the following macro definition, if you want that the
instrumentation of declarations in conditions is not done.

Alternatively, you can define CTC_DECL_COND_NO_INSTR on the
command line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_DECL_COND_NO_INSTR
*/

/*
Uncomment the following macro definition, if you want that
multicondition coverage instrumentation for C++ source files is
done in the same way as for C files.

Alternatively, you can define CTC_CLIKE_MCOND on the command
line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_CLIKE_MCOND
*/

/*
Uncomment the following macro definition, if you want that the
timing instrumentation for C++ source files is done in the same
way as for C files.

Alternatively, you can define CTC_CLIKE_TIMING on the command
line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_CLIKE_TIMING
*/

/*
Uncomment the following macro definition, if you want to use a
C++ function as the execution cost measurement function. By
default, clock() or some other C function is used.

Alternatively, you can define CTC_CPP_TIMER_FUNC on the command
line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_CPP_TIMER_FUNC
*/

/*
Uncomment the following macro definition, if you want an RCS
version control stamp to be added to the instrumented file.

Alternatively, you can define CTC_EMIT_RCS_STAMP on the command
line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_EMIT_RCS_STAMP
*/

/*
Uncomment the following macro definition, if you want an SCCS
version control stamp to be added to the instrumented file.

Alternatively, you can define CTC_EMIT_SCCS_STAMP on the command
line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_EMIT_SCCS_STAMP
*/

/*
Uncomment the following macro definition, if you want that the
execution counters are always allocated from the heap.

Alternatively, you can define CTC_HEAP_COUNTERS on the command
line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_HEAP_COUNTERS
*/

/*
Uncomment the following macro definition, if you want that the
function ctc_append_trigger() is called. The aim of this function
is to launch an 'appender' thread that will write coverage data
repeatedly out.

Alternatively, you can define CTC_LAUNCH_APPENDER on the command
line when instrumenting and compiling the source file(s).
*/
/*
#define CTC_LAUNCH_APPENDER
*/

/*
By default, the execution cost measurement function is the C library
function clock() from <time.h>. If you are using any other cost
function, for example, some function of your own, you may need to
redefine the following macros CTC_TIMER_IMPORT and CTC_TIMER_API.

Note for MSVC++ users: the macros are defined here in such a way
that the clock function may either reside in a DLL or come from
a static-link library.
*/

#if !defined(CTC_TIMER_IMPORT)
#  if defined(_WIN32) && defined(_DLL)
#    define CTC_TIMER_IMPORT __declspec(dllimport)
#  else
#    define CTC_TIMER_IMPORT
#  endif
#endif

/*
On Windows, the default for CTC_TIMER_API, __cdecl is a valid
calling convention for the default cost measurement function clock(),
and also for any other function using the default __cdecl calling
convention. You need to define CTC_TIMER_API only in case your cost
measurement function uses __stdcall or __fastcall or some other
calling convention.
*/

#if !defined(CTC_TIMER_API)
#  if defined(_WIN32)
#    define CTC_TIMER_API __cdecl
#  else
#    define CTC_TIMER_API
#  endif
#endif

/*
By default, the execution cost measurement (timer) function
is declared as having "C" linkage.
*/

#if !defined(CTC_TIMER_EXTERN)
#  if defined(__cplusplus) && !defined(CTC_CPP_TIMER_FUNC)
#    define CTC_TIMER_EXTERN extern "C"
#  else
#    define CTC_TIMER_EXTERN
#  endif
#endif

/*
Exception specification for the execution cost measurement
(timer) function
*/

#if !defined(CTC_TIMER_THROW)
#  if defined(__cplusplus) && \
      (defined(__linux) || defined(__linux__))
#    define CTC_TIMER_THROW throw()
#  else
#    define CTC_TIMER_THROW
#  endif
#endif

/*
By default, the function ctc_append_trigger() is not called.
*/

#if !defined(CTC_APPEND_TRIGGER)
#  if defined(CTC_LAUNCH_APPENDER)
#    define CTC_APPEND_TRIGGER ctc_append_trigger();
#    ifdef __cplusplus
     extern "C"
#    endif
     void CTC_APPEND_TRIGGER
#  else
#    define CTC_APPEND_TRIGGER
#  endif
#else
#  ifdef __cplusplus
   extern "C"
#  endif
   void CTC_APPEND_TRIGGER
#endif

/*
   CTC_CWRAP_START/END: extern "C" wrappers for C++ compilation
*/

#if !defined(CTC_CWRAP_START)
#  ifdef __cplusplus
#    define CTC_CWRAP_START extern "C" {
#  else
#    define CTC_CWRAP_START
#  endif
#endif
#if !defined(CTC_CWRAP_END)
#  ifdef __cplusplus
#    define CTC_CWRAP_END   }
#  else
#    define CTC_CWRAP_END
#  endif
#endif


CTC_CWRAP_START


/*************************************************************************
   Type definitions
   - CTC_COUNTER: type of the counter value
   - CTC_TIMER: type of the timer value
   - CTC_MODULE_INFO: type of the module information structure
**************************************************************************/

#if !defined(CTC_COUNTER)
typedef unsigned long CTC_COUNTER;
#endif

#if !defined(CTC_TIMER)
#  if defined(__HP_aCC) || defined(__HP_cc) || \
      defined(__hpux) || defined(__hpux__)
   /* HPUX aC++/cc/g++/gcc */
typedef unsigned int CTC_TIMER;
#  else
typedef long CTC_TIMER;
#  endif
#endif

typedef struct CTC_MODULE_INFO {
    /* Path of the source file */
    const char *source_path;

    /* Path of the datafile (usually absolute) */
    const char *dat_file;

    /* Time of the instrumentation */
    long time_stamp;

    /* Rewrite count and update count of module data */
    unsigned int rewrite_count;
    unsigned int update_count;

    /* Number of function, jump, true/false, multicondition and
       timer/maxtimer counters */
    unsigned long num_s, num_j, num_tf, num_c, num_time;

    /* Pointers to counter arrays (function, jump, true, false,
       multicondition, timer, and max timer) */
    CTC_COUNTER *ctc_s, *ctc_j, *ctc_t, *ctc_f, *ctc_c;
    CTC_TIMER   *ctc_time, *ctc_maxtime;

    /* Pointer to the next registered module */
    struct CTC_MODULE_INFO* next;
} CTC_MODULE_INFO;


/* Environment-specific declarations */

#if !defined(CTCIMPORT)
#  define CTCIMPORT extern
#endif

#if !defined(CTCAPI)
#  if defined(_WIN32) || defined(__CYGWIN32__) || defined(__MINGW32__)
#    define CTCAPI __cdecl
#  else
#    define CTCAPI
#  endif
#endif

#if !defined(CTCEXTERN)
#  if defined(_WIN32) || defined(__CYGWIN32__) || defined(__MINGW32__)
#    define CTCEXTERN __declspec(dllimport)
#  else
#    define CTCEXTERN extern
#  endif
#endif

#if !defined(CTCIMPORTVAR)
#  define CTCIMPORTVAR
#endif


/* The global variable declarations */

#if defined(CTC_TIMING) && defined(CTC_EXCLUSIVE_TIMING)
CTCEXTERN CTC_TIMER  CTCIMPORTVAR ctc_curf_start;
CTCEXTERN CTC_TIMER* CTCIMPORTVAR ctc_curf_tp;
CTCEXTERN CTC_TIMER  CTCIMPORTVAR ctc_curf_elapsed;
CTCEXTERN CTC_TIMER* CTCIMPORTVAR ctc_curf_maxtp;
#endif

/*
Declaration of version control stamps
(argument 'src' is the source file string)
*/

#ifdef CTC_EMIT_RCS_STAMP
#  define CTC_RCS_STAMP(src) \
     static const char* ctc_rcs_stamp = "\44Id: Instrumented " src " \44";
#else
#  define CTC_RCS_STAMP(src)
#endif

#ifdef CTC_EMIT_SCCS_STAMP
#  define CTC_SCCS_STAMP(src) \
     static const char* ctc_sccs_stamp = "\100(\43) Instrumented " src;
#else
#  define CTC_SCCS_STAMP(src)
#endif


/* Declaration of library functions */

CTCIMPORT void CTCAPI ctc_register_module(CTC_MODULE_INFO*);

CTCIMPORT void CTCAPI ctc_register_module2(const char*,   const char*,
                                           long,
                                           unsigned long, unsigned long,
                                           unsigned long, unsigned long,
                                           unsigned long,
                                           CTC_COUNTER**, CTC_COUNTER**,
                                           CTC_COUNTER**, CTC_COUNTER**,
                                           CTC_COUNTER**,
                                           CTC_TIMER**,   CTC_TIMER**);

CTCIMPORT void CTCAPI ctc_init(void);

CTCIMPORT void CTCAPI ctc_quit(void);

CTCIMPORT void CTCAPI ctc_inc(CTC_COUNTER*);

CTCIMPORT void CTCAPI ctc_dec(CTC_COUNTER*);

CTCIMPORT int  CTCAPI ctc_condition(CTC_COUNTER*, CTC_COUNTER*,
                                    unsigned, int);

CTCIMPORT void CTCAPI ctc_append_all(void);

CTCIMPORT void CTCAPI ctc_set_testcase(const char*);

CTC_CWRAP_END


/* Instrumentation macros */

/**************************************************************************
   MACRO       : CTC_MODULE_HEAD
   PURPOSE     : Inserted at the beginning of the module
   DESCRIPTION : Declares the pointers which will be used as counter
                 arrays. Also declares the module initializer function.
   ARGUMENTS   : - timer_func: name of the execution cost measurement
                               (timer) function
**************************************************************************/

#ifdef CTC_TIMING
#  if defined(__cplusplus) && !defined(CTC_CLIKE_TIMING)
#    ifdef CTC_INCLUSIVE_TIMING
#      define CTC_MODULE_HEAD(timer_func)                         \
CTC_TIMER_EXTERN CTC_TIMER_IMPORT CTC_TIMER CTC_TIMER_API         \
   timer_func(void) CTC_TIMER_THROW;                              \
CTC_CWRAP_START                                                   \
static CTC_COUNTER *ctc_s = 0;                                    \
static CTC_COUNTER *ctc_j = 0;                                    \
static CTC_COUNTER *ctc_t = 0;                                    \
static CTC_COUNTER *ctc_f = 0;                                    \
static CTC_COUNTER *ctc_c = 0;                                    \
static CTC_TIMER   *ctc_time = 0;                                 \
static CTC_TIMER   *ctc_maxtime = 0;                              \
static CTC_TIMER (CTC_TIMER_API *ctc_timer)(void) = timer_func;   \
static void ctc_module_init(void);                                \
CTC_CWRAP_END                                                     \
class Ctc_timer_class {                                           \
public:                                                           \
   Ctc_timer_class() {                                            \
      ctc_start_temp = ctc_timer();                               \
   }                                                              \
   void set_timer(CTC_TIMER* tp, CTC_TIMER* maxtp) {              \
      ctc_time_ptr = tp;                                          \
      ctc_maxtime_ptr = maxtp;                                    \
   }                                                              \
   ~Ctc_timer_class() {                                           \
      ctc_elapsed_temp = ctc_timer() - ctc_start_temp;            \
      *ctc_time_ptr += ctc_elapsed_temp;                          \
      if (ctc_elapsed_temp > *ctc_maxtime_ptr)                    \
         *ctc_maxtime_ptr = ctc_elapsed_temp;                     \
   }                                                              \
private:                                                          \
   CTC_TIMER  ctc_start_temp;                                     \
   CTC_TIMER* ctc_time_ptr;                                       \
   CTC_TIMER* ctc_maxtime_ptr;                                    \
   CTC_TIMER  ctc_elapsed_temp;                                   \
};

#    else /* !defined(CTC_INCLUSIVE_TIMING) */
#      define CTC_MODULE_HEAD(timer_func)                         \
CTC_TIMER_EXTERN CTC_TIMER_IMPORT CTC_TIMER CTC_TIMER_API         \
   timer_func(void) CTC_TIMER_THROW;                              \
CTC_CWRAP_START                                                   \
static CTC_COUNTER *ctc_s = 0;                                    \
static CTC_COUNTER *ctc_j = 0;                                    \
static CTC_COUNTER *ctc_t = 0;                                    \
static CTC_COUNTER *ctc_f = 0;                                    \
static CTC_COUNTER *ctc_c = 0;                                    \
static CTC_TIMER   *ctc_time = 0;                                 \
static CTC_TIMER   *ctc_maxtime = 0;                              \
static CTC_TIMER (CTC_TIMER_API *ctc_timer)(void) = timer_func;   \
static void ctc_module_init(void);                                \
CTC_CWRAP_END                                                     \
class Ctc_timer_class {                                           \
public:                                                           \
   Ctc_timer_class() {                                            \
      ctc_start_temp = ctc_timer();                               \
      ctc_prev_tp = ctc_curf_tp;                                  \
      ctc_prev_maxtp = ctc_curf_maxtp;                            \
      *ctc_prev_tp += ctc_start_temp - ctc_curf_start;            \
      ctc_prev_elapsed =                                          \
         ctc_curf_elapsed + (ctc_start_temp - ctc_curf_start);    \
      ctc_curf_start = ctc_start_temp;                            \
      ctc_curf_elapsed = 0;                                       \
   }                                                              \
   void set_timer(CTC_TIMER* tp, CTC_TIMER* maxtp) {              \
      ctc_curf_tp = tp;                                           \
      ctc_curf_maxtp = maxtp;                                     \
   }                                                              \
   ~Ctc_timer_class() {                                           \
      ctc_start_temp = ctc_timer();                               \
      *ctc_curf_tp += ctc_start_temp - ctc_curf_start;            \
      ctc_curf_elapsed += ctc_start_temp - ctc_curf_start;        \
      if (ctc_curf_elapsed > *ctc_curf_maxtp)                     \
         *ctc_curf_maxtp = ctc_curf_elapsed;                      \
      ctc_curf_start = ctc_start_temp;                            \
      ctc_curf_tp = ctc_prev_tp;                                  \
      ctc_curf_maxtp = ctc_prev_maxtp;                            \
      ctc_curf_elapsed = ctc_prev_elapsed;                        \
   }                                                              \
private:                                                          \
   CTC_TIMER* ctc_prev_tp;                                        \
   CTC_TIMER* ctc_prev_maxtp;                                     \
   CTC_TIMER  ctc_start_temp;                                     \
   CTC_TIMER  ctc_prev_elapsed;                                   \
};
#    endif /* CTC_INCLUSIVE_TIMING */

#  else /* !defined(__cplusplus) || defined(CTC_CLIKE_TIMING) */
#    define CTC_MODULE_HEAD(timer_func)                           \
CTC_TIMER_EXTERN CTC_TIMER_IMPORT CTC_TIMER CTC_TIMER_API         \
   timer_func(void) CTC_TIMER_THROW;                              \
CTC_CWRAP_START                                                   \
static CTC_COUNTER *ctc_s = 0;                                    \
static CTC_COUNTER *ctc_j = 0;                                    \
static CTC_COUNTER *ctc_t = 0;                                    \
static CTC_COUNTER *ctc_f = 0;                                    \
static CTC_COUNTER *ctc_c = 0;                                    \
static CTC_TIMER   *ctc_time = 0;                                 \
static CTC_TIMER   *ctc_maxtime = 0;                              \
static CTC_TIMER (CTC_TIMER_API *ctc_timer)(void) = timer_func;   \
static void ctc_module_init(void);                                \
CTC_CWRAP_END
#  endif /* __cplusplus */

#else /* !defined(CTC_TIMING) */
#  define CTC_MODULE_HEAD(timer_func)                             \
CTC_CWRAP_START                                                   \
static CTC_COUNTER *ctc_s = 0;                                    \
static CTC_COUNTER *ctc_j = 0;                                    \
static CTC_COUNTER *ctc_t = 0;                                    \
static CTC_COUNTER *ctc_f = 0;                                    \
static CTC_COUNTER *ctc_c = 0;                                    \
static CTC_TIMER   *ctc_time = 0;                                 \
static CTC_TIMER   *ctc_maxtime = 0;                              \
static void ctc_module_init(void);                                \
CTC_CWRAP_END
#endif /* CTC_TIMING */


/**************************************************************************
   MACRO       : CTC_MODULE_TAIL
   PURPOSE     : Inserted at the end of the module
   DESCRIPTION : Defines the counter arrays, module information struct and
                 module initializer function for the current module.
   ARGUMENTS   : - src: source file string
                 - datfile: datafile name (full path)
                 - timestamp: time of the instrumentation
                 - s: number of function counters
                 - j: number of jump counters
                 - tf: number of true/false counters
                 - c: number of multicondition counters
                 - time: number of timer/maxtimer counters
**************************************************************************/

#if !defined(CTC_HEAP_COUNTERS)
#  define CTC_MODULE_TAIL(src, datfile, timestamp,                \
                          s, j, tf, c, time)                      \
CTC_CWRAP_START                                                   \
static CTC_COUNTER ctc_s_t[s + 1];                                \
static CTC_COUNTER ctc_j_t[j + 1];                                \
static CTC_COUNTER ctc_t_t[tf + 1];                               \
static CTC_COUNTER ctc_f_t[tf + 1];                               \
static CTC_COUNTER ctc_c_t[c + 1];                                \
static CTC_TIMER   ctc_time_t[time + 1];                          \
static CTC_TIMER   ctc_maxtime_t[time + 1];                       \
static CTC_MODULE_INFO ctc_module_info;                           \
static void ctc_module_init(void) {                               \
    ctc_module_info.source_path = src;                            \
    ctc_module_info.dat_file = datfile;                           \
    ctc_module_info.time_stamp = timestamp;                       \
    ctc_module_info.rewrite_count = 0;                            \
    ctc_module_info.update_count = 0;                             \
    ctc_module_info.num_s = s;                                    \
    ctc_module_info.num_j = j;                                    \
    ctc_module_info.num_tf = tf;                                  \
    ctc_module_info.num_c = c;                                    \
    ctc_module_info.num_time = time;                              \
    ctc_module_info.ctc_s = ctc_s_t;                              \
    ctc_module_info.ctc_j = ctc_j_t;                              \
    ctc_module_info.ctc_t = ctc_t_t;                              \
    ctc_module_info.ctc_f = ctc_f_t;                              \
    ctc_module_info.ctc_c = ctc_c_t;                              \
    ctc_module_info.ctc_time = ctc_time_t;                        \
    ctc_module_info.ctc_maxtime = ctc_maxtime_t;                  \
    ctc_module_info.next = 0;                                     \
    ctc_register_module(&ctc_module_info);                        \
    ctc_s = ctc_s_t;                                              \
    ctc_j = ctc_j_t;                                              \
    ctc_t = ctc_t_t;                                              \
    ctc_f = ctc_f_t;                                              \
    ctc_c = ctc_c_t;                                              \
    ctc_time = ctc_time_t;                                        \
    ctc_maxtime = ctc_maxtime_t;                                  \
    CTC_APPEND_TRIGGER                                            \
}                                                                 \
CTC_RCS_STAMP(src)                                                \
CTC_SCCS_STAMP(src)                                               \
CTC_CWRAP_END

#else /* defined(CTC_HEAP_COUNTERS) */
#  define CTC_MODULE_TAIL(src, datfile, timestamp,                \
                          s, j, tf, c, time)                      \
CTC_CWRAP_START                                                   \
static void ctc_module_init(void) {                               \
    ctc_register_module2(src, datfile, timestamp, s, j, tf, c,    \
                         time, &ctc_s, &ctc_j, &ctc_t, &ctc_f,    \
                         &ctc_c, &ctc_time, &ctc_maxtime);        \
    CTC_APPEND_TRIGGER                                            \
}                                                                 \
CTC_RCS_STAMP(src)                                                \
CTC_SCCS_STAMP(src)                                               \
CTC_CWRAP_END
#endif /* CTC_HEAP_COUNTERS */


/**************************************************************************
   MACRO       : CTC_FSTART
   PURPOSE     : Inserted at the start of function
   ARGUMENTS   : - name: string literal, name of the function
                 - findex: function counter index, and also timer index
                           in case of timing instrumentation
**************************************************************************/

#define CTC_FSTART(name, findex) \
   CTC_TIMER_TMP CTC_INIT CTC_IS(findex) CTC_START(findex) {


/**************************************************************************
   MACRO       : CTC_FEND
   PURPOSE     : Inserted at the end of function, if the end is reachable
   ARGUMENTS   : - name: string literal, name of the function
                 - eindex: jump index of the function end (meaningless
                           if only function coverage)
                 - tindex: timer index (when timing-instrumented, same as
                           function counter index; otherwise meaningless)
**************************************************************************/

#define CTC_FEND(name, eindex, tindex) \
   CTC_STOP(tindex) CTC_IE(eindex) }


/**************************************************************************
   MACRO       : CTC_FEND_MAIN
   PURPOSE     : Inserted at the end of "main" function (function whose
                 name matches any of the values in the EMBED_FUNCTION_NAME
                 configuration parameter), if the end is reachable
   ARGUMENTS   : - name: string literal, name of the function
                 - eindex: jump index of the function end (meaningless
                           if only function coverage)
                 - tindex: timer index (when timing-instrumented, same as
                           function counter index; otherwise meaningless)
**************************************************************************/

#define CTC_FEND_MAIN(name, eindex, tindex) \
   CTC_STOP(tindex) CTC_IE(eindex) ctc_append_all(); }


/**************************************************************************
   MACRO       : CTC_FEND_NR
   PURPOSE     : Inserted at the end of function if the end is Not Reachable
   ARGUMENTS   : None
**************************************************************************/

#define CTC_FEND_NR }


/**************************************************************************
   MACRO       : CTC_MAIN_START/END
   PURPOSE     : Inserted around return or throw in "main" function
                 (function whose name matches any of the values in the
                 EMBED_FUNCTION_NAME configuration parameter)
   ARGUMENTS   : None
**************************************************************************/

#define CTC_MAIN_START { ctc_append_all();

#define CTC_MAIN_END   }


/**************************************************************************
   MACRO       : CTC_LAMBDA_START
   PURPOSE     : Inserted at the start of lambda body
   ARGUMENTS   : - jindex: jump index of the lambda
**************************************************************************/

#define CTC_LAMBDA_START(jindex) \
   { CTC_IJ(jindex)


/**************************************************************************
   MACRO       : CTC_LAMBDA_END
   PURPOSE     : Inserted at the end of lambda, if the end is reachable
   ARGUMENTS   : - eindex: jump index of the lambda end
**************************************************************************/

#define CTC_LAMBDA_END(eindex) \
   CTC_IJ(eindex) }


/**************************************************************************
   MACRO       : CTC_LAMBDA_END_NR
   PURPOSE     : Inserted at the end of lambda, if the end is Not Reachable
   ARGUMENTS   : None
**************************************************************************/

#define CTC_LAMBDA_END_NR }


/**************************************************************************
   MACRO       : CTC_STMT_JUMP
   PURPOSE     : Inserted at beginning of jump statements break, continue,
                 goto, and __leave
   ARGUMENTS   : - jindex: jump counter index
**************************************************************************/

#define CTC_STMT_JUMP(jindex) \
   { CTC_IJ(jindex)


/**************************************************************************
   MACRO       : CTC_STMT_RETURN
   PURPOSE     : Inserted at start of return and throw statements.
   ARGUMENTS   : - name: string literal, name of the function
                 - jindex: jump counter index
                 - tindex: timer index (when timing-instrumented, same as
                           function counter index; otherwise meaningless)
**************************************************************************/

#define CTC_STMT_RETURN(name, jindex, tindex) \
   { CTC_STOP(tindex) CTC_IJ(jindex)


/**************************************************************************
   MACRO       : CTC_STMT_TIMER_RETURN
   PURPOSE     : Inserted at start of return statements, if timing
                 instrumentation AND only function coverage
   ARGUMENTS   : - name: string literal, name of the function
                 - tindex: timer index (same as function counter index)
**************************************************************************/

#define CTC_STMT_TIMER_RETURN(name, tindex) \
   { CTC_STOP(tindex)


/**************************************************************************
   MACRO       : CTC_STMT_END
   PURPOSE     : Ends a statement started with CTC_STMT_JUMP,
                 CTC_STMT_RETURN, or CTC_STMT_TIMER_RETURN
   ARGUMENTS   : None
**************************************************************************/

#define CTC_STMT_END }


/**************************************************************************
   MACRO       : CTC_CASE_PREV
   PURPOSE     : Inserted at the end of the previous case or default if
                 execution "falls through" from the previous case/default
   ARGUMENTS   : - jindex: jump counter index
**************************************************************************/

#if !defined(CTC_CASE_FALL_THROUGH_LOOSE)
#  define CTC_CASE_PREV(jindex) \
     goto CTC_L##jindex;
#else
#  define CTC_CASE_PREV(jindex)
#endif


/**************************************************************************
   MACRO       : CTC_CASE_CURR1
   PURPOSE     : Inserted at the beginning of the current case or default
                 if execution does NOT "fall through" from the previous
                 case/default
   ARGUMENTS   : - jindex: jump counter index
**************************************************************************/

#define CTC_CASE_CURR1(jindex) CTC_IJ(jindex)


/**************************************************************************
   MACRO       : CTC_CASE_CURR2
   PURPOSE     : Inserted at the beginning of the current case or default
                 if execution DOES "fall through" from the previous
                 case/default
   ARGUMENTS   : - jindex: jump counter index
**************************************************************************/

#if !defined(CTC_CASE_FALL_THROUGH_LOOSE)
#  define CTC_CASE_CURR2(jindex) \
     CTC_IJ(jindex) CTC_L##jindex:
#else
#  define CTC_CASE_CURR2(jindex) \
     CTC_IJ(jindex)
#endif


/**************************************************************************
   MACRO       : CTC_LOOP_START
   PURPOSE     : Inserted at the start of loop body
   ARGUMENTS   : - jindex: jump index of the loop
**************************************************************************/

#define CTC_LOOP_START(jindex) \
   { CTC_IJ(jindex)


/**************************************************************************
   MACRO       : CTC_LOOP_END
   PURPOSE     : Inserted at the end of loop body
   ARGUMENTS   : None
**************************************************************************/

#define CTC_LOOP_END }


/**************************************************************************
   MACRO       : CTC_TRY_START
   PURPOSE     : Start of a try block
   ARGUMENTS   : - jindex: jump index of the try
**************************************************************************/

#define CTC_TRY_START(jindex) \
   { CTC_IJ(jindex)


/**************************************************************************
   MACRO       : CTC_TRY_END
   PURPOSE     : End of a try sequence
   ARGUMENTS   : None
**************************************************************************/

#define CTC_TRY_END }


/**************************************************************************
   MACRO       : CTC_CATCH_START
   PURPOSE     : Start of a normal catch sequence
   ARGUMENTS   : - jindex: jump index of the catch
                 - tindex: timer index (when timing-instrumented, same as
                           function counter index; otherwise meaningless)
**************************************************************************/

#define CTC_CATCH_START(jindex, tindex) \
   { CTC_START(tindex) CTC_IJ(jindex)


/**************************************************************************
   MACRO       : CTC_CATCH_END
   PURPOSE     : End of a normal catch sequence
   ARGUMENTS   : None
**************************************************************************/

#define CTC_CATCH_END }


/**************************************************************************
   MACRO       : CTC_CTRCATCH_START
   PURPOSE     : Start of a constructor function catch sequence
   ARGUMENTS   : - jindex: jump index of the catch
**************************************************************************/

#define CTC_CTRCATCH_START(jindex) \
   CTC_INIT CTC_IJ(jindex) {


/**************************************************************************
   MACRO       : CTC_CTRCATCH_END
   PURPOSE     : End of a constructor function catch sequence
   ARGUMENTS   : - name: string literal, name of the function
                 - eindex: jump index of the catch end
**************************************************************************/

#define CTC_CTRCATCH_END(name, eindex) \
   CTC_IJ(eindex) }


/**************************************************************************
   MACRO       : CTC_CTRCATCH_END_MAIN
   PURPOSE     : End of constructor function catch sequence of "main"
                 function (function whose name matches any of the values
                 in the EMBED_FUNCTION_NAME configuration parameter),
                 if the end is reachable
   ARGUMENTS   : - name: string literal, name of the function
                 - eindex: jump index of the catch end
**************************************************************************/

#define CTC_CTRCATCH_END_MAIN(name, eindex) \
   CTC_IJ(eindex) ctc_append_all(); }


/**************************************************************************
   MACRO       : CTC_CTRCATCH_END_NR
   PURPOSE     : End of a constructor function catch sequence, if the end
                 is Not Reachable
   ARGUMENTS   : None
**************************************************************************/

#define CTC_CTRCATCH_END_NR }


/**************************************************************************
   MACRO       : CTC_BLOCK_START/END
   PURPOSE     : Start/end of a CTC++ generated block
   ARGUMENTS   : None
**************************************************************************/

#define CTC_BLOCK_START {

#define CTC_BLOCK_END   }


/**************************************************************************
   MACRO       : CTC_PRAGMA_APPEND/_INIT/_QUIT/_COUNT/_TESTCASE
   PURPOSE     : Pragma command expansions
   ARGUMENTS   : - jindex: jump index of the own counter
                 - name: string literal, name of a new test case, or an
                         empty string if there is none
**************************************************************************/

#define CTC_PRAGMA_APPEND          ctc_append_all();
#define CTC_PRAGMA_INIT            ctc_init();
#define CTC_PRAGMA_QUIT            ctc_quit();
#define CTC_PRAGMA_COUNT(jindex)   CTC_IJ(jindex)
#define CTC_PRAGMA_TESTCASE(name)  ctc_set_testcase(name);


/*
Module initializer
*/

#define CTC_INIT if (!ctc_s) ctc_module_init();


/*
Multicondition auxiliary temporary variable
*/

#define CTC_MULTI_TMP unsigned int ctc_m;


/*
Function end counter (a jump counter);
no counter when function coverage only
*/

#if defined(CTC_DECISION)
#  define CTC_IE(i) CTC_IJ(i)
#else
#  define CTC_IE(i)
#endif


#ifdef CTC_SAFE
#  define CTC_IS(i)          ctc_inc(ctc_s + i);
#  define CTC_IJ(i)          ctc_inc(ctc_j + i);
#  if defined(__cplusplus)
#    define CTC_COND_START(i)  ctc_condition(ctc_t, ctc_f, \
                                             i, static_cast<bool>(
#  else
#    define CTC_COND_START(i)  ctc_condition(ctc_t, ctc_f, \
                                             i, (int) (
#  endif
#  define CTC_COND_END(i)    ))
#  define CTC_M_START        ( ctc_m = 0, (
#  if defined(__cplusplus) && !defined(CTC_CLIKE_MCOND) && \
      !defined(__embedded_cplusplus)
#    define CTC_M_IND(x, n)  (static_cast<bool>(x) && (ctc_m += n))
#  else
#    define CTC_M_IND(x, n)  (x && (ctc_m += n))
#  endif
#  define CTC_M_END(c)       ) ? (ctc_inc(ctc_c + c + ctc_m), 1) : \
                                 (ctc_inc(ctc_c + c + ctc_m), 0) )
#  if !defined(CTC_DECL_COND_NO_INSTR)
#    define CTC_DECL_COND_START(i) ctc_inc(ctc_f + i);
#    define CTC_DECL_COND_END(i)   ctc_dec(ctc_f + i); \
                                   ctc_inc(ctc_t + i);
#  else
#    define CTC_DECL_COND_START(i)
#    define CTC_DECL_COND_END(i)
#  endif
#  if !defined(CTC_COND_OPER_NO_INSTR)
#    if defined(__cplusplus)
#      define CTC_COND_OPER_START(i) ctc_condition(ctc_t, ctc_f, i, \
                                                   static_cast<bool>(
#    else
#      define CTC_COND_OPER_START(i) ctc_condition(ctc_t, ctc_f, i, \
                                                   (int) (
#    endif
#    define CTC_COND_OPER_END(i)   ))
#  else
#    define CTC_COND_OPER_START(i)
#    define CTC_COND_OPER_END(i)
#  endif

#else /* !defined(CTC_SAFE) */
#  define CTC_IS(i)          ctc_s[i]++;
#  define CTC_IJ(i)          ctc_j[i]++;
#  define CTC_COND_START(i)  ((
#  define CTC_COND_END(i)    ) ? (ctc_t[i]++, 1) : (ctc_f[i]++, 0))
#  define CTC_M_START        ( ctc_m = 0, (
#  if defined(__cplusplus) && !defined(CTC_CLIKE_MCOND) && \
      !defined(__embedded_cplusplus)
#    define CTC_M_IND(x, n)  (static_cast<bool>(x) && (ctc_m += n))
#  else
#    define CTC_M_IND(x, n)  (x && (ctc_m += n))
#  endif
#  define CTC_M_END(c)       ) ? (ctc_c[c + ctc_m]++, 1) : \
                                 (ctc_c[c + ctc_m]++, 0) )
#  if !defined(CTC_DECL_COND_NO_INSTR)
#    define CTC_DECL_COND_START(i) ctc_f[i]++;
#    define CTC_DECL_COND_END(i)   ctc_f[i]--; ctc_t[i]++;
#  else
#    define CTC_DECL_COND_START(i)
#    define CTC_DECL_COND_END(i)
#  endif
#  if !defined(CTC_COND_OPER_NO_INSTR)
#    define CTC_COND_OPER_START(i) ((
#    define CTC_COND_OPER_END(i)   ) ? (ctc_t[i]++, 1) : \
                                       (ctc_f[i]++, 0))
#  else
#    define CTC_COND_OPER_START(i)
#    define CTC_COND_OPER_END(i)
#  endif
#endif /* CTC_SAFE */


#ifdef CTC_TIMING
#  if defined(__cplusplus) && !defined(CTC_CLIKE_TIMING) && \
      !defined(__embedded_cplusplus)
#    define CTC_TIMER_TMP Ctc_timer_class ctc_timer_object;
#    define CTC_START(i)  ctc_timer_object.set_timer(&(ctc_time[i]), \
                                                     &(ctc_maxtime[i]));
#    define CTC_STOP(i)
#  else /* !defined(__cplusplus) || defined(CTC_CLIKE_TIMING) */
#    ifdef CTC_INCLUSIVE_TIMING
#      define CTC_TIMER_TMP CTC_TIMER ctc_start_temp;
#      define CTC_START(i)  ctc_start_temp = ctc_timer();
#      define CTC_STOP(i)                                         \
         { CTC_TIMER ctc_end_temp = ctc_timer();                  \
           CTC_TIMER ctc_elapsed_temp =                           \
              ctc_end_temp - ctc_start_temp;                      \
           ctc_time[i] += ctc_elapsed_temp;                       \
           if (ctc_elapsed_temp > ctc_maxtime[i])                 \
              ctc_maxtime[i] = ctc_elapsed_temp;                  \
           ctc_start_temp = ctc_end_temp; }
#    else /* !defined(CTC_INCLUSIVE_TIMING) */
#      define CTC_TIMER_TMP                                       \
         CTC_TIMER ctc_start_temp;                                \
         CTC_TIMER* ctc_prev_tp;                                  \
         CTC_TIMER* ctc_prev_maxtp;                               \
         CTC_TIMER ctc_prev_elapsed;
#      define CTC_START(i)                                        \
         ctc_start_temp = ctc_timer();                            \
         ctc_prev_tp = ctc_curf_tp;                               \
         ctc_prev_maxtp = ctc_curf_maxtp;                         \
         *ctc_prev_tp += ctc_start_temp - ctc_curf_start;         \
         ctc_prev_elapsed =                                       \
            ctc_curf_elapsed + (ctc_start_temp - ctc_curf_start); \
         ctc_curf_tp = &(ctc_time[i]);                            \
         ctc_curf_maxtp = &(ctc_maxtime[i]);                      \
         ctc_curf_start = ctc_start_temp;                         \
         ctc_curf_elapsed = 0;
#      define CTC_STOP(i)                                         \
         ctc_start_temp = ctc_timer();                            \
         if (ctc_curf_tp == &(ctc_time[i]))                       \
            ctc_time[i] += ctc_start_temp - ctc_curf_start;       \
         ctc_curf_elapsed += ctc_start_temp - ctc_curf_start;     \
         if (ctc_curf_elapsed > *ctc_curf_maxtp)                  \
            *ctc_curf_maxtp = ctc_curf_elapsed;                   \
         ctc_curf_tp = ctc_prev_tp;                               \
         ctc_curf_maxtp = ctc_prev_maxtp;                         \
         ctc_curf_start = ctc_start_temp;                         \
         ctc_curf_elapsed = ctc_prev_elapsed;
#    endif /* CTC_INCLUSIVE_TIMING */
#  endif /* __cplusplus */
#else /* !defined(CTC_TIMING) */
   /* If timing not defined, define empty macros. */
#  define CTC_TIMER_TMP
#  define CTC_START(i)
#  define CTC_STOP(i)
#endif /* CTC_TIMING */


#ifdef CTC_SPECIAL
#  include "ctcalt.h"
#endif

#endif /* CTC_H */

/* EOF $RCSfile: ctc.h $ */
