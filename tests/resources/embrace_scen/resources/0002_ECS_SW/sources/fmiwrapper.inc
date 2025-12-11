#include "OpenSW.h"
#include "OpenSW_private.h"

typedef struct {
	BuiltInDTypeId dtypeID;
	size_t size;
	void* address;
} ModelVariable;

#ifndef NO_FMI_FUNCTION_PREFIX
#define FMI2_FUNCTION_PREFIX OpenSW_
#endif

#define MODEL_GUID       "{62d7e035-6100-43aa-941f-6cfc6384bd36}"
#define MODEL            OpenSW
#define MODEL_INITIALIZE OpenSW_initialize
#define MODEL_STEP       OpenSW_step
#define MODEL_TERMINATE  OpenSW_terminate
#define RT_MDL_TYPE      RT_MODEL_OpenSW_T
#define STEP_SIZE        0.033333333333333333

/* R2019a defines the block parameters as extern */
#ifndef rtmGetDefaultParam
#define rtmGetDefaultParam(S) (&OpenSW_P)
#endif

#define REUSABLE_FUNCTION

static void initializeModelVariables(RT_MDL_TYPE* S, ModelVariable modelVariables[]) {
    modelVariables[0].dtypeID = 0;
    modelVariables[0].size    = 0;
    modelVariables[0].address = &(rtmGetU(S)->Input.TLiquid);
    modelVariables[1].dtypeID = 6;
    modelVariables[1].size    = 0;
    modelVariables[1].address = &(rtmGetU(S)->Input.Aircraft_State);
    modelVariables[2].dtypeID = 0;
    modelVariables[2].size    = 0;
    modelVariables[2].address = &(rtmGetY(S)->TCoolingPack);
}

#define N_MODEL_VARIABLES 4
