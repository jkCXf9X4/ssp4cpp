/*
 * OpenSW.c
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

const Input_Type OpenSW_rtZInput_Type = { 0.0,/* TLiquid */
  Aircraft_State_Type_Stationary       /* Aircraft_State */
};

/* Model step function */
void OpenSW_step(RT_MODEL_OpenSW_T *const OpenSW_M)
{
  P_OpenSW_T *OpenSW_P = ((P_OpenSW_T *) OpenSW_M->defaultParam);
  B_OpenSW_T *OpenSW_B = ((B_OpenSW_T *) OpenSW_M->blockIO);
  DW_OpenSW_T *OpenSW_DW = ((DW_OpenSW_T *) OpenSW_M->dwork);
  ExtU_OpenSW_T *OpenSW_U = (ExtU_OpenSW_T *) OpenSW_M->inputs;
  ExtY_OpenSW_T *OpenSW_Y = (ExtY_OpenSW_T *) OpenSW_M->outputs;
  real_T maxV;

  /* Outputs for Atomic SubSystem: '<Root>/Compare_To_Enum' */
  /* RelationalOperator: '<S1>/Compare' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Input'
   */
  OpenSW_B->Compare = (OpenSW_U->Input.Aircraft_State ==
                       OpenSW_P->Constant_Value);

  /* End of Outputs for SubSystem: '<Root>/Compare_To_Enum' */

  /* Switch: '<Root>/Switch' */
  if (OpenSW_B->Compare) {
    /* Outputs for Atomic SubSystem: '<Root>/Constant2' */
    OpenSW_B->Switch = OpenSW_P->Constant2_Value;

    /* End of Outputs for SubSystem: '<Root>/Constant2' */
  } else {
    /* Outputs for Atomic SubSystem: '<Root>/Constant1' */
    OpenSW_B->Switch = OpenSW_P->Constant1_Value;

    /* End of Outputs for SubSystem: '<Root>/Constant1' */
  }

  /* End of Switch: '<Root>/Switch' */

  /* Sum: '<Root>/Subtract' incorporates:
   *  Inport: '<Root>/Input'
   */
  OpenSW_B->Subtract = OpenSW_B->Switch - OpenSW_U->Input.TLiquid;

  /* Gain: '<Root>/Gain_Kp' */
  OpenSW_B->Gain_Kp = OpenSW_P->Kp * OpenSW_B->Subtract;

  /* UnitDelay: '<Root>/Unit Delay' */
  OpenSW_B->UnitDelay = OpenSW_DW->UnitDelay_DSTATE;

  /* UnitDelay: '<Root>/Unit Delay1' */
  OpenSW_B->UnitDelay1 = OpenSW_DW->UnitDelay1_DSTATE;

  /* Sum: '<Root>/Subtract1' incorporates:
   *  Inport: '<Root>/Input'
   */
  OpenSW_B->Subtract1 = (OpenSW_B->Switch - OpenSW_U->Input.TLiquid) +
    OpenSW_B->UnitDelay1;

  /* Gain: '<Root>/Gain_KI' */
  OpenSW_B->Gain_KI = OpenSW_P->Ki * OpenSW_B->Subtract1;

  /* Product: '<Root>/Product' incorporates:
   *  Constant: '<S4>/Constant'
   */
  OpenSW_B->Product = OpenSW_B->Gain_KI * OpenSW_P->OpenSW_Sample_Time;

  /* Sum: '<Root>/Add2' */
  OpenSW_B->Add2 = OpenSW_B->UnitDelay + OpenSW_B->Product;

  /* Sum: '<Root>/Add1' */
  OpenSW_B->Add1 = OpenSW_B->Gain_Kp + OpenSW_B->Add2;

  /* Outputs for Atomic SubSystem: '<Root>/Saturation' */
  /* Outputs for Atomic SubSystem: '<S5>/Saturation_Dynamic' */
  /* MinMax: '<S6>/Max' */
  maxV = fmax(OpenSW_B->Add1, OpenSW_P->Saturation_LowerLimit);
  OpenSW_B->Max = maxV;

  /* MinMax: '<S6>/Min' */
  maxV = fmin(OpenSW_P->Saturation_UpperLimit, OpenSW_B->Max);
  OpenSW_B->Min = maxV;

  /* End of Outputs for SubSystem: '<S5>/Saturation_Dynamic' */
  /* End of Outputs for SubSystem: '<Root>/Saturation' */

  /* Outport: '<Root>/TCoolingPack' incorporates:
   *  Sum: '<Root>/Add'
   */
  OpenSW_Y->TCoolingPack = OpenSW_B->Min + OpenSW_B->Switch;

  /* Sum: '<Root>/Add3' */
  OpenSW_B->Add3 = OpenSW_B->Min - OpenSW_B->Add1;

  /* Update for UnitDelay: '<Root>/Unit Delay' */
  OpenSW_DW->UnitDelay_DSTATE = OpenSW_B->Add2;

  /* Update for UnitDelay: '<Root>/Unit Delay1' */
  OpenSW_DW->UnitDelay1_DSTATE = OpenSW_B->Add3;
}

