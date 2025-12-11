/*
 * PUBLISHED header for C cgxert, the runtime library for CGXE C file
 *
 * Copyright 2014-2016 The MathWorks, Inc.
 *
 */

#ifndef cgxert_h
#define cgxert_h

#if defined(_MSC_VER)
# pragma once
#endif
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3))
# pragma once
#endif

/*
 * Only define EXTERN_C if it hasn't been defined already. This allows
 * individual modules to have more control over managing their exports.
 */
#ifndef EXTERN_C

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif

#endif

#ifndef LIBCGXERT_API
#define LIBCGXERT_API
#endif

#if defined(BUILDING_LIBMWCGXERT) || defined(DLL_IMPORT_SYM)
/* internal use */
# include "simstruct/simstruc.h"
#else
/* external use */
# include "simstruc.h"
#endif

#include <stdarg.h>

typedef struct covrtInstance covrtInstance;

typedef enum {
    CGXERT_DIAG_BLOCK_PATH = 0,
    CGXERT_DIAG_STRING, 
    CGXERT_DIAG_STRING_FROM_DOUBLE,
    CGXERT_DIAG_NUMERIC,
    CGXERT_DIAG_NUMERIC_FROM_DOUBLE
} cgxertDiagnosticsInputType;


/*
 *  MATLAB INTERNAL USE ONLY :: macro wrappers for jit mode
 */ 
EXTERN_C LIBCGXERT_API const void* cgxertGetInputPortSignal(SimStruct *S, int32_T/*Sint32*/index);
EXTERN_C LIBCGXERT_API const void* const * cgxertGetInputPortSignalPtrs(SimStruct *S, int32_T ip);
EXTERN_C LIBCGXERT_API void* cgxertGetOutputPortSignal(SimStruct *S, int32_T index);
EXTERN_C LIBCGXERT_API void* cgxertGetDWork(SimStruct *S, int32_T index);
EXTERN_C LIBCGXERT_API void* cgxertGetRunTimeParamInfoData(SimStruct *S, int32_T index);
/* Get varsize input port dimensions array address */
EXTERN_C LIBCGXERT_API int* cgxertGetCurrentInputPortDimensions(SimStruct *S, int32_T portNumber);
/* Get varsize output port dimensions array address */
EXTERN_C LIBCGXERT_API int* cgxertGetCurrentOutputPortDimensions(SimStruct *S, int32_T portNumber);
EXTERN_C LIBCGXERT_API void cgxertSetCurrentOutputPortDimensions(SimStruct *S, int32_T pIdx, int32_T dIdx, int32_T val);
EXTERN_C LIBCGXERT_API bool cgxertIsMajorTimeStep(SimStruct *S);
EXTERN_C LIBCGXERT_API void cgxertSetSolverNeedsReset(SimStruct *S);
EXTERN_C LIBCGXERT_API double cgxertGetT(SimStruct *S);
EXTERN_C LIBCGXERT_API double cgxertGetTaskTime(SimStruct *S, int32_T sti);
EXTERN_C LIBCGXERT_API bool cgxertIsSampleHit(SimStruct *S, int32_T sti, int32_T tid);
EXTERN_C LIBCGXERT_API void* cgxertGetPrevZCSigState(SimStruct *S);
EXTERN_C LIBCGXERT_API void cgxertCallAccelRunBlock(SimStruct *S, int32_T sysIdx, int32_T blkIdx, int32_T method);
EXTERN_C LIBCGXERT_API int32_T cgxertGetSubsysIdx(SimStruct *S);
EXTERN_C LIBCGXERT_API void cgxertSetDisallowSimState(SimStruct *S);

/*
 * MATLAB INTERNAL USE ONLY :: Runtime info access functions
 */
EXTERN_C LIBCGXERT_API void* cgxertGetRuntimeInstance(SimStruct* S);
EXTERN_C LIBCGXERT_API void cgxertSetRuntimeInstance(SimStruct* S, void* instance);

