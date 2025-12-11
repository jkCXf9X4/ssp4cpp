/*
 * OpenSW_data.c
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

#include "OpenSW.h"
#include "OpenSW_private.h"

/* Block parameters (auto storage) */
P_OpenSW_T OpenSW_P = {
  1.0,                                 /* Variable: Ki
                                        * Referenced by: '<Root>/Gain_KI'
                                        */
  10.0,                                /* Variable: Kp
                                        * Referenced by: '<Root>/Gain_Kp'
                                        */
  0.033333333333333333,                /* Variable: OpenSW_Sample_Time
                                        * Referenced by: '<S4>/Constant'
                                        */
  -200.0,                              /* Mask Parameter: Saturation_LowerLimit
                                        * Referenced by: '<S5>/Lower_Limit'
                                        */
  200.0,                               /* Mask Parameter: Saturation_UpperLimit
                                        * Referenced by: '<S5>/Upper_Limit'
                                        */
  313.0,                               /* Mask Parameter: Constant1_Value
                                        * Referenced by: '<S2>/Constant'
                                        */
  293.0,                               /* Mask Parameter: Constant2_Value
                                        * Referenced by: '<S3>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay1'
                                        */
  Aircraft_State_Type_Airborne         /* Expression: Aircraft_State_Type.Airborne
                                        * Referenced by: '<S1>/Constant'
                                        */
};
