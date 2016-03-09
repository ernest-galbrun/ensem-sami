/*
 * ARDroneHover_data.c
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
#include "ARDroneHover.h"
#include "ARDroneHover_private.h"

/* Block parameters (auto storage) */
P_ARDroneHover_T ARDroneHover_P = {
  10.0,                                /* Expression: MaxMissedTicks
                                        * Referenced by: '<S7>/Packet Output'
                                        */
  0.0,                                 /* Expression: YieldWhenWaiting
                                        * Referenced by: '<S7>/Packet Output'
                                        */
  10.0,                                /* Expression: MaxMissedTicks
                                        * Referenced by: '<S10>/Packet Output1'
                                        */
  0.0,                                 /* Expression: YieldWhenWaiting
                                        * Referenced by: '<S10>/Packet Output1'
                                        */
  1.0,                                 /* Expression: MaxMissedTicks
                                        * Referenced by: '<S1>/Packet Input'
                                        */
  0.0,                                 /* Expression: YieldWhenWaiting
                                        * Referenced by: '<S1>/Packet Input'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/land'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/take off'
                                        */

  /*  Expression: [0 0]
   * Referenced by: '<S17>/Constant1'
   */
  { 0.0, 0.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Inertial X ref (m)'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Inertial Y ref (m)'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Unit Delay to avoid algebraic loop'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/commands disabled'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/commands enabled'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<Root>/deg 2 rad'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S15>/Gain3'
                                        */
  0.4,                                 /* Expression: 0.4
                                        * Referenced by: '<S14>/Gain1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation 1'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation 1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S15>/Gain2'
                                        */
  -0.5,                                /* Expression: -0.5
                                        * Referenced by: '<S11>/Gain'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation 2'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation 2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Heading ref (rad)'
                                        */
  1.5,                                 /* Expression: 1.5
                                        * Referenced by: '<S12>/proportional control gain - yaw'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation 3'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation 3'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Height ref (m)'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S13>/proportional control gain'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation 4'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation 4'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/_'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/stop'
                                        */
  57.295779513082323,                  /* Expression: 180/pi
                                        * Referenced by: '<S4>/deg 2 rad1'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S7>/Packet Output'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S10>/Packet Output1'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S1>/Packet Input'
                                        */

  /*  Computed Parameter: Constant_Value
   * Referenced by: '<S10>/Constant'
   */
  { 1U, 13U },
  1U,                                  /* Computed Parameter: ManualSwitch1_CurrentSetting
                                        * Referenced by: '<Root>/Manual Switch1'
                                        */
  1U,                                  /* Computed Parameter: ManualSwitch2_CurrentSetting
                                        * Referenced by: '<Root>/Manual Switch2'
                                        */
  1U                                   /* Computed Parameter: ManualSwitch_CurrentSetting
                                        * Referenced by: '<Root>/Manual Switch'
                                        */
};