EXTERN_C LIBCGXERT_API void* cgxertGetEMLRTCtx(SimStruct *S);
EXTERN_C LIBCGXERT_API covrtInstance* cgxertGetCovrtInstance(SimStruct *S);
EXTERN_C LIBCGXERT_API uint32_T cgxertGetCovId(SimStruct *S);


/*
 * MATLAB INTERNAL USE ONLY :: macro wrappers for Data Store Memory functions
 */

EXTERN_C LIBCGXERT_API void ReadFromDataStoreElement_wrapper(SimStruct *S, int dsmIndex, void *dataAddr, int elementIndex);
EXTERN_C LIBCGXERT_API void WriteToDataStoreElement_wrapper(SimStruct *S, int dsmIndex, void *dataAddr, int elementIndex);
EXTERN_C LIBCGXERT_API void AccessDataStore_wrapper(SimStruct *S, int dsmIndex, void *dataAddr, int isReadOnly);
EXTERN_C LIBCGXERT_API void UpdateDataStoreLog_wrapper(SimStruct *S, void* dsmId);
EXTERN_C LIBCGXERT_API void GetDataStoreNameAddrIdx_wrapper(SimStruct *S, const char *name, void **dsmAddress, int *dsmIndex);
EXTERN_C LIBCGXERT_API void MemRegionCreateDescriptor_wrapper(SimStruct *S, int numSubMemRegions, SFcnMemRegionInfo** memRegionDescriptor);
EXTERN_C LIBCGXERT_API void MemRegionSetFlatSubElement_wrapper(SimStruct *S, SFcnMemRegionInfo* memRegionDescriptor, int subRegionIdx, int busElementIdx, int numFlatIdx, int *flatIdxs);
EXTERN_C LIBCGXERT_API void AccessDataStoreRegion_wrapper(SimStruct *S, int dsmIdx, void *dataAddr,  SFcnMemRegionInfo* dsmRegionDescriptor, bool isReadOnly);
EXTERN_C LIBCGXERT_API void MemRegionDestroyDescriptor_wrapper(SimStruct *S, SFcnMemRegionInfo** memRegionDescriptor);

/*
 * MATLAB INTERNAL USE ONLY :: Check for Ctrl+C interrupt from the command prompt
 */
EXTERN_C LIBCGXERT_API unsigned int cgxertListenForCtrlC(SimStruct *S);

/*
 * Call back functions into Simulink engine
 */
/*
 * Call Simulink Function server
 */
EXTERN_C LIBCGXERT_API void cgxertCallSLFcn(SimStruct* S,
                                            const char* fcnName,
                                            const char* fullPath,
                                            int blkId,
                                            int numInputs,
                                            void* inArgs,
                                            void* inSizes,
                                            int numOutputs,
                                            void* outArgs,
                                            int* outSizes);
/*
 * MATLAB INTERNAL USE ONLY :: Get runtime error status
 */
EXTERN_C LIBCGXERT_API bool cgxertGetErrorStatus(SimStruct *S);

/*
 * MATLAB INTERNAL USE ONLY :: Handle runtime diagnostic report request
 */
EXTERN_C LIBCGXERT_API void cgxertReportDiagnostics(SimStruct* S, int sysIdx, int blkIdx, 
                                                    int diagType, int diagModeIndex,
                                                    const char* const aMsgID,
                                                    const int aArgCount, ...);
/*
 * MATLAB INTERNAL USE ONLY :: Check diagnostic setting to be not none
 */
EXTERN_C LIBCGXERT_API bool cgxertCheckDiagnosticSettingNotNone(SimStruct* S, int sysIdx, int blkIdx,
                                                                int diagType, int diagModeIndex);

/*
 * MATLAB INTERNAL USE ONLY :: Multithreading helpers
 */
EXTERN_C LIBCGXERT_API void cgxertSemCreate(void** semPtr);
EXTERN_C LIBCGXERT_API void cgxertSemPost(void* semPtr);
EXTERN_C LIBCGXERT_API void cgxertSemWait(void* semPtr);
EXTERN_C LIBCGXERT_API void cgxertSemDestroy(void* semPtr);

#endif /* cgxert_h */