/* Model initialize function */
void OpenSW_initialize(RT_MODEL_OpenSW_T *const OpenSW_M)
{
  P_OpenSW_T *OpenSW_P = ((P_OpenSW_T *) OpenSW_M->defaultParam);
  DW_OpenSW_T *OpenSW_DW = ((DW_OpenSW_T *) OpenSW_M->dwork);

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  OpenSW_DW->UnitDelay_DSTATE = OpenSW_P->UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay1' */
  OpenSW_DW->UnitDelay1_DSTATE = OpenSW_P->UnitDelay1_InitialCondition;
}

/* Model terminate function */
void OpenSW_terminate(RT_MODEL_OpenSW_T * OpenSW_M)
{
  /* model code */
  rt_FREE(OpenSW_M->blockIO);
  rt_FREE(OpenSW_M->inputs);
  rt_FREE(OpenSW_M->outputs);
  if (OpenSW_M->paramIsMalloced) {
    rt_FREE(OpenSW_M->defaultParam);
  }

  rt_FREE(OpenSW_M->dwork);
  rt_FREE(OpenSW_M);
}

/* Model data allocation function */
RT_MODEL_OpenSW_T *OpenSW(void)
{
  RT_MODEL_OpenSW_T *OpenSW_M;
  OpenSW_M = (RT_MODEL_OpenSW_T *) malloc(sizeof(RT_MODEL_OpenSW_T));
  if (OpenSW_M == NULL) {
    return NULL;
  }

  (void) memset((char *)OpenSW_M, 0,
                sizeof(RT_MODEL_OpenSW_T));

  /* block I/O */
  {
    B_OpenSW_T *b = (B_OpenSW_T *) malloc(sizeof(B_OpenSW_T));
    rt_VALIDATE_MEMORY(OpenSW_M,b);
    OpenSW_M->blockIO = (b);
  }

  /* parameters */
  {
    P_OpenSW_T *p;
    static int_T pSeen = 0;

    /* only malloc on multiple model instantiation */
    if (pSeen == 1 ) {
      p = (P_OpenSW_T *) malloc(sizeof(P_OpenSW_T));
      rt_VALIDATE_MEMORY(OpenSW_M,p);
      (void) memcpy(p, &OpenSW_P,
                    sizeof(P_OpenSW_T));
      OpenSW_M->paramIsMalloced = (true);
    } else {
      p = &OpenSW_P;
      OpenSW_M->paramIsMalloced = (false);
      pSeen = 1;
    }

    OpenSW_M->defaultParam = (p);
  }

  /* states (dwork) */
  {
    DW_OpenSW_T *dwork = (DW_OpenSW_T *) malloc(sizeof(DW_OpenSW_T));
    rt_VALIDATE_MEMORY(OpenSW_M,dwork);
    OpenSW_M->dwork = (dwork);
  }

  /* external inputs */
  {
    ExtU_OpenSW_T *OpenSW_U = (ExtU_OpenSW_T *) malloc(sizeof(ExtU_OpenSW_T));
    rt_VALIDATE_MEMORY(OpenSW_M,OpenSW_U);
    OpenSW_M->inputs = (((ExtU_OpenSW_T *) OpenSW_U));
  }

  /* external outputs */
  {
    ExtY_OpenSW_T *OpenSW_Y = (ExtY_OpenSW_T *) malloc(sizeof(ExtY_OpenSW_T));
    rt_VALIDATE_MEMORY(OpenSW_M,OpenSW_Y);
    OpenSW_M->outputs = (OpenSW_Y);
  }

  {
    P_OpenSW_T *OpenSW_P = ((P_OpenSW_T *) OpenSW_M->defaultParam);
    B_OpenSW_T *OpenSW_B = ((B_OpenSW_T *) OpenSW_M->blockIO);
    DW_OpenSW_T *OpenSW_DW = ((DW_OpenSW_T *) OpenSW_M->dwork);
    ExtU_OpenSW_T *OpenSW_U = (ExtU_OpenSW_T *) OpenSW_M->inputs;
    ExtY_OpenSW_T *OpenSW_Y = (ExtY_OpenSW_T *) OpenSW_M->outputs;

    /* block I/O */
    (void) memset(((void *) OpenSW_B), 0,
                  sizeof(B_OpenSW_T));

    /* states (dwork) */
    (void) memset((void *)OpenSW_DW, 0,
                  sizeof(DW_OpenSW_T));

    /* external inputs */
    OpenSW_U->Input = OpenSW_rtZInput_Type;

    /* external outputs */
    OpenSW_Y->TCoolingPack = 0.0;
  }

  return OpenSW_M;
}
