/*
 * OpenSW.h
 *
 * Code generation for model "OpenSW".
 *
 * Model version              : 1.11
 * Simulink Coder version : 8.11 (R2016b) 25-Aug-2016
 * C source code generated on : Tue Jun 15 13:29:08 2021
 *
 * Target selection: grtfmi.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_OpenSW_h_
#define RTW_HEADER_OpenSW_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef OpenSW_COMMON_INCLUDES_
# define OpenSW_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* OpenSW_COMMON_INCLUDES_ */

#include "OpenSW_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->defaultParam = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ((rtm)->paramIsMalloced)
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ((rtm)->paramIsMalloced = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->inputs = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->outputs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define OpenSW_M_TYPE                  RT_MODEL_OpenSW_T

/* Block signals (auto storage) */
typedef struct {
  real_T Switch;                       /* '<Root>/Switch' */
  real_T Subtract;                     /* '<Root>/Subtract' */
  real_T Gain_Kp;                      /* '<Root>/Gain_Kp' */
  real_T UnitDelay;                    /* '<Root>/Unit Delay' */
  real_T UnitDelay1;                   /* '<Root>/Unit Delay1' */
  real_T Subtract1;                    /* '<Root>/Subtract1' */
  real_T Gain_KI;                      /* '<Root>/Gain_KI' */
  real_T Product;                      /* '<Root>/Product' */
  real_T Add2;                         /* '<Root>/Add2' */
  real_T Add1;                         /* '<Root>/Add1' */
  real_T Add3;                         /* '<Root>/Add3' */
  real_T Max;                          /* '<S6>/Max' */
  real_T Min;                          /* '<S6>/Min' */
  boolean_T Compare;                   /* '<S1>/Compare' */
} B_OpenSW_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  real_T UnitDelay1_DSTATE;            /* '<Root>/Unit Delay1' */
} DW_OpenSW_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  Input_Type Input;                    /* '<Root>/Input' */
} ExtU_OpenSW_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T TCoolingPack;                 /* '<Root>/TCoolingPack' */
} ExtY_OpenSW_T;

/* Parameters (auto storage) */
struct P_OpenSW_T_ {
  real_T Ki;                           /* Variable: Ki
                                        * Referenced by: '<Root>/Gain_KI'
                                        */
  real_T Kp;                           /* Variable: Kp
                                        * Referenced by: '<Root>/Gain_Kp'
                                        */
  real_T OpenSW_Sample_Time;           /* Variable: OpenSW_Sample_Time
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Saturation_LowerLimit;        /* Mask Parameter: Saturation_LowerLimit
                                        * Referenced by: '<S5>/Lower_Limit'
                                        */
  real_T Saturation_UpperLimit;        /* Mask Parameter: Saturation_UpperLimit
                                        * Referenced by: '<S5>/Upper_Limit'
                                        */
  real_T Constant1_Value;              /* Mask Parameter: Constant1_Value
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant2_Value;              /* Mask Parameter: Constant2_Value
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  real_T UnitDelay1_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay1'
                                        */
  Aircraft_State_Type Constant_Value;  /* Expression: Aircraft_State_Type.Airborne
                                        * Referenced by: '<S1>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_OpenSW_T {
  const char_T *errorStatus;
  B_OpenSW_T *blockIO;
  P_OpenSW_T *defaultParam;
  ExtU_OpenSW_T *inputs;
  ExtY_OpenSW_T *outputs;
  boolean_T paramIsMalloced;
  DW_OpenSW_T *dwork;
};

/* External data declarations for dependent source files */
extern const Input_Type OpenSW_rtZInput_Type;/* Input_Type ground */
extern const char *RT_MEMORY_ALLOCATION_ERROR;
extern P_OpenSW_T OpenSW_P;            /* parameters */

/* Model entry point functions */
extern RT_MODEL_OpenSW_T *OpenSW(void);
extern void OpenSW_initialize(RT_MODEL_OpenSW_T *const OpenSW_M);
extern void OpenSW_step(RT_MODEL_OpenSW_T *const OpenSW_M);
extern void OpenSW_terminate(RT_MODEL_OpenSW_T * OpenSW_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'OpenSW'
 * '<S1>'   : 'OpenSW/Compare_To_Enum'
 * '<S2>'   : 'OpenSW/Constant1'
 * '<S3>'   : 'OpenSW/Constant2'
 * '<S4>'   : 'OpenSW/Constant3'
 * '<S5>'   : 'OpenSW/Saturation'
 * '<S6>'   : 'OpenSW/Saturation/Saturation_Dynamic'
 */
#endif                                 /* RTW_HEADER_OpenSW_h_ */
