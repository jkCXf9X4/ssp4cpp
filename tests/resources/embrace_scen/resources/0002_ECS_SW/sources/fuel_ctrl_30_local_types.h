#ifndef RTW_HEADER_fuel_ctrl_30_local_types_h_
#define RTW_HEADER_fuel_ctrl_30_local_types_h_
#include "rtwtypes.h"

typedef enum {
  Aircraft_State_Type_Stationary = 0,  /* Default value */
  Aircraft_State_Type_Rolling,
  Aircraft_State_Type_Rotating,
  Aircraft_State_Type_Touching_Down,
  Aircraft_State_Type_Airborne
} Aircraft_State_Type;

#endif                                 /* RTW_HEADER_fuel_ctrl_30_local_types_h_ */
