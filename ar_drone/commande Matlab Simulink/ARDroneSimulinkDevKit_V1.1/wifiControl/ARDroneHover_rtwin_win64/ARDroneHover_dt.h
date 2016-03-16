/*
 * ARDroneHover_dt.h
 *
 * Code generation for model "ARDroneHover".
 *
 * Model version              : $Id: UAV_PIL.mdl 965 2013-03-21 01:08:53Z escobar $
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Fri Feb 26 16:27:27 2016
 *
 * Target selection: rtwin.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&ARDroneHover_B.ManualSwitch1), 0, 0, 68 },

  { (char_T *)(&ARDroneHover_B.PacketInput_o1[0]), 3, 0, 650 },

  { (char_T *)(&ARDroneHover_B.PacketInput_o2), 8, 0, 1 }
  ,

  { (char_T *)(&ARDroneHover_DW.UnitDelaytoavoidalgebraicloop_DSTATE), 0, 0, 8 },

  { (char_T *)(&ARDroneHover_DW.PacketOutput_PWORK[0]), 11, 0, 12 },

  { (char_T *)(&ARDroneHover_DW.Integrator_IWORK.IcNeedsLoading), 10, 0, 1 },

  { (char_T *)(&ARDroneHover_DW.frame[0]), 3, 0, 2512 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&ARDroneHover_P.PacketOutput_MaxMissedTicks), 0, 0, 35 },

  { (char_T *)(&ARDroneHover_P.PacketOutput_PacketID), 6, 0, 3 },

  { (char_T *)(&ARDroneHover_P.Constant_Value[0]), 3, 0, 5 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  3U,
  rtPTransitions
};

/* [EOF] ARDroneHover_dt.h */
