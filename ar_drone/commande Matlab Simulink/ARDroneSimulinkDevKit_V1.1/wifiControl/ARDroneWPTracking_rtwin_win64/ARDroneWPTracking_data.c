/*
 * ARDroneWPTracking_data.c
 *
 * Code generation for model "ARDroneWPTracking".
 *
 * Model version              : $Id: UAV_PIL.mdl 965 2013-03-21 01:08:53Z escobar $
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Fri Feb 26 18:24:15 2016
 *
 * Target selection: rtwin.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ARDroneWPTracking.h"
#include "ARDroneWPTracking_private.h"

/* Block parameters (auto storage) */
P_ARDroneWPTracking_T ARDroneWPTracking_P = {
  10.0,                                /* Expression: MaxMissedTicks
                                        * Referenced by: '<S8>/Packet Output'
                                        */
  0.0,                                 /* Expression: YieldWhenWaiting
                                        * Referenced by: '<S8>/Packet Output'
                                        */
  10.0,                                /* Expression: MaxMissedTicks
                                        * Referenced by: '<S11>/Packet Output1'
                                        */
  0.0,                                 /* Expression: YieldWhenWaiting
                                        * Referenced by: '<S11>/Packet Output1'
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
   * Referenced by: '<S19>/Constant1'
   */
  { 0.0, 0.0 },

  /*  Expression: waypoints
   * Referenced by: '<S3>/Constant5'
   */
  { 0.0, 0.0, 1.0, 0.0, 1.0, -0.22984884706593012, 0.42073549240394825, 1.0, 0.0,
    1.0, -0.70807341827357118, 0.45464871341284085, 1.0, 0.0, 1.0,
    -0.99499624830022271, 0.0705600040299336, 1.0, 0.0, 1.0,
    -0.82682181043180591, -0.3784012476539641, 1.0, 0.0, 1.0,
    -0.3581689072683869, -0.47946213733156923, 1.0, 0.0, 1.0,
    -0.019914856674816961, -0.13970774909946293, 1.0, 0.0, 1.0,
    -0.1230488728283477, 0.32849329935939453, 1.0, 0.0, 1.0,
    -0.57275001690430671, 0.49467912331169089, 1.0, 0.0, 1.0,
    -0.95556513094233853, 0.2060592426208783, 1.0, 0.0, 1.0,
    -0.91953576453822627, -0.27201055544468489, 1.0, 0.0, 1.0,
    -0.49778715100597459, -0.49999510327535174, 1.0, 0.0, 1.0,
    -0.078073020633753931, -0.26828645900021747, 1.0, 0.0, 1.0,
    -0.0462766092749019, 0.21008351841332046, 1.0, 0.0, 1.0,
    -0.43163139089608321, 0.49530367784743518, 1.0, 0.0, 1.0,
    -0.87984395642941071, 0.32514392007855841, 1.0, 0.0, 1.0,
    -0.97882974016169233, -0.14395165833253265, 1.0, 0.0, 1.0,
    -0.63758166902579849, -0.4806987459397784, 1.0, 0.0, 1.0,
    -0.16984164587795991, -0.37549362338583808, 1.0, 0.0, 1.0,
    -0.0056476909066653924, 0.074938604831476172, 1.0, 0.0, 1.0,
    -0.295958969093304, 0.45647262536381383, 1.0, 0.0, 1.0, -0.77386463011213413,
    0.41832781926802803, 1.0, 0.0, 1.0, -0.99998041319731856,
    -0.0044256546452019381, 1.0, 0.0, 1.0, -0.76641651016669876,
    -0.42311020208758532, 1.0, 0.0, 1.0, -0.28791049633150151,
    -0.45278918100331189, 1.0, 0.0, 1.0, -0.0043985940682632063,
    -0.066175875048886515, 1.0, 0.0, 1.0, -0.17654033883567982,
    0.3812792252398014, 1.0, 0.0, 1.0, -0.64606940436691807, 0.47818796420225151,
    1.0, 0.0, 1.0, -0.9813029331567833, 0.13545289415393452, 1.0, 0.0, 1.0,
    -0.87402876484450021, -0.33181694210648377, 1.0, 0.0, 1.0,
    -0.422874275056208, -0.49401581204643091, 1.0, 0.0, 1.0,
    -0.04262882109773436, -0.20201882266153251, 1.0, 0.0, 1.0,
    -0.082888319746744876, 0.27571334062084529, 1.0, 0.0, 1.0,
    -0.50663837361152975, 0.49995593005363359, 1.0, 0.0, 1.0,
    -0.92428513739230267, 0.26454134306001192, 1.0, 0.0, 1.0,
    -0.95184610254575341, -0.21409133474807551, 1.0, 0.0, 1.0,
    -0.56398184481370239, -0.49588942672155789, 1.0, 0.0, 1.0,
    -0.1172929740273283, -0.32176906667849975, 1.0, 0.0, 1.0,
    -0.022463177976352555, 0.14818428935469266, 1.0, 0.0, 1.0,
    -0.36667853382003135, 0.48189769314204389, 1.0, 0.0, 1.0, -0.833469030826131,
    0.37255658023967442, 1.0, 0.0, 1.0, -0.99366963876191328,
    -0.0793113344023545, 1.0, 0.0, 1.0, -0.69999265749417561,
    -0.45826077395781689, 1.0, 0.0, 1.0, -0.22244334923968717,
    -0.41588737131429915, 1.0, 0.0, 1.0, -7.834567615438992E-5,
    0.0088509625527067887, 1.0, 0.0, 1.0, -0.23733900559113513,
    0.42545176226705922, 1.0, 0.0, 1.0, -0.71608897244238912,
    0.45089417382440461, 1.0, 0.0, 1.0, -0.99616773457546437, 0.061786561372612,
    1.0, 0.0, 1.0, -0.82007216973459984, -0.38412733066183341, 1.0, 0.0, 1.0,
    -0.34970372812818146, -0.47687632637973593, 1.0, 0.0, 1.0 },
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
                                        * Referenced by: '<S16>/Gain3'
                                        */
  0.4,                                 /* Expression: 0.4
                                        * Referenced by: '<S15>/Gain1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation 1'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation 1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S16>/Gain2'
                                        */
  -0.5,                                /* Expression: -0.5
                                        * Referenced by: '<S12>/Gain'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation 2'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation 2'
                                        */
  1.5,                                 /* Expression: 1.5
                                        * Referenced by: '<S13>/proportional control gain - yaw'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation 3'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation 3'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S14>/proportional control gain'
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
                                        * Referenced by: '<S5>/deg 2 rad1'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S8>/Packet Output'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S11>/Packet Output1'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S1>/Packet Input'
                                        */

  /*  Computed Parameter: Constant_Value
   * Referenced by: '<S11>/Constant'
   */
  { 1U, 13U },
  1U,                                  /* Computed Parameter: ManualSwitch1_CurrentSetting
                                        * Referenced by: '<Root>/Manual Switch1'
                                        */
  0U,                                  /* Computed Parameter: ManualSwitch2_CurrentSetting
                                        * Referenced by: '<Root>/Manual Switch2'
                                        */
  1U                                   /* Computed Parameter: ManualSwitch_CurrentSetting
                                        * Referenced by: '<Root>/Manual Switch'
                                        */
};
