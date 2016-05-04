/*
 * ARDroneHover.c
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
#include "ARDroneHover_dt.h"

/* options for Real-Time Windows Target board 0 */
static double RTWinBoardOptions0[] = {
  3.232235777E+9,
  5556.0,
};

/* options for Real-Time Windows Target board 1 */
static double RTWinBoardOptions1[] = {
  3.232235777E+9,
  5554.0,
};

/* list of Real-Time Windows Target timers */
const int RTWinTimerCount = 2;
const double RTWinTimers[4] = {
  0.065, 0.0,
  0.65, 0.0,
};

/* list of Real-Time Windows Target boards */
const int RTWinBoardCount = 2;
RTWINBOARD RTWinBoards[2] = {
  { "Standard_Devices/UDP_Protocol", 5556U, 2, RTWinBoardOptions0 },

  { "Standard_Devices/UDP_Protocol", 5554U, 2, RTWinBoardOptions1 },
};

/* Block signals (auto storage) */
B_ARDroneHover_T ARDroneHover_B;

/* Continuous states */
X_ARDroneHover_T ARDroneHover_X;

/* Block states (auto storage) */
DW_ARDroneHover_T ARDroneHover_DW;

/* Real-time model */
RT_MODEL_ARDroneHover_T ARDroneHover_M_;
RT_MODEL_ARDroneHover_T *const ARDroneHover_M = &ARDroneHover_M_;

/* Forward declaration for local functions */
static void ARDroneHover_dec2hex(const uint8_T d[4], char_T s_data[8], int32_T
  s_sizes[2]);
static real_T ARDroneHover_hex2dec(const char_T s_data[8], const int32_T
  s_sizes[2]);
static void ARDroneHover_getString(real_T a, char_T strOut_data[11], int32_T
  strOut_sizes[2]);
static int32_T ARDroneHover_float2IEEE754(real_T fVal);
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(ARDroneHover_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(ARDroneHover_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (ARDroneHover_M->Timing.TaskCounters.TID[2])++;
  if ((ARDroneHover_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.65s, 0.0s] */
    ARDroneHover_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  ARDroneHover_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for MATLAB Function: '<S1>/ARDrone data decoding' */
static void ARDroneHover_dec2hex(const uint8_T d[4], char_T s_data[8], int32_T
  s_sizes[2])
{
  uint8_T di;
  uint8_T r;
  int32_T firstcol;
  int32_T b_j;
  boolean_T p;
  int32_T c_i;
  boolean_T exitg;
  boolean_T exitg_0;
  char_T s_data_0[8];
  s_sizes[0] = 4;
  s_sizes[1] = 2;
  for (b_j = 0; b_j < 8; b_j++) {
    s_data[b_j] = '0';
  }

  di = d[0];
  b_j = 2;
  exitg = FALSE;
  while ((!exitg) && (b_j > 0)) {
    r = di;
    di = (uint8_T)((uint32_T)di >> 4);
    r = (uint8_T)((uint32_T)r - (di << 4));
    if (r > 9) {
      r += 7U;
    }

    s_data[(b_j - 1) << 2] = (int8_T)(r + 48);
    if (di > 0) {
      b_j--;
    } else {
      exitg = TRUE;
    }
  }

  di = d[1];
  b_j = 2;
  exitg = FALSE;
  while ((!exitg) && (b_j > 0)) {
    r = di;
    di = (uint8_T)((uint32_T)di >> 4);
    r = (uint8_T)((uint32_T)r - (di << 4));
    if (r > 9) {
      r += 7U;
    }

    s_data[1 + ((b_j - 1) << 2)] = (int8_T)(r + 48);
    if (di > 0) {
      b_j--;
    } else {
      exitg = TRUE;
    }
  }

  di = d[2];
  b_j = 2;
  exitg = FALSE;
  while ((!exitg) && (b_j > 0)) {
    r = di;
    di = (uint8_T)((uint32_T)di >> 4);
    r = (uint8_T)((uint32_T)r - (di << 4));
    if (r > 9) {
      r += 7U;
    }

    s_data[2 + ((b_j - 1) << 2)] = (int8_T)(r + 48);
    if (di > 0) {
      b_j--;
    } else {
      exitg = TRUE;
    }
  }

  di = d[3];
  b_j = 2;
  exitg = FALSE;
  while ((!exitg) && (b_j > 0)) {
    r = di;
    di = (uint8_T)((uint32_T)di >> 4);
    r = (uint8_T)((uint32_T)r - (di << 4));
    if (r > 9) {
      r += 7U;
    }

    s_data[3 + ((b_j - 1) << 2)] = (int8_T)(r + 48);
    if (di > 0) {
      b_j--;
    } else {
      exitg = TRUE;
    }
  }

  firstcol = 2;
  b_j = 1;
  exitg = FALSE;
  while ((!exitg) && (b_j <= 1)) {
    p = FALSE;
    c_i = 0;
    exitg_0 = FALSE;
    while ((!exitg_0) && (c_i <= 3)) {
      if (s_data[c_i] != '0') {
        p = TRUE;
        exitg_0 = TRUE;
      } else {
        c_i++;
      }
    }

    if (p) {
      firstcol = 1;
      exitg = TRUE;
    } else {
      b_j = 2;
    }
  }

  if (firstcol > 1) {
    s_data[0] = s_data[4];
    s_data[1] = s_data[5];
    s_data[2] = s_data[6];
    s_data[3] = s_data[7];
    s_data_0[0] = s_data[0];
    s_data_0[1] = s_data[1];
    s_data_0[2] = s_data[2];
    s_data_0[3] = s_data[3];
    s_sizes[0] = 4;
    s_sizes[1] = 1;
    for (b_j = 0; b_j < 1; b_j++) {
      s_data[0] = s_data_0[0];
      s_data[1] = s_data_0[1];
      s_data[2] = s_data_0[2];
      s_data[3] = s_data_0[3];
    }
  }
}

/* Function for MATLAB Function: '<S1>/ARDrone data decoding' */
static real_T ARDroneHover_hex2dec(const char_T s_data[8], const int32_T
  s_sizes[2])
{
  real_T x;
  real_T p;
  int32_T j;
  int32_T b_j;
  x = 0.0;
  p = 1.0;
  for (b_j = 1; b_j - 1 < s_sizes[1]; b_j++) {
    j = s_sizes[1] - b_j;
    if (s_data[s_sizes[0] * j] != ' ') {
      if (((uint8_T)s_data[s_sizes[0] * j] != 0) && ((uint8_T)s_data[s_sizes[0] *
           j] != 48)) {
        if ((uint8_T)s_data[s_sizes[0] * j] <= 57) {
          j = (uint8_T)s_data[s_sizes[0] * j];
        } else if ((uint8_T)s_data[s_sizes[0] * j] > 70) {
          j = (uint8_T)s_data[s_sizes[0] * j] - 39;
        } else {
          j = (uint8_T)s_data[s_sizes[0] * j] - 7;
        }

        x += ((real_T)j - 48.0) * p;
      }

      p *= 16.0;
    }
  }

  return x;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = -0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = (rtNaN);
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S7>/Drone state request' */
static void ARDroneHover_getString(real_T a, char_T strOut_data[11], int32_T
  strOut_sizes[2])
{
  int32_T d;
  int32_T k;
  real_T c;
  real_T r;
  int32_T i;
  uint8_T digit_data[11];

  /* % My str2num function that allows for code generation */
  /* '<S9>:1:138' */
  d = 1;
  if ((a >= 10.0) && (a < 100.0)) {
    /* '<S9>:1:144' */
    /* '<S9>:1:145' */
    d = 2;
  }

  if ((a >= 100.0) && (a < 1000.0)) {
    /* '<S9>:1:148' */
    /* '<S9>:1:149' */
    d = 3;
  }

  if ((a >= 1000.0) && (a < 10000.0)) {
    /* '<S9>:1:152' */
    /* '<S9>:1:153' */
    d = 4;
  }

  if ((a >= 10000.0) && (a < 100000.0)) {
    /* '<S9>:1:156' */
    /* '<S9>:1:157' */
    d = 5;
  }

  if ((a >= 100000.0) && (a < 1.0E+6)) {
    /* '<S9>:1:160' */
    /* '<S9>:1:161' */
    d = 6;
  }

  if ((a >= 1.0E+6) && (a < 1.0E+7)) {
    /* '<S9>:1:164' */
    /* '<S9>:1:165' */
    d = 7;
  }

  if ((a >= 1.0E+7) && (a < 1.0E+8)) {
    /* '<S9>:1:168' */
    /* '<S9>:1:169' */
    d = 8;
  }

  if ((a >= 1.0E+8) && (a < 1.0E+9)) {
    /* '<S9>:1:172' */
    /* '<S9>:1:173' */
    d = 9;
  }

  if ((a >= 1.0E+9) && (a < 1.0E+10)) {
    /* '<S9>:1:176' */
    /* '<S9>:1:177' */
    d = 10;
  }

  if (a >= 1.0E+10) {
    /* '<S9>:1:180' */
    /* '<S9>:1:181' */
    d = 11;
  }

  /* '<S9>:1:186' */
  for (i = 0; i < d; i++) {
    digit_data[i] = 0U;
  }

  /* d = length(a) ; */
  /* '<S9>:1:189' */
  for (k = 0; k < d; k++) {
    /* '<S9>:1:189' */
    /* '<S9>:1:191' */
    c = rt_powd_snf(10.0, 1.0 + (real_T)k);
    if (c == c) {
      r = a - floor(a / c) * c;
    } else {
      r = a / c;
      if (fabs(r - rt_roundd_snf(r)) <= 2.2204460492503131E-16 * fabs(r)) {
        r = 0.0;
      } else {
        r = (r - floor(r)) * c;
      }
    }

    /* ( mod(a,10*k) - resTotal)/(10*k) ; */
    /* '<S9>:1:194' */
    c = floor(r / rt_powd_snf(10.0, (1.0 + (real_T)k) - 1.0) + 48.0);
    if (rtIsNaN(c) || rtIsInf(c)) {
      c = 0.0;
    } else {
      c = fmod(c, 256.0);
    }

    digit_data[(d - k) - 1] = (uint8_T)(c < 0.0 ? (int32_T)(int8_T)-(int8_T)
      (uint8_T)-c : (int32_T)(int8_T)(uint8_T)c);

    /* '<S9>:1:189' */
  }

  /* '<S9>:1:199' */
  strOut_sizes[0] = 1;
  strOut_sizes[1] = (int8_T)d;
  k = (int8_T)d;
  for (i = 0; i < k; i++) {
    strOut_data[i] = (char_T)digit_data[i];
  }
}

/* Function for MATLAB Function: '<S7>/Drone state request' */
static int32_T ARDroneHover_float2IEEE754(real_T fVal)
{
  int32_T iVal;
  char_T binData[32];
  char_T binData_0[32];
  int32_T bit;
  real_T b_iVal;
  uint8_T y[4];
  real32_T x;
  int32_T b_k;

  /* % Function to obtain a IEEE754 representation of a float number */
  /* '<S9>:1:207' */
  x = (real32_T)fVal;
  memcpy(&y[0], &x, 4U);
  for (b_k = 0; b_k < 32; b_k++) {
    binData[b_k] = '0';
  }

  for (b_k = 0; b_k < 4; b_k++) {
    for (bit = 0; bit < 8; bit++) {
      if ((1 << bit & y[b_k]) != 0) {
        binData[b_k + ((7 - bit) << 2)] = '1';
      }
    }
  }

  /* '<S9>:1:209' */
  for (b_k = 0; b_k < 8; b_k++) {
    binData_0[b_k] = binData[(b_k << 2) + 3];
  }

  for (b_k = 0; b_k < 8; b_k++) {
    binData_0[b_k + 8] = binData[(b_k << 2) + 2];
  }

  for (b_k = 0; b_k < 8; b_k++) {
    binData_0[b_k + 16] = binData[(b_k << 2) + 1];
  }

  for (b_k = 0; b_k < 8; b_k++) {
    binData_0[b_k + 24] = binData[b_k << 2];
  }

  /* '<S9>:1:210' */
  b_iVal = 0.0;

  /* '<S9>:1:211' */
  for (b_k = 0; b_k < 32; b_k++) {
    /* '<S9>:1:211' */
    if (binData_0[31 - b_k] == '1') {
      /* '<S9>:1:213' */
      /* '<S9>:1:214' */
      bit = 1;
    } else {
      /* '<S9>:1:216' */
      bit = 0;
    }

    if (32 - b_k == 1) {
      /* '<S9>:1:219' */
      /* '<S9>:1:220' */
      b_iVal -= (real_T)bit * 2.147483648E+9;
    } else {
      /* '<S9>:1:222' */
      b_iVal += rt_powd_snf(2.0, 32.0 - (32.0 + -(real_T)b_k)) * (real_T)bit;
    }

    /* '<S9>:1:211' */
  }

  /* '<S9>:1:227' */
  b_iVal = rt_roundd_snf(b_iVal);
  if (b_iVal < 2.147483648E+9) {
    if (b_iVal >= -2.147483648E+9) {
      iVal = (int32_T)b_iVal;
    } else {
      iVal = MIN_int32_T;
    }
  } else {
    iVal = MAX_int32_T;
  }

  return iVal;
}

/* Model output function for TID0 */
void ARDroneHover_output0(void)        /* Sample time: [0.0s, 0.0s] */
{
  real_T bytesToRead;
  boolean_T exitg;
  uint8_T data[496];
  real32_T e_res;
  real32_T f_res;
  real32_T g_res;
  int32_T aux;
  static const char_T c[30] = { ',', '\"', 'g', 'e', 'n', 'e', 'r', 'a', 'l',
    ':', 'n', 'a', 'v', 'd', 'a', 't', 'a', '_', 'd', 'e', 'm', 'o', '\"', ',',
    '\"', 'T', 'R', 'U', 'E', '\"' };

  static const char_T d[10] = { 'A', 'T', '*', 'C', 'O', 'N', 'F', 'I', 'G', '='
  };

  static const char_T e[10] = { ',', '2', '9', '0', '7', '1', '7', '9', '5', '2'
  };

  static const char_T f[7] = { 'A', 'T', '*', 'R', 'E', 'F', '=' };

  static const char_T g[9] = { 'A', 'T', '*', 'F', 'T', 'R', 'I', 'M', '=' };

  static const char_T h[30] = { '\"', 'c', 'o', 'n', 'r', 'o', 'l', ':', 'a',
    'l', 't', 'i', 't', 'u', 'd', 'e', '_', 'm', 'a', 'x', '\"', ',', '\"', '1',
    '0', '0', '0', '0', '0', '\"' };

  static const char_T i[10] = { ',', '2', '9', '0', '7', '1', '8', '2', '0', '8'
  };

  static const char_T k[8] = { 'A', 'T', '*', 'P', 'C', 'M', 'D', '=' };

  static const char_T l[10] = { ',', '2', '9', '0', '7', '1', '7', '6', '9', '6'
  };

  static const char_T m[10] = { 'A', 'T', '*', 'C', 'O', 'M', 'W', 'D', 'G', '='
  };

  real32_T rtb_rollAngle;
  real32_T rtb_pitchAngle;
  real32_T rtb_yawAngle;
  real_T rtb_Saturation1;
  real32_T rtb_u;
  real_T rtb_Saturation2;
  real_T rtb_height;
  real_T rtb_battery;
  real32_T rtb_w;
  int32_T i_0;
  int32_T i_1;
  int32_T loop_ub;
  int32_T loop_ub_0;
  int32_T loop_ub_1;
  int16_T tmp[496];
  int16_T o_data[496];
  char_T hex_data[8];
  int32_T hex_sizes[2];
  char_T b_hex_data[8];
  char_T cmd_data[144];
  char_T strCmd_data[11];
  int32_T hex_sizes_0[2];
  int32_T hex_sizes_1[2];
  int32_T hex_sizes_2[2];
  int32_T hex_sizes_3[2];
  int32_T hex_sizes_4[2];
  int32_T hex_sizes_5[2];
  int32_T hex_sizes_6[2];
  int32_T hex_sizes_7[2];
  char_T cmd_data_0[144];
  char_T tmp_data[12];
  int32_T tmp_data_0[144];
  int32_T tmp_data_1[496];
  int32_T aux_data[1024];
  int32_T m_data[1024];
  uint8_T tmp_data_2[1024];
  int32_T b_hex_sizes_idx;
  real_T unnamed_idx;
  uint32_T x;
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* set solver stop time */
    if (!(ARDroneHover_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&ARDroneHover_M->solverInfo,
                            ((ARDroneHover_M->Timing.clockTickH0 + 1) *
        ARDroneHover_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&ARDroneHover_M->solverInfo,
                            ((ARDroneHover_M->Timing.clockTick0 + 1) *
        ARDroneHover_M->Timing.stepSize0 + ARDroneHover_M->Timing.clockTickH0 *
        ARDroneHover_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(ARDroneHover_M)) {
    ARDroneHover_M->Timing.t[0] = rtsiGetT(&ARDroneHover_M->solverInfo);
  }

  /* S-Function Block: <S7>/Packet Output */

  /* no code required */
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* S-Function Block: <S1>/Packet Input */
    {
      uint8_T indata[500U];
      int status = RTBIO_DriverIO(1, STREAMINPUT, IOREAD, 500U,
        &ARDroneHover_P.PacketInput_PacketID, (double*) indata, NULL);
      ARDroneHover_B.PacketInput_o2 = status & 0x1;/* Data Ready port */
      if (status & 0x1) {
        RTWin_ANYTYPEPTR indp;
        indp.p_uint8_T = indata;

        {
          int_T i1;
          uint8_T *y0 = ARDroneHover_B.PacketInput_o1;
          for (i1=0; i1 < 500; i1++) {
            y0[i1] = *indp.p_uint8_T++;
          }
        }
      }
    }

    /* MATLAB Function: '<S1>/Data synchronization ' */
    /* MATLAB Function 'ARDrone Wi-Fi  Block/Data synchronization ': '<S6>:1' */
    /* % Author: David Escobar Sanabria */
    /*   Description: This function synchronizes data coming from the flight computer */
    /*   computer.  */
    /*   frameOut: Organized frame */
    /*   frameIn: sequence of bytes not sync. */
    /* % Size of byte array containing the data */
    /* % Size of the array read each time step */
    /* size(dataIn,1);  */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* % Initialization of presistent variables */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* % Filling the buffer */
    /* '<S6>:1:52' */
    for (i_1 = 0; i_1 < 500; i_1++) {
      ARDroneHover_DW.buffer[(int32_T)(ARDroneHover_DW.countBuffer + (1.0 +
        (real_T)i_1)) - 1] = ARDroneHover_B.PacketInput_o1[i_1];
    }

    /* '<S6>:1:54' */
    bytesToRead = ARDroneHover_DW.countBuffer + 500.0;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* % Reading buffer */
    /* '<S6>:1:59' */
    b_hex_sizes_idx = 0;
    exitg = FALSE;
    while ((!exitg) && (b_hex_sizes_idx <= (int32_T)(ARDroneHover_DW.countBuffer
             + 500.0) - 1)) {
      /* '<S6>:1:59' */
      if ((ARDroneHover_DW.countHeader == 4.0) && (ARDroneHover_DW.count < 496.0))
      {
        /* '<S6>:1:60' */
        /* '<S6>:1:61' */
        rtb_height = 496.0 - ARDroneHover_DW.count;
        unnamed_idx = ((1.0 + (real_T)b_hex_sizes_idx) + (496.0 -
          ARDroneHover_DW.count)) - 1.0;
        if (1.0 + (real_T)b_hex_sizes_idx > unnamed_idx) {
          aux = 1;
          loop_ub_1 = 0;
        } else {
          aux = (int32_T)(1.0 + (real_T)b_hex_sizes_idx);
          loop_ub_1 = (int32_T)unnamed_idx;
        }

        /* '<S6>:1:62' */
        i_1 = (int32_T)(ARDroneHover_DW.count + 1.0);
        loop_ub = -i_1;
        for (loop_ub_0 = 0; loop_ub_0 <= loop_ub + 496; loop_ub_0++) {
          tmp_data_1[loop_ub_0] = i_1 + loop_ub_0;
        }

        loop_ub = loop_ub_1 - aux;
        for (i_1 = 0; i_1 <= loop_ub; i_1++) {
          aux_data[i_1] = aux + i_1;
        }

        i_0 = (loop_ub_1 - aux) + 1;
        for (i_1 = 0; i_1 < i_0; i_1++) {
          for (loop_ub_0 = 0; loop_ub_0 < 1; loop_ub_0++) {
            ARDroneHover_DW.frame[tmp_data_1[i_1] - 1] =
              ARDroneHover_DW.buffer[aux_data[i_1] - 1];
          }
        }

        /* '<S6>:1:63' */
        ARDroneHover_DW.count = 496.0;

        /* '<S6>:1:64' */
        ARDroneHover_DW.countBuffer = (ARDroneHover_DW.countBuffer + 500.0) -
          rtb_height;
        rtb_height += 1.0 + (real_T)b_hex_sizes_idx;
        if (rtb_height > bytesToRead) {
          loop_ub_1 = 1;
          loop_ub_0 = 0;
        } else {
          loop_ub_1 = (int32_T)rtb_height;
          loop_ub_0 = (int32_T)bytesToRead;
        }

        if (1.0 > ARDroneHover_DW.countBuffer) {
          aux = 0;
        } else {
          aux = (int32_T)ARDroneHover_DW.countBuffer;
        }

        /* '<S6>:1:65' */
        for (i_1 = 0; i_1 < aux; i_1++) {
          aux_data[i_1] = 1 + i_1;
        }

        loop_ub = loop_ub_0 - loop_ub_1;
        for (i_1 = 0; i_1 <= loop_ub; i_1++) {
          m_data[i_1] = loop_ub_1 + i_1;
        }

        i_0 = (loop_ub_0 - loop_ub_1) + 1;
        for (i_1 = 0; i_1 < i_0; i_1++) {
          for (loop_ub_0 = 0; loop_ub_0 < 1; loop_ub_0++) {
            tmp_data_2[i_1] = ARDroneHover_DW.buffer[m_data[i_1] - 1];
          }
        }

        for (i_1 = 0; i_1 < i_0; i_1++) {
          ARDroneHover_DW.buffer[aux_data[i_1] - 1] = tmp_data_2[i_1];
        }

        exitg = TRUE;
      } else if ((ARDroneHover_DW.countHeader == 3.0) &&
                 (ARDroneHover_DW.buffer[(int32_T)(1.0 + (real_T)b_hex_sizes_idx)
                  - 1] == 85)) {
        /* '<S6>:1:70' */
        /* '<S6>:1:72' */
        ARDroneHover_DW.countHeader = 4.0;
        if ((ARDroneHover_DW.countBuffer + 500.0) - (1.0 + (real_T)
             b_hex_sizes_idx) > 496.0) {
          /* '<S6>:1:74' */
          /* '<S6>:1:75' */
          ARDroneHover_DW.count = 496.0;

          /* '<S6>:1:76' */
          for (i_1 = 0; i_1 < 496; i_1++) {
            o_data[i_1] = (int16_T)((int16_T)(1 + i_1) - 1);
            tmp[i_1] = (int16_T)(1 + i_1);
          }

          for (i_1 = 0; i_1 < 496; i_1++) {
            ARDroneHover_DW.frame[o_data[i_1]] = ARDroneHover_DW.buffer[(int32_T)
              ((1.0 + (real_T)b_hex_sizes_idx) + (real_T)tmp[i_1]) - 1];
          }

          /* '<S6>:1:77' */
          ARDroneHover_DW.countBuffer = ((ARDroneHover_DW.countBuffer + 500.0) -
            (1.0 + (real_T)b_hex_sizes_idx)) - 496.0;
          if (((1.0 + (real_T)b_hex_sizes_idx) + 496.0) + 1.0 > bytesToRead) {
            loop_ub_1 = 1;
            i_0 = 0;
          } else {
            loop_ub_1 = (int32_T)(((1.0 + (real_T)b_hex_sizes_idx) + 496.0) +
                                  1.0);
            i_0 = (int32_T)bytesToRead;
          }

          if (1.0 > ARDroneHover_DW.countBuffer) {
            aux = 0;
          } else {
            aux = (int32_T)ARDroneHover_DW.countBuffer;
          }

          /* '<S6>:1:78' */
          for (i_1 = 0; i_1 < aux; i_1++) {
            aux_data[i_1] = 1 + i_1;
          }

          loop_ub = i_0 - loop_ub_1;
          for (i_1 = 0; i_1 <= loop_ub; i_1++) {
            m_data[i_1] = loop_ub_1 + i_1;
          }

          i_0 = (i_0 - loop_ub_1) + 1;
          for (i_1 = 0; i_1 < i_0; i_1++) {
            for (loop_ub_0 = 0; loop_ub_0 < 1; loop_ub_0++) {
              tmp_data_2[i_1] = ARDroneHover_DW.buffer[m_data[i_1] - 1];
            }
          }

          for (i_1 = 0; i_1 < i_0; i_1++) {
            ARDroneHover_DW.buffer[aux_data[i_1] - 1] = tmp_data_2[i_1];
          }
        } else {
          /* '<S6>:1:81' */
          ARDroneHover_DW.count = (ARDroneHover_DW.countBuffer + 500.0) - (1.0 +
            (real_T)b_hex_sizes_idx);
          if (ARDroneHover_DW.count > 0.0) {
            /* '<S6>:1:82' */
            if ((1.0 + (real_T)b_hex_sizes_idx) + 1.0 >
                ARDroneHover_DW.countBuffer + 500.0) {
              aux = 1;
              loop_ub_1 = 0;
            } else {
              aux = (int32_T)((1.0 + (real_T)b_hex_sizes_idx) + 1.0);
              loop_ub_1 = (int32_T)(ARDroneHover_DW.countBuffer + 500.0);
            }

            /* '<S6>:1:83' */
            loop_ub = (int32_T)ARDroneHover_DW.count;
            for (i_1 = 0; i_1 < loop_ub; i_1++) {
              tmp_data_1[i_1] = 1 + i_1;
            }

            loop_ub = loop_ub_1 - aux;
            for (i_1 = 0; i_1 <= loop_ub; i_1++) {
              aux_data[i_1] = aux + i_1;
            }

            i_0 = (loop_ub_1 - aux) + 1;
            for (i_1 = 0; i_1 < i_0; i_1++) {
              for (loop_ub_0 = 0; loop_ub_0 < 1; loop_ub_0++) {
                ARDroneHover_DW.frame[tmp_data_1[i_1] - 1] =
                  ARDroneHover_DW.buffer[aux_data[i_1] - 1];
              }
            }
          }

          /* '<S6>:1:85' */
          ARDroneHover_DW.countBuffer = 0.0;
        }

        exitg = TRUE;
      } else {
        if ((ARDroneHover_DW.countHeader == 2.0) && (ARDroneHover_DW.buffer
             [(int32_T)(1.0 + (real_T)b_hex_sizes_idx) - 1] == 102)) {
          /* '<S6>:1:92' */
          /* '<S6>:1:93' */
          ARDroneHover_DW.countHeader = 3.0;
        }

        if ((ARDroneHover_DW.countHeader == 1.0) && (ARDroneHover_DW.buffer
             [(int32_T)(1.0 + (real_T)b_hex_sizes_idx) - 1] == 119)) {
          /* '<S6>:1:96' */
          /* '<S6>:1:97' */
          ARDroneHover_DW.countHeader = 2.0;
        }

        if ((ARDroneHover_DW.countHeader == 0.0) && (ARDroneHover_DW.buffer
             [(int32_T)(1.0 + (real_T)b_hex_sizes_idx) - 1] == 136)) {
          /* '<S6>:1:100' */
          /* '<S6>:1:101' */
          ARDroneHover_DW.countHeader = 1.0;
        }

        /* '<S6>:1:59' */
        b_hex_sizes_idx++;
      }
    }

    if (ARDroneHover_DW.count == 496.0) {
      /* '<S6>:1:106' */
      /* '<S6>:1:107' */
      /* '<S6>:1:108' */
      /* '<S6>:1:109' */
      /* '<S6>:1:110' */
      for (i_0 = 0; i_0 < 496; i_0++) {
        ARDroneHover_DW.lastFrame[i_0] = ARDroneHover_DW.frame[i_0];
        ARDroneHover_DW.frame[i_0] = 0U;
      }

      /* '<S6>:1:111' */
      ARDroneHover_DW.count = 0.0;

      /* '<S6>:1:112' */
      ARDroneHover_DW.countHeader = 0.0;
    } else {
      /*  In case the buffer does not have an entire payload */
      /* '<S6>:1:115' */
      /* '<S6>:1:116' */
    }

    /* MATLAB Function: '<S1>/ARDrone data decoding' incorporates:
     *  MATLAB Function: '<S1>/Data synchronization '
     */
    memcpy(&data[0], &ARDroneHover_DW.lastFrame[0], 496U * sizeof(uint8_T));

    /* MATLAB Function 'ARDrone Wi-Fi  Block/ARDrone data decoding': '<S5>:1' */
    /*  Checksum array. cksum(1) contains the computed checksum, cksum(2) */
    /*  contains the checksum sent by the ARDrone.  */
    /*  Previous value of height  */
    /*  Previous data packet */
    /*  Initialization of persistent variables */
    /*  Computing checksum */
    /* '<S5>:1:23' */
    /*  Checksum given by the drone */
    /* '<S5>:1:25' */
    /*  Checksum error */
    /* '<S5>:1:27' */
    /* % Change the following if statement to ensure that the data checksum is valid  */
    /* if (data(15) == 148 && cksumError==0 ) */
    if (ARDroneHover_DW.lastFrame[14] == 148) {
      /* '<S5>:1:30' */
      /* '<S5>:1:31' */
      memcpy(&ARDroneHover_DW.dataPrev[0], &ARDroneHover_DW.lastFrame[0], 496U *
             sizeof(uint8_T));
    } else {
      /* '<S5>:1:33' */
      memcpy(&data[0], &ARDroneHover_DW.dataPrev[0], 496U * sizeof(uint8_T));
    }

    /*  Converting bytes to drone information */
    /* '<S5>:1:37' */
    /* '<S5>:1:74' */
    for (i_0 = 0; i_0 < 32; i_0++) {
      ARDroneHover_B.status[i_0] = 0.0;
    }

    /* '<S5>:1:75' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[0], hex_data, hex_sizes);

    /*  put the hex_value in the order [31, 30......0] */
    /* '<S5>:1:77' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    b_hex_sizes_idx = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) +
      hex_sizes[1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    /* '<S5>:1:78' */
    for (i_0 = 0; i_0 < b_hex_sizes_idx; i_0++) {
      /* '<S5>:1:78' */
      if (b_hex_data[i_0] == 'F') {
        /* '<S5>:1:79' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:80' */
        ARDroneHover_B.status[-3 + aux] = 1.0;
        ARDroneHover_B.status[-2 + aux] = 1.0;
        ARDroneHover_B.status[-1 + aux] = 1.0;
        ARDroneHover_B.status[aux] = 1.0;
      } else if (b_hex_data[i_0] == 'E') {
        /* '<S5>:1:81' */
        loop_ub_1 = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:82' */
        ARDroneHover_B.status[-3 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[-2 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[-1 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[loop_ub_1] = 0.0;
      } else if (b_hex_data[i_0] == 'D') {
        /* '<S5>:1:83' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:84' */
        ARDroneHover_B.status[-3 + aux] = 1.0;
        ARDroneHover_B.status[-2 + aux] = 1.0;
        ARDroneHover_B.status[-1 + aux] = 0.0;
        ARDroneHover_B.status[aux] = 1.0;
      } else if (b_hex_data[i_0] == 'C') {
        /* '<S5>:1:85' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:86' */
        ARDroneHover_B.status[-3 + aux] = 1.0;
        ARDroneHover_B.status[-2 + aux] = 1.0;
        ARDroneHover_B.status[-1 + aux] = 0.0;
        ARDroneHover_B.status[aux] = 0.0;
      } else if (b_hex_data[i_0] == 'B') {
        /* '<S5>:1:87' */
        loop_ub_0 = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:88' */
        ARDroneHover_B.status[-3 + loop_ub_0] = 1.0;
        ARDroneHover_B.status[-2 + loop_ub_0] = 0.0;
        ARDroneHover_B.status[-1 + loop_ub_0] = 1.0;
        ARDroneHover_B.status[loop_ub_0] = 1.0;
      } else if (b_hex_data[i_0] == 'A') {
        /* '<S5>:1:89' */
        loop_ub_1 = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:90' */
        ARDroneHover_B.status[-3 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[-2 + loop_ub_1] = 0.0;
        ARDroneHover_B.status[-1 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[loop_ub_1] = 0.0;
      } else if (b_hex_data[i_0] == '9') {
        /* '<S5>:1:91' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:92' */
        ARDroneHover_B.status[-3 + aux] = 1.0;
        ARDroneHover_B.status[-2 + aux] = 0.0;
        ARDroneHover_B.status[-1 + aux] = 0.0;
        ARDroneHover_B.status[aux] = 1.0;
      } else if (b_hex_data[i_0] == '8') {
        /* '<S5>:1:93' */
        loop_ub_1 = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:94' */
        ARDroneHover_B.status[-3 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[-2 + loop_ub_1] = 0.0;
        ARDroneHover_B.status[-1 + loop_ub_1] = 0.0;
        ARDroneHover_B.status[loop_ub_1] = 0.0;
      } else if (b_hex_data[i_0] == '7') {
        /* '<S5>:1:95' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:96' */
        ARDroneHover_B.status[-3 + aux] = 0.0;
        ARDroneHover_B.status[-2 + aux] = 1.0;
        ARDroneHover_B.status[-1 + aux] = 1.0;
        ARDroneHover_B.status[aux] = 1.0;
      } else if (b_hex_data[i_0] == '6') {
        /* '<S5>:1:97' */
        loop_ub_1 = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:98' */
        ARDroneHover_B.status[-3 + loop_ub_1] = 0.0;
        ARDroneHover_B.status[-2 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[-1 + loop_ub_1] = 1.0;
        ARDroneHover_B.status[loop_ub_1] = 0.0;
      } else if (b_hex_data[i_0] == '5') {
        /* '<S5>:1:99' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:100' */
        ARDroneHover_B.status[-3 + aux] = 0.0;
        ARDroneHover_B.status[-2 + aux] = 1.0;
        ARDroneHover_B.status[-1 + aux] = 0.0;
        ARDroneHover_B.status[aux] = 1.0;
      } else if (b_hex_data[i_0] == '4') {
        /* '<S5>:1:101' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:102' */
        ARDroneHover_B.status[-3 + aux] = 0.0;
        ARDroneHover_B.status[-2 + aux] = 1.0;
        ARDroneHover_B.status[-1 + aux] = 0.0;
        ARDroneHover_B.status[aux] = 0.0;
      } else if (b_hex_data[i_0] == '3') {
        /* '<S5>:1:103' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:104' */
        ARDroneHover_B.status[-3 + aux] = 0.0;
        ARDroneHover_B.status[-2 + aux] = 0.0;
        ARDroneHover_B.status[-1 + aux] = 1.0;
        ARDroneHover_B.status[aux] = 1.0;
      } else if (b_hex_data[i_0] == '2') {
        /* '<S5>:1:105' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:106' */
        ARDroneHover_B.status[-3 + aux] = 0.0;
        ARDroneHover_B.status[-2 + aux] = 0.0;
        ARDroneHover_B.status[-1 + aux] = 1.0;
        ARDroneHover_B.status[aux] = 0.0;
      } else if (b_hex_data[i_0] == '1') {
        /* '<S5>:1:107' */
        aux = ((1 + i_0) << 2) - 1;

        /* '<S5>:1:108' */
        ARDroneHover_B.status[-3 + aux] = 0.0;
        ARDroneHover_B.status[-2 + aux] = 0.0;
        ARDroneHover_B.status[-1 + aux] = 0.0;
        ARDroneHover_B.status[aux] = 1.0;
      } else {
        if (b_hex_data[i_0] == '0') {
          /* '<S5>:1:109' */
          aux = ((1 + i_0) << 2) - 1;

          /* '<S5>:1:110' */
          ARDroneHover_B.status[-3 + aux] = 0.0;
          ARDroneHover_B.status[-2 + aux] = 0.0;
          ARDroneHover_B.status[-1 + aux] = 0.0;
          ARDroneHover_B.status[aux] = 0.0;
        }
      }

      /* '<S5>:1:78' */
    }

    /* '<S5>:1:38' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[20], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:67' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_7[0] = 1;
    hex_sizes_7[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    rtb_battery = ARDroneHover_hex2dec(b_hex_data, hex_sizes_7);

    /*  unit: deg */
    /* '<S5>:1:39' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[24], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:69' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_6[0] = 1;
    hex_sizes_6[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    bytesToRead = rt_roundd_snf(ARDroneHover_hex2dec(b_hex_data, hex_sizes_6));
    if (bytesToRead < 4.294967296E+9) {
      if (bytesToRead >= 0.0) {
        x = (uint32_T)bytesToRead;
      } else {
        x = 0U;
      }
    } else {
      x = MAX_uint32_T;
    }

    memcpy(&rtb_u, &x, 4U);

    /*  unit: deg */
    /* '<S5>:1:40' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[28], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:69' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_5[0] = 1;
    hex_sizes_5[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    bytesToRead = rt_roundd_snf(ARDroneHover_hex2dec(b_hex_data, hex_sizes_5));
    if (bytesToRead < 4.294967296E+9) {
      if (bytesToRead >= 0.0) {
        x = (uint32_T)bytesToRead;
      } else {
        x = 0U;
      }
    } else {
      x = MAX_uint32_T;
    }

    memcpy(&rtb_w, &x, 4U);

    /*  unit: deg */
    /* '<S5>:1:41' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[32], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:69' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_4[0] = 1;
    hex_sizes_4[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    bytesToRead = rt_roundd_snf(ARDroneHover_hex2dec(b_hex_data, hex_sizes_4));
    if (bytesToRead < 4.294967296E+9) {
      if (bytesToRead >= 0.0) {
        x = (uint32_T)bytesToRead;
      } else {
        x = 0U;
      }
    } else {
      x = MAX_uint32_T;
    }

    memcpy(&rtb_yawAngle, &x, 4U);

    /*  unit: deg */
    /* '<S5>:1:42' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[36], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:67' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_3[0] = 1;
    hex_sizes_3[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    rtb_height = ARDroneHover_hex2dec(b_hex_data, hex_sizes_3) / 1000.0;

    /*  unit: deg */
    /* '<S5>:1:43' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[40], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:69' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_2[0] = 1;
    hex_sizes_2[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    bytesToRead = rt_roundd_snf(ARDroneHover_hex2dec(b_hex_data, hex_sizes_2));
    if (bytesToRead < 4.294967296E+9) {
      if (bytesToRead >= 0.0) {
        x = (uint32_T)bytesToRead;
      } else {
        x = 0U;
      }
    } else {
      x = MAX_uint32_T;
    }

    memcpy(&e_res, &x, 4U);

    /*  unit: m/s */
    /* '<S5>:1:44' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[44], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:69' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_1[0] = 1;
    hex_sizes_1[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    bytesToRead = rt_roundd_snf(ARDroneHover_hex2dec(b_hex_data, hex_sizes_1));
    if (bytesToRead < 4.294967296E+9) {
      if (bytesToRead >= 0.0) {
        x = (uint32_T)bytesToRead;
      } else {
        x = 0U;
      }
    } else {
      x = MAX_uint32_T;
    }

    memcpy(&f_res, &x, 4U);

    /*  unit: m/s */
    /* '<S5>:1:45' */
    /*  if mark = 1; then output a int */
    /*  else output the float value which is defined by SDK description. */
    /*  the input is an array (1*4)  */
    /*  e.g. : NDS(Battery_OS:Battery_OS+data_length-1) */
    /* '<S5>:1:64' */
    ARDroneHover_dec2hex(*(uint8_T (*)[4])&data[48], hex_data, hex_sizes);

    /* '<S5>:1:65' */
    /* '<S5>:1:69' */
    loop_ub = hex_sizes[1];
    i_0 = hex_sizes[1];
    loop_ub_0 = hex_sizes[1];
    loop_ub_1 = hex_sizes[1];
    hex_sizes_0[0] = 1;
    hex_sizes_0[1] = ((hex_sizes[1] + hex_sizes[1]) + hex_sizes[1]) + hex_sizes
      [1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      b_hex_data[i_1] = hex_data[hex_sizes[0] * i_1 + 3];
    }

    for (i_1 = 0; i_1 < i_0; i_1++) {
      b_hex_data[i_1 + hex_sizes[1]] = hex_data[hex_sizes[0] * i_1 + 2];
    }

    for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
      b_hex_data[(i_1 + hex_sizes[1]) + hex_sizes[1]] = hex_data[hex_sizes[0] *
        i_1 + 1];
    }

    for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
      b_hex_data[((i_1 + hex_sizes[1]) + hex_sizes[1]) + hex_sizes[1]] =
        hex_data[hex_sizes[0] * i_1];
    }

    bytesToRead = rt_roundd_snf(ARDroneHover_hex2dec(b_hex_data, hex_sizes_0));
    if (bytesToRead < 4.294967296E+9) {
      if (bytesToRead >= 0.0) {
        x = (uint32_T)bytesToRead;
      } else {
        x = 0U;
      }
    } else {
      x = MAX_uint32_T;
    }

    memcpy(&g_res, &x, 4U);

    /*  unit: m/s */
    if ((ARDroneHover_B.status[31] == 1.0) && (rtb_height < 0.2)) {
      /* '<S5>:1:49' */
      /* '<S5>:1:50' */
      rtb_height = ARDroneHover_DW.hPrev;
    } else {
      if (ARDroneHover_B.status[31] == 1.0) {
        /* '<S5>:1:51' */
        /* '<S5>:1:52' */
        ARDroneHover_DW.hPrev = rtb_height;
      }
    }

    rtb_rollAngle = rtb_w / 1000.0F;
    rtb_pitchAngle = rtb_u / 1000.0F;
    rtb_yawAngle /= 1000.0F;
    rtb_u = e_res / 1000.0F;
    rtb_w = g_res / 1000.0F;

    /* ManualSwitch: '<Root>/Manual Switch1' incorporates:
     *  Constant: '<Root>/land'
     *  Constant: '<Root>/take off'
     */
    if (ARDroneHover_P.ManualSwitch1_CurrentSetting == 1) {
      ARDroneHover_B.ManualSwitch1 = ARDroneHover_P.land_Value;
    } else {
      ARDroneHover_B.ManualSwitch1 = ARDroneHover_P.takeoff_Value;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch1' */

    /* DataTypeConversion: '<S1>/Type Conversion6' incorporates:
     *  MATLAB Function: '<S1>/ARDrone data decoding'
     */
    ARDroneHover_B.TypeConversion6 = f_res / 1000.0F;

    /* Constant: '<S17>/Constant1' */
    ARDroneHover_B.Constant1[0] = ARDroneHover_P.Constant1_Value[0];
    ARDroneHover_B.Constant1[1] = ARDroneHover_P.Constant1_Value[1];
  }

  /* Integrator: '<S17>/Integrator' */
  if (ARDroneHover_DW.Integrator_IWORK.IcNeedsLoading) {
    ARDroneHover_X.Integrator_CSTATE[0] = ARDroneHover_B.Constant1[0];
    ARDroneHover_X.Integrator_CSTATE[1] = ARDroneHover_B.Constant1[1];
  }

  ARDroneHover_B.Integrator[0] = ARDroneHover_X.Integrator_CSTATE[0];
  ARDroneHover_B.Integrator[1] = ARDroneHover_X.Integrator_CSTATE[1];
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* Constant: '<Root>/Inertial X ref (m)' */
    ARDroneHover_B.InertialXrefm = ARDroneHover_P.InertialXrefm_Value;

    /* Constant: '<Root>/Inertial Y ref (m)' */
    ARDroneHover_B.InertialYrefm = ARDroneHover_P.InertialYrefm_Value;
  }

  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* DataTypeConversion: '<S1>/Type Conversion1' */
    ARDroneHover_B.TypeConversion1 = rtb_rollAngle;

    /* DataTypeConversion: '<S1>/Type Conversion2' */
    ARDroneHover_B.TypeConversion2 = rtb_pitchAngle;

    /* ManualSwitch: '<Root>/Manual Switch2' incorporates:
     *  Constant: '<Root>/commands disabled'
     *  Constant: '<Root>/commands enabled'
     */
    if (ARDroneHover_P.ManualSwitch2_CurrentSetting == 1) {
      ARDroneHover_B.ManualSwitch2 = ARDroneHover_P.commandsdisabled_Value;
    } else {
      ARDroneHover_B.ManualSwitch2 = ARDroneHover_P.commandsenabled_Value;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch2' */

    /* MATLAB Function: '<S1>/This block sets the heading angle to zero when the  commands from the Simulink controller are enabled. ' incorporates:
     *  DataTypeConversion: '<S1>/Type Conversion3'
     *  UnitDelay: '<S1>/Unit Delay to avoid algebraic loop'
     */
    /* MATLAB Function 'ARDrone Wi-Fi  Block/This block sets the heading angle to zero when the  commands from the Simulink controller are enabled. ': '<S8>:1' */
    /*  Description: This function zeroes out the heading angle once the commands */
    /*  are enabled.  */
    /* '<S8>:1:6' */
    ARDroneHover_B.yawOut = rtb_yawAngle;
    if ((ARDroneHover_DW.UnitDelaytoavoidalgebraicloop_DSTATE == 1.0) &&
        (ARDroneHover_B.ManualSwitch2 == 1.0)) {
      /* '<S8>:1:19' */
      /* '<S8>:1:20' */
      ARDroneHover_B.yawOut = rtb_yawAngle - ARDroneHover_DW.yaw0;

      /* '<S8>:1:21' */
      ARDroneHover_DW.mode = 1.0;
    } else {
      if ((ARDroneHover_DW.UnitDelaytoavoidalgebraicloop_DSTATE == 1.0) &&
          (ARDroneHover_DW.mode == 0.0)) {
        /* '<S8>:1:22' */
        /* '<S8>:1:23' */
        ARDroneHover_DW.yaw0 = rtb_yawAngle;
      }
    }

    /* '<S8>:1:27' */
    ARDroneHover_B.yawOut -= floor(ARDroneHover_B.yawOut / 360.0) * 360.0;
    if (ARDroneHover_B.yawOut > 180.0) {
      /* '<S8>:1:28' */
      /* '<S8>:1:29' */
      ARDroneHover_B.yawOut += -360.0;
    }

    /* End of MATLAB Function: '<S1>/This block sets the heading angle to zero when the  commands from the Simulink controller are enabled. ' */

    /* Gain: '<Root>/deg 2 rad' */
    ARDroneHover_B.deg2rad[0] = ARDroneHover_P.deg2rad_Gain *
      ARDroneHover_B.TypeConversion1;
    ARDroneHover_B.deg2rad[1] = ARDroneHover_P.deg2rad_Gain *
      ARDroneHover_B.TypeConversion2;
    ARDroneHover_B.deg2rad[2] = ARDroneHover_P.deg2rad_Gain *
      ARDroneHover_B.yawOut;
  }

  /* Sum: '<S15>/Sum4' incorporates:
   *  MATLAB Function: '<S15>/Coordinate trnasformation  from inertial frame to body frame '
   */
  /* MATLAB Function 'Baseline Controller/Position controller/Coordinate trnasformation  from inertial frame to body frame ': '<S16>:1' */
  /* '<S16>:1:3' */
  /* '<S16>:1:4' */
  bytesToRead = ARDroneHover_B.InertialXrefm - ARDroneHover_B.Integrator[0];
  unnamed_idx = ARDroneHover_B.InertialYrefm - ARDroneHover_B.Integrator[1];

  /* Gain: '<S14>/Gain1' incorporates:
   *  Gain: '<S15>/Gain3'
   *  MATLAB Function: '<S15>/Coordinate trnasformation  from inertial frame to body frame '
   *  Sum: '<S14>/Sum5'
   */
  rtb_Saturation1 = ((-sin(ARDroneHover_B.deg2rad[2]) * bytesToRead + cos
                      (ARDroneHover_B.deg2rad[2]) * unnamed_idx) *
                     ARDroneHover_P.Gain3_Gain - ARDroneHover_B.TypeConversion6)
    * ARDroneHover_P.Gain1_Gain;

  /* Saturate: '<S1>/Saturation 1' */
  if (rtb_Saturation1 >= ARDroneHover_P.Saturation1_UpperSat) {
    rtb_Saturation1 = ARDroneHover_P.Saturation1_UpperSat;
  } else {
    if (rtb_Saturation1 <= ARDroneHover_P.Saturation1_LowerSat) {
      rtb_Saturation1 = ARDroneHover_P.Saturation1_LowerSat;
    }
  }

  /* End of Saturate: '<S1>/Saturation 1' */
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* DataTypeConversion: '<S1>/Type Conversion5' */
    ARDroneHover_B.TypeConversion5 = rtb_u;
  }

  /* Gain: '<S11>/Gain' incorporates:
   *  Gain: '<S15>/Gain2'
   *  MATLAB Function: '<S15>/Coordinate trnasformation  from inertial frame to body frame '
   *  Sum: '<S11>/Sum2'
   */
  rtb_Saturation2 = ((cos(ARDroneHover_B.deg2rad[2]) * bytesToRead + sin
                      (ARDroneHover_B.deg2rad[2]) * unnamed_idx) *
                     ARDroneHover_P.Gain2_Gain - ARDroneHover_B.TypeConversion5)
    * ARDroneHover_P.Gain_Gain;

  /* Saturate: '<S1>/Saturation 2' */
  if (rtb_Saturation2 >= ARDroneHover_P.Saturation2_UpperSat) {
    rtb_Saturation2 = ARDroneHover_P.Saturation2_UpperSat;
  } else {
    if (rtb_Saturation2 <= ARDroneHover_P.Saturation2_LowerSat) {
      rtb_Saturation2 = ARDroneHover_P.Saturation2_LowerSat;
    }
  }

  /* End of Saturate: '<S1>/Saturation 2' */
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* Gain: '<S12>/proportional control gain - yaw' incorporates:
     *  Constant: '<Root>/Heading ref (rad)'
     *  Sum: '<S12>/Sum1'
     */
    bytesToRead = (ARDroneHover_P.Headingrefrad_Value - ARDroneHover_B.deg2rad[2])
      * ARDroneHover_P.proportionalcontrolgainyaw_Gain;

    /* Saturate: '<S1>/Saturation 3' */
    if (bytesToRead >= ARDroneHover_P.Saturation3_UpperSat) {
      ARDroneHover_B.Saturation3 = ARDroneHover_P.Saturation3_UpperSat;
    } else if (bytesToRead <= ARDroneHover_P.Saturation3_LowerSat) {
      ARDroneHover_B.Saturation3 = ARDroneHover_P.Saturation3_LowerSat;
    } else {
      ARDroneHover_B.Saturation3 = bytesToRead;
    }

    /* End of Saturate: '<S1>/Saturation 3' */

    /* DataTypeConversion: '<S1>/Type Conversion4' */
    ARDroneHover_B.TypeConversion4 = rtb_height;

    /* Gain: '<S13>/proportional control gain' incorporates:
     *  Constant: '<Root>/Height ref (m)'
     *  Sum: '<S13>/Sum3'
     */
    bytesToRead = (ARDroneHover_P.Heightrefm_Value -
                   ARDroneHover_B.TypeConversion4) *
      ARDroneHover_P.proportionalcontrolgain_Gain;

    /* Saturate: '<S1>/Saturation 4' */
    if (bytesToRead >= ARDroneHover_P.Saturation4_UpperSat) {
      ARDroneHover_B.Saturation4 = ARDroneHover_P.Saturation4_UpperSat;
    } else if (bytesToRead <= ARDroneHover_P.Saturation4_LowerSat) {
      ARDroneHover_B.Saturation4 = ARDroneHover_P.Saturation4_LowerSat;
    } else {
      ARDroneHover_B.Saturation4 = bytesToRead;
    }

    /* End of Saturate: '<S1>/Saturation 4' */

    /* ManualSwitch: '<Root>/Manual Switch' incorporates:
     *  Constant: '<Root>/_'
     *  Constant: '<Root>/stop'
     */
    if (ARDroneHover_P.ManualSwitch_CurrentSetting == 1) {
      ARDroneHover_B.ManualSwitch = ARDroneHover_P._Value;
    } else {
      ARDroneHover_B.ManualSwitch = ARDroneHover_P.stop_Value;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch' */
  }

  /* MATLAB Function: '<S7>/Drone state request' */
  unnamed_idx = ARDroneHover_B.Saturation3;
  bytesToRead = ARDroneHover_B.Saturation4;

  /* MATLAB Function 'ARDrone Wi-Fi  Block/Subsystem1/Drone state request': '<S9>:1' */
  /* '<S9>:1:26' */
  /* '<S9>:1:32' */
  /* '<S9>:1:38' */
  /* '<S9>:1:42' */
  /* '<S9>:1:51' */
  /* '<S9>:1:54' */
  /* '<S9>:1:65' */
  /* '<S9>:1:72' */
  /* '<S9>:1:113' */
  /*  Persistent variables. */
  /*  Initialization of persistent variables at first time step.  */
  /*  Error code / No error: 0 */
  /* '<S9>:1:16' */
  /*  Boolean of flying status / Flying: 1 */
  /* '<S9>:1:19' */
  ARDroneHover_B.isFlying = ARDroneHover_B.status[31];

  /*  Byte array of size 150 to be sent to the drone. */
  /* '<S9>:1:22' */
  memset(&ARDroneHover_B.dataControl[0], 0, 150U * sizeof(uint8_T));

  /*  String that coontains a variable size command.  */
  /*  cmd is concatenated with previous commands at each sample */
  /* '<S9>:1:26' */
  b_hex_sizes_idx = 0;

  /*  At first time step and every 100 time steps, data is requested. */
  if ((ARDroneHover_DW.SequenceNumber <= 1.0) || (ARDroneHover_DW.SequenceNumber
       - floor(ARDroneHover_DW.SequenceNumber / 100.0) * 100.0 == 0.0)) {
    /* '<S9>:1:29' */
    /* '<S9>:1:30' */
    ARDroneHover_DW.SequenceNumber++;

    /* '<S9>:1:31' */
    /* '<S9>:1:32' */
    ARDroneHover_getString(ARDroneHover_DW.SequenceNumber, strCmd_data,
      hex_sizes);
    b_hex_sizes_idx = 41 + hex_sizes[1];
    for (i_1 = 0; i_1 < 10; i_1++) {
      cmd_data[i_1] = d[i_1];
    }

    loop_ub = hex_sizes[0] * hex_sizes[1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      cmd_data[i_1 + 10] = strCmd_data[i_1];
    }

    for (i_1 = 0; i_1 < 30; i_1++) {
      cmd_data[(i_1 + hex_sizes[0] * hex_sizes[1]) + 10] = c[i_1];
    }

    cmd_data[40 + hex_sizes[0] * hex_sizes[1]] = '\x0d';
  }

  /* '<S9>:1:36' */
  ARDroneHover_DW.SequenceNumber++;

  /* '<S9>:1:37' */
  ARDroneHover_getString(ARDroneHover_DW.SequenceNumber, strCmd_data, hex_sizes);

  /* '<S9>:1:38' */
  i_0 = b_hex_sizes_idx + 10;
  loop_ub_0 = hex_sizes[1];
  b_hex_sizes_idx = (i_0 + hex_sizes[1]) + 1;
  for (i_1 = 0; i_1 < 10; i_1++) {
    /* MATLAB Function: '<S7>/Drone state request' */
    cmd_data[(i_0 + i_1) - 10] = m[i_1];
  }

  for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
    cmd_data[i_0 + i_1] = strCmd_data[i_1];
  }

  /* MATLAB Function: '<S7>/Drone state request' */
  cmd_data[i_0 + hex_sizes[1]] = '\x0d';
  if (ARDroneHover_B.ManualSwitch == 1.0) {
    /* '<S9>:1:41' */
    /*  Emergency stop */
    /* '<S9>:1:42' */
    b_hex_sizes_idx = 18 + hex_sizes[1];
    for (i_1 = 0; i_1 < 7; i_1++) {
      cmd_data[i_1] = f[i_1];
    }

    loop_ub = hex_sizes[0] * hex_sizes[1];
    for (i_1 = 0; i_1 < loop_ub; i_1++) {
      cmd_data[i_1 + 7] = strCmd_data[i_1];
    }

    for (i_1 = 0; i_1 < 10; i_1++) {
      cmd_data[(i_1 + hex_sizes[0] * hex_sizes[1]) + 7] = e[i_1];
    }

    cmd_data[17 + hex_sizes[0] * hex_sizes[1]] = '\x0d';
  } else {
    /*  Not emergency stop */
    if ((ARDroneHover_DW.SequenceNumber > 20.0) &&
        (ARDroneHover_DW.SequenceNumber < 22.0)) {
      /* '<S9>:1:46' */
      /*  Trim vehicle state estimation / angles set to zero */
      /* '<S9>:1:49' */
      ARDroneHover_DW.SequenceNumber = 22.0;

      /* '<S9>:1:50' */
      /* '<S9>:1:51' */
      ARDroneHover_getString(22.0, strCmd_data, hex_sizes);
      loop_ub_1 = (b_hex_sizes_idx + hex_sizes[1]) + 10;
      for (i_1 = 0; i_1 < b_hex_sizes_idx; i_1++) {
        cmd_data_0[i_1] = cmd_data[i_1];
      }

      for (i_1 = 0; i_1 < 9; i_1++) {
        cmd_data_0[i_1 + b_hex_sizes_idx] = g[i_1];
      }

      loop_ub = hex_sizes[1];
      for (i_1 = 0; i_1 < loop_ub; i_1++) {
        cmd_data_0[(i_1 + b_hex_sizes_idx) + 9] = strCmd_data[hex_sizes[0] * i_1];
      }

      cmd_data_0[(b_hex_sizes_idx + hex_sizes[1]) + 9] = '\x0d';
      b_hex_sizes_idx = loop_ub_1;
      for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
        cmd_data[i_1] = cmd_data_0[i_1];
      }
    } else if ((ARDroneHover_DW.SequenceNumber >= 22.0) &&
               (ARDroneHover_DW.SequenceNumber < 25.0)) {
      /* '<S9>:1:53' */
      /* '<S9>:1:54' */
      i_0 = b_hex_sizes_idx + 10;
      loop_ub_0 = hex_sizes[1];
      b_hex_sizes_idx = (i_0 + hex_sizes[1]) + 31;
      for (i_1 = 0; i_1 < 10; i_1++) {
        cmd_data[(i_0 + i_1) - 10] = d[i_1];
      }

      for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
        cmd_data[i_0 + i_1] = strCmd_data[i_1];
      }

      for (i_1 = 0; i_1 < 30; i_1++) {
        cmd_data[(i_0 + i_1) + hex_sizes[1]] = h[i_1];
      }

      cmd_data[(i_0 + hex_sizes[1]) + 30] = '\x0d';
    } else {
      if (ARDroneHover_DW.SequenceNumber >= 25.0) {
        /* '<S9>:1:57' */
        if (ARDroneHover_B.ManualSwitch1 == 1.0) {
          /* '<S9>:1:59' */
          if (ARDroneHover_B.status[31] == 0.0) {
            /* '<S9>:1:61' */
            /* '<S9>:1:63' */
            ARDroneHover_DW.SequenceNumber++;

            /* '<S9>:1:64' */
            /* '<S9>:1:65' */
            ARDroneHover_getString(ARDroneHover_DW.SequenceNumber, strCmd_data,
              hex_sizes);
            loop_ub_1 = (b_hex_sizes_idx + hex_sizes[1]) + 18;
            for (i_1 = 0; i_1 < b_hex_sizes_idx; i_1++) {
              cmd_data_0[i_1] = cmd_data[i_1];
            }

            for (i_1 = 0; i_1 < 7; i_1++) {
              cmd_data_0[i_1 + b_hex_sizes_idx] = f[i_1];
            }

            loop_ub = hex_sizes[1];
            for (i_1 = 0; i_1 < loop_ub; i_1++) {
              cmd_data_0[(i_1 + b_hex_sizes_idx) + 7] = strCmd_data[hex_sizes[0]
                * i_1];
            }

            for (i_1 = 0; i_1 < 10; i_1++) {
              cmd_data_0[((i_1 + b_hex_sizes_idx) + hex_sizes[1]) + 7] = i[i_1];
            }

            cmd_data_0[(b_hex_sizes_idx + hex_sizes[1]) + 17] = '\x0d';
            b_hex_sizes_idx = loop_ub_1;
            for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
              cmd_data[i_1] = cmd_data_0[i_1];
            }
          } else {
            if ((ARDroneHover_B.status[31] == 1.0) &&
                (ARDroneHover_B.ManualSwitch2 == 1.0)) {
              /* '<S9>:1:67' */
              /* '<S9>:1:69' */
              ARDroneHover_DW.SequenceNumber++;

              /* '<S9>:1:70' */
              /* '<S9>:1:72' */
              ARDroneHover_getString(ARDroneHover_DW.SequenceNumber, strCmd_data,
                hex_sizes);
              loop_ub_1 = (b_hex_sizes_idx + hex_sizes[1]) + 11;
              for (i_1 = 0; i_1 < b_hex_sizes_idx; i_1++) {
                cmd_data_0[i_1] = cmd_data[i_1];
              }

              for (i_1 = 0; i_1 < 8; i_1++) {
                cmd_data_0[i_1 + b_hex_sizes_idx] = k[i_1];
              }

              loop_ub = hex_sizes[1];
              for (i_1 = 0; i_1 < loop_ub; i_1++) {
                cmd_data_0[(i_1 + b_hex_sizes_idx) + 8] = strCmd_data[hex_sizes
                  [0] * i_1];
              }

              cmd_data_0[(b_hex_sizes_idx + hex_sizes[1]) + 8] = ',';
              cmd_data_0[(b_hex_sizes_idx + hex_sizes[1]) + 9] = '1';
              cmd_data_0[(b_hex_sizes_idx + hex_sizes[1]) + 10] = ',';
              for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
                cmd_data[i_1] = cmd_data_0[i_1];
              }

              /* '<S9>:1:74' */
              aux = ARDroneHover_float2IEEE754(rtb_Saturation1);

              /* '<S9>:1:75' */
              ARDroneHover_getString(fabs(aux), strCmd_data, hex_sizes);
              if (rtb_Saturation1 < 0.0) {
                /* '<S9>:1:76' */
                /* '<S9>:1:77' */
                i_0 = 1 + hex_sizes[1];
                tmp_data[0] = '-';
                loop_ub = hex_sizes[1];
                for (i_1 = 0; i_1 < loop_ub; i_1++) {
                  tmp_data[i_1 + 1] = strCmd_data[hex_sizes[0] * i_1];
                }

                hex_sizes[1] = i_0;
                for (i_1 = 0; i_1 < i_0; i_1++) {
                  strCmd_data[i_1] = tmp_data[i_1];
                }
              }

              /* '<S9>:1:79' */
              loop_ub_0 = hex_sizes[1];
              b_hex_sizes_idx = (loop_ub_1 + hex_sizes[1]) + 1;
              for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
                cmd_data[loop_ub_1 + i_1] = strCmd_data[i_1];
              }

              cmd_data[loop_ub_1 + hex_sizes[1]] = ',';

              /* '<S9>:1:81' */
              aux = ARDroneHover_float2IEEE754(rtb_Saturation2);

              /* '<S9>:1:82' */
              ARDroneHover_getString(fabs(aux), strCmd_data, hex_sizes);
              if (rtb_Saturation2 < 0.0) {
                /* '<S9>:1:83' */
                /* '<S9>:1:84' */
                i_0 = 1 + hex_sizes[1];
                tmp_data[0] = '-';
                loop_ub = hex_sizes[1];
                for (i_1 = 0; i_1 < loop_ub; i_1++) {
                  tmp_data[i_1 + 1] = strCmd_data[hex_sizes[0] * i_1];
                }

                hex_sizes[1] = i_0;
                for (i_1 = 0; i_1 < i_0; i_1++) {
                  strCmd_data[i_1] = tmp_data[i_1];
                }
              }

              /* '<S9>:1:86' */
              i_0 = b_hex_sizes_idx;
              loop_ub_0 = hex_sizes[1];
              b_hex_sizes_idx = (b_hex_sizes_idx + hex_sizes[1]) + 1;
              for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
                cmd_data[i_0 + i_1] = strCmd_data[i_1];
              }

              cmd_data[i_0 + hex_sizes[1]] = ',';

              /* '<S9>:1:88' */
              aux = ARDroneHover_float2IEEE754(bytesToRead);

              /* '<S9>:1:89' */
              ARDroneHover_getString(fabs(aux), strCmd_data, hex_sizes);
              if (bytesToRead < 0.0) {
                /* '<S9>:1:90' */
                /* '<S9>:1:91' */
                i_0 = 1 + hex_sizes[1];
                tmp_data[0] = '-';
                loop_ub = hex_sizes[1];
                for (i_1 = 0; i_1 < loop_ub; i_1++) {
                  tmp_data[i_1 + 1] = strCmd_data[hex_sizes[0] * i_1];
                }

                hex_sizes[1] = i_0;
                for (i_1 = 0; i_1 < i_0; i_1++) {
                  strCmd_data[i_1] = tmp_data[i_1];
                }
              }

              /* '<S9>:1:93' */
              i_0 = b_hex_sizes_idx;
              loop_ub_0 = hex_sizes[1];
              b_hex_sizes_idx = (b_hex_sizes_idx + hex_sizes[1]) + 1;
              for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
                cmd_data[i_0 + i_1] = strCmd_data[i_1];
              }

              cmd_data[i_0 + hex_sizes[1]] = ',';

              /* '<S9>:1:96' */
              aux = ARDroneHover_float2IEEE754(unnamed_idx);

              /* '<S9>:1:97' */
              ARDroneHover_getString(fabs(aux), strCmd_data, hex_sizes);
              if (unnamed_idx < 0.0) {
                /* '<S9>:1:98' */
                /* '<S9>:1:99' */
                /* '<S9>:1:100' */
                i_0 = 1 + hex_sizes[1];
                tmp_data[0] = '-';
                loop_ub = hex_sizes[1];
                for (i_1 = 0; i_1 < loop_ub; i_1++) {
                  tmp_data[i_1 + 1] = strCmd_data[hex_sizes[0] * i_1];
                }

                hex_sizes[1] = i_0;
                for (i_1 = 0; i_1 < i_0; i_1++) {
                  strCmd_data[i_1] = tmp_data[i_1];
                }
              }

              /* '<S9>:1:102' */
              i_0 = b_hex_sizes_idx;
              loop_ub_0 = hex_sizes[1];
              b_hex_sizes_idx = (b_hex_sizes_idx + hex_sizes[1]) + 1;
              for (i_1 = 0; i_1 < loop_ub_0; i_1++) {
                cmd_data[i_0 + i_1] = strCmd_data[i_1];
              }

              cmd_data[i_0 + hex_sizes[1]] = '\x0d';
            }
          }
        } else {
          if ((ARDroneHover_B.ManualSwitch1 == 0.0) && (ARDroneHover_B.status[31]
               == 1.0)) {
            /* '<S9>:1:108' */
            /* '<S9>:1:110' */
            /* '<S9>:1:111' */
            ARDroneHover_DW.SequenceNumber++;

            /* '<S9>:1:112' */
            /* '<S9>:1:113' */
            ARDroneHover_getString(ARDroneHover_DW.SequenceNumber, strCmd_data,
              hex_sizes);
            loop_ub_1 = (b_hex_sizes_idx + hex_sizes[1]) + 18;
            for (i_1 = 0; i_1 < b_hex_sizes_idx; i_1++) {
              cmd_data_0[i_1] = cmd_data[i_1];
            }

            for (i_1 = 0; i_1 < 7; i_1++) {
              cmd_data_0[i_1 + b_hex_sizes_idx] = f[i_1];
            }

            loop_ub = hex_sizes[1];
            for (i_1 = 0; i_1 < loop_ub; i_1++) {
              cmd_data_0[(i_1 + b_hex_sizes_idx) + 7] = strCmd_data[hex_sizes[0]
                * i_1];
            }

            for (i_1 = 0; i_1 < 10; i_1++) {
              cmd_data_0[((i_1 + b_hex_sizes_idx) + hex_sizes[1]) + 7] = l[i_1];
            }

            cmd_data_0[(b_hex_sizes_idx + hex_sizes[1]) + 17] = '\x0d';
            b_hex_sizes_idx = loop_ub_1;
            for (i_1 = 0; i_1 < loop_ub_1; i_1++) {
              cmd_data[i_1] = cmd_data_0[i_1];
            }
          }
        }
      }
    }
  }

  /*  cmd must contain less than 150 bytes.  */
  /* '<S9>:1:126' */
  loop_ub = b_hex_sizes_idx - 1;
  for (i_1 = 0; i_1 <= loop_ub; i_1++) {
    tmp_data_0[i_1] = 1 + i_1;
  }

  for (i_1 = 0; i_1 < b_hex_sizes_idx; i_1++) {
    ARDroneHover_B.dataControl[tmp_data_0[i_1] - 1] = (uint8_T)cmd_data[i_1];
  }

  /* '<S9>:1:131' */
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* DataTypeConversion: '<S1>/Type Conversion' */
    ARDroneHover_B.TypeConversion = rtb_battery;

    /* DataTypeConversion: '<S1>/Type Conversion7' */
    ARDroneHover_B.TypeConversion7 = rtb_w;

    /* SignalConversion: '<S4>/TmpSignal ConversionAtTo WorkspaceInport1' */
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[0] =
      ARDroneHover_B.deg2rad[0];
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[1] =
      ARDroneHover_B.deg2rad[1];
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[2] =
      ARDroneHover_B.deg2rad[2];
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[3] =
      ARDroneHover_B.TypeConversion5;
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[4] =
      ARDroneHover_B.TypeConversion6;
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[5] =
      ARDroneHover_B.TypeConversion7;
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[6] =
      ARDroneHover_B.Integrator[0];
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[7] =
      ARDroneHover_B.Integrator[1];
    ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[8] =
      ARDroneHover_B.TypeConversion4;

    /* Gain: '<S4>/deg 2 rad1' */
    ARDroneHover_B.deg2rad1 = ARDroneHover_P.deg2rad1_Gain *
      ARDroneHover_B.deg2rad[2];

    /* MATLAB Function: '<S17>/Velocity from vehicle body frame  to inertial NED  frame' incorporates:
     *  SignalConversion: '<S18>/TmpSignal ConversionAt SFunction Inport1'
     */
    /* MATLAB Function 'Position estimation Important:This block provides an  inaccurate extimation of position  based on  velocity information. /Position estimation/Velocity from vehicle body frame  to inertial NED  frame': '<S18>:1' */
    /* '<S18>:1:3' */
    /* '<S18>:1:4' */
    ARDroneHover_B.Vel_xy[0] = 0.0;
    ARDroneHover_B.Vel_xy[0] += cos(ARDroneHover_B.deg2rad[2]) *
      ARDroneHover_B.TypeConversion5;
    ARDroneHover_B.Vel_xy[0] += -sin(ARDroneHover_B.deg2rad[2]) *
      ARDroneHover_B.TypeConversion6;
    ARDroneHover_B.Vel_xy[1] = 0.0;
    ARDroneHover_B.Vel_xy[1] += sin(ARDroneHover_B.deg2rad[2]) *
      ARDroneHover_B.TypeConversion5;
    ARDroneHover_B.Vel_xy[1] += cos(ARDroneHover_B.deg2rad[2]) *
      ARDroneHover_B.TypeConversion6;
  }

  /* Clock: '<Root>/Clock1' */
  ARDroneHover_B.Clock1 = ARDroneHover_M->Timing.t[0];
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
  }
}

/* Model update function for TID0 */
void ARDroneHover_update0(void)        /* Sample time: [0.0s, 0.0s] */
{
  /* S-Function Block: <S7>/Packet Output */
  {
    uint8_T outdata[150U];
    RTWin_ANYTYPEPTR outdp;
    outdp.p_uint8_T = outdata;

    {
      int_T i1;
      const uint8_T *u0 = ARDroneHover_B.dataControl;
      for (i1=0; i1 < 150; i1++) {
        {
          uint8_T pktout = u0[i1];
          *outdp.p_uint8_T++ = pktout;
        }
      }
    }

    RTBIO_DriverIO(0, STREAMOUTPUT, IOWRITE, 150U,
                   &ARDroneHover_P.PacketOutput_PacketID, (double*) outdata,
                   NULL);
  }

  /* Update for Integrator: '<S17>/Integrator' */
  ARDroneHover_DW.Integrator_IWORK.IcNeedsLoading = 0;
  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    /* Update for UnitDelay: '<S1>/Unit Delay to avoid algebraic loop' */
    ARDroneHover_DW.UnitDelaytoavoidalgebraicloop_DSTATE =
      ARDroneHover_B.isFlying;
  }

  if (rtmIsMajorTimeStep(ARDroneHover_M)) {
    rt_ertODEUpdateContinuousStates(&ARDroneHover_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ARDroneHover_M->Timing.clockTick0)) {
    ++ARDroneHover_M->Timing.clockTickH0;
  }

  ARDroneHover_M->Timing.t[0] = rtsiGetSolverStopTime
    (&ARDroneHover_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ARDroneHover_M->Timing.clockTick1)) {
    ++ARDroneHover_M->Timing.clockTickH1;
  }

  ARDroneHover_M->Timing.t[1] = ARDroneHover_M->Timing.clockTick1 *
    ARDroneHover_M->Timing.stepSize1 + ARDroneHover_M->Timing.clockTickH1 *
    ARDroneHover_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void ARDroneHover_derivatives(void)
{
  /* Derivatives for Integrator: '<S17>/Integrator' */
  {
    ((XDot_ARDroneHover_T *) ARDroneHover_M->ModelData.derivs)
      ->Integrator_CSTATE[0] = ARDroneHover_B.Vel_xy[0];
    ((XDot_ARDroneHover_T *) ARDroneHover_M->ModelData.derivs)
      ->Integrator_CSTATE[1] = ARDroneHover_B.Vel_xy[1];
  }
}

/* Model output function for TID2 */
void ARDroneHover_output2(void)        /* Sample time: [0.65s, 0.0s] */
{
  /* S-Function Block: <S10>/Packet Output1 */

  /* no code required */
}

/* Model update function for TID2 */
void ARDroneHover_update2(void)        /* Sample time: [0.65s, 0.0s] */
{
  /* S-Function Block: <S10>/Packet Output1 */
  {
    uint8_T outdata[2U];
    RTWin_ANYTYPEPTR outdp;
    outdp.p_uint8_T = outdata;

    {
      uint8_T pktout = (ARDroneHover_P.Constant_Value[0]);
      *outdp.p_uint8_T++ = pktout;
    }

    {
      uint8_T pktout = (ARDroneHover_P.Constant_Value[1]);
      *outdp.p_uint8_T++ = pktout;
    }

    RTBIO_DriverIO(1, STREAMOUTPUT, IOWRITE, 2U,
                   &ARDroneHover_P.PacketOutput1_PacketID, (double*) outdata,
                   NULL);
  }

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ARDroneHover_M->Timing.clockTick2)) {
    ++ARDroneHover_M->Timing.clockTickH2;
  }

  ARDroneHover_M->Timing.t[2] = ARDroneHover_M->Timing.clockTick2 *
    ARDroneHover_M->Timing.stepSize2 + ARDroneHover_M->Timing.clockTickH2 *
    ARDroneHover_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void ARDroneHover_output(int_T tid)
{
  switch (tid) {
   case 0 :
    ARDroneHover_output0();
    break;

   case 2 :
    ARDroneHover_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void ARDroneHover_update(int_T tid)
{
  switch (tid) {
   case 0 :
    ARDroneHover_update0();
    break;

   case 2 :
    ARDroneHover_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void ARDroneHover_initialize(void)
{
  /* S-Function Block: <S7>/Packet Output */
  /* no initial value should be set */

  /* S-Function Block: <S10>/Packet Output1 */
  /* no initial value should be set */

  /* Start for Constant: '<S17>/Constant1' */
  ARDroneHover_B.Constant1[0] = ARDroneHover_P.Constant1_Value[0];
  ARDroneHover_B.Constant1[1] = ARDroneHover_P.Constant1_Value[1];

  {
    int32_T i;

    /* InitializeConditions for MATLAB Function: '<S1>/Data synchronization ' */
    for (i = 0; i < 496; i++) {
      ARDroneHover_DW.frame[i] = 0U;
      ARDroneHover_DW.lastFrame[i] = 0U;
    }

    ARDroneHover_DW.count = 0.0;
    ARDroneHover_DW.countHeader = 0.0;
    ARDroneHover_DW.countBuffer = 0.0;
    memset(&ARDroneHover_DW.buffer[0], 0, sizeof(uint8_T) << 10U);

    /* End of InitializeConditions for MATLAB Function: '<S1>/Data synchronization ' */

    /* InitializeConditions for MATLAB Function: '<S1>/ARDrone data decoding' */
    ARDroneHover_DW.hPrev = 0.0;
    memset(&ARDroneHover_DW.dataPrev[0], 0, 496U * sizeof(uint8_T));

    /* InitializeConditions for Integrator: '<S17>/Integrator' */
    if (rtmIsFirstInitCond(ARDroneHover_M)) {
      ARDroneHover_X.Integrator_CSTATE[0] = 0.0;
      ARDroneHover_X.Integrator_CSTATE[1] = 0.0;
    }

    ARDroneHover_DW.Integrator_IWORK.IcNeedsLoading = 1;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay to avoid algebraic loop' */
    ARDroneHover_DW.UnitDelaytoavoidalgebraicloop_DSTATE =
      ARDroneHover_P.UnitDelaytoavoidalgebraicloop_InitialCondition;

    /* InitializeConditions for MATLAB Function: '<S1>/This block sets the heading angle to zero when the  commands from the Simulink controller are enabled. ' */
    ARDroneHover_DW.yaw0 = 0.0;
    ARDroneHover_DW.mode = 0.0;

    /* InitializeConditions for MATLAB Function: '<S7>/Drone state request' */
    ARDroneHover_DW.SequenceNumber = 1.0;

    /* set "at time zero" to false */
    if (rtmIsFirstInitCond(ARDroneHover_M)) {
      rtmSetFirstInitCond(ARDroneHover_M, 0);
    }
  }
}

/* Model terminate function */
void ARDroneHover_terminate(void)
{
  /* S-Function Block: <S7>/Packet Output */
  /* no initial value should be set */

  /* S-Function Block: <S10>/Packet Output1 */
  /* no initial value should be set */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  ARDroneHover_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  ARDroneHover_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  ARDroneHover_initialize();
}

void MdlTerminate(void)
{
  ARDroneHover_terminate();
}

/* Registration function */
RT_MODEL_ARDroneHover_T *ARDroneHover(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ARDroneHover_M, 0,
                sizeof(RT_MODEL_ARDroneHover_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ARDroneHover_M->solverInfo,
                          &ARDroneHover_M->Timing.simTimeStep);
    rtsiSetTPtr(&ARDroneHover_M->solverInfo, &rtmGetTPtr(ARDroneHover_M));
    rtsiSetStepSizePtr(&ARDroneHover_M->solverInfo,
                       &ARDroneHover_M->Timing.stepSize0);
    rtsiSetdXPtr(&ARDroneHover_M->solverInfo, &ARDroneHover_M->ModelData.derivs);
    rtsiSetContStatesPtr(&ARDroneHover_M->solverInfo,
                         &ARDroneHover_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&ARDroneHover_M->solverInfo,
      &ARDroneHover_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&ARDroneHover_M->solverInfo, (&rtmGetErrorStatus
      (ARDroneHover_M)));
    rtsiSetRTModelPtr(&ARDroneHover_M->solverInfo, ARDroneHover_M);
  }

  rtsiSetSimTimeStep(&ARDroneHover_M->solverInfo, MAJOR_TIME_STEP);
  ARDroneHover_M->ModelData.intgData.f[0] = ARDroneHover_M->ModelData.odeF[0];
  ARDroneHover_M->ModelData.contStates = ((real_T *) &ARDroneHover_X);
  rtsiSetSolverData(&ARDroneHover_M->solverInfo, (void *)
                    &ARDroneHover_M->ModelData.intgData);
  rtsiSetSolverName(&ARDroneHover_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ARDroneHover_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    ARDroneHover_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ARDroneHover_M->Timing.sampleTimes =
      (&ARDroneHover_M->Timing.sampleTimesArray[0]);
    ARDroneHover_M->Timing.offsetTimes =
      (&ARDroneHover_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ARDroneHover_M->Timing.sampleTimes[0] = (0.0);
    ARDroneHover_M->Timing.sampleTimes[1] = (0.065);
    ARDroneHover_M->Timing.sampleTimes[2] = (0.65);

    /* task offsets */
    ARDroneHover_M->Timing.offsetTimes[0] = (0.0);
    ARDroneHover_M->Timing.offsetTimes[1] = (0.0);
    ARDroneHover_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(ARDroneHover_M, &ARDroneHover_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ARDroneHover_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = ARDroneHover_M->Timing.perTaskSampleHitsArray;
    ARDroneHover_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    ARDroneHover_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ARDroneHover_M, -1);
  ARDroneHover_M->Timing.stepSize0 = 0.065;
  ARDroneHover_M->Timing.stepSize1 = 0.065;
  ARDroneHover_M->Timing.stepSize2 = 0.65;
  rtmSetFirstInitCond(ARDroneHover_M, 1);

  /* External mode info */
  ARDroneHover_M->Sizes.checksums[0] = (1775794353U);
  ARDroneHover_M->Sizes.checksums[1] = (1537477494U);
  ARDroneHover_M->Sizes.checksums[2] = (1787961229U);
  ARDroneHover_M->Sizes.checksums[3] = (34757474U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    ARDroneHover_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ARDroneHover_M->extModeInfo,
      &ARDroneHover_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(ARDroneHover_M->extModeInfo,
                        ARDroneHover_M->Sizes.checksums);
    rteiSetTPtr(ARDroneHover_M->extModeInfo, rtmGetTPtr(ARDroneHover_M));
  }

  ARDroneHover_M->solverInfoPtr = (&ARDroneHover_M->solverInfo);
  ARDroneHover_M->Timing.stepSize = (0.065);
  rtsiSetFixedStepSize(&ARDroneHover_M->solverInfo, 0.065);
  rtsiSetSolverMode(&ARDroneHover_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  ARDroneHover_M->ModelData.blockIO = ((void *) &ARDroneHover_B);
  (void) memset(((void *) &ARDroneHover_B), 0,
                sizeof(B_ARDroneHover_T));

  {
    int_T i;
    for (i = 0; i < 9; i++) {
      ARDroneHover_B.TmpSignalConversionAtToWorkspaceInport1[i] = 0.0;
    }

    for (i = 0; i < 32; i++) {
      ARDroneHover_B.status[i] = 0.0;
    }

    ARDroneHover_B.ManualSwitch1 = 0.0;
    ARDroneHover_B.TypeConversion6 = 0.0;
    ARDroneHover_B.Constant1[0] = 0.0;
    ARDroneHover_B.Constant1[1] = 0.0;
    ARDroneHover_B.Integrator[0] = 0.0;
    ARDroneHover_B.Integrator[1] = 0.0;
    ARDroneHover_B.InertialXrefm = 0.0;
    ARDroneHover_B.InertialYrefm = 0.0;
    ARDroneHover_B.TypeConversion1 = 0.0;
    ARDroneHover_B.TypeConversion2 = 0.0;
    ARDroneHover_B.ManualSwitch2 = 0.0;
    ARDroneHover_B.deg2rad[0] = 0.0;
    ARDroneHover_B.deg2rad[1] = 0.0;
    ARDroneHover_B.deg2rad[2] = 0.0;
    ARDroneHover_B.TypeConversion5 = 0.0;
    ARDroneHover_B.Saturation3 = 0.0;
    ARDroneHover_B.TypeConversion4 = 0.0;
    ARDroneHover_B.Saturation4 = 0.0;
    ARDroneHover_B.ManualSwitch = 0.0;
    ARDroneHover_B.TypeConversion = 0.0;
    ARDroneHover_B.TypeConversion7 = 0.0;
    ARDroneHover_B.deg2rad1 = 0.0;
    ARDroneHover_B.Clock1 = 0.0;
    ARDroneHover_B.Vel_xy[0] = 0.0;
    ARDroneHover_B.Vel_xy[1] = 0.0;
    ARDroneHover_B.yawOut = 0.0;
    ARDroneHover_B.isFlying = 0.0;
  }

  /* parameters */
  ARDroneHover_M->ModelData.defaultParam = ((real_T *)&ARDroneHover_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &ARDroneHover_X;
    ARDroneHover_M->ModelData.contStates = (x);
    (void) memset((void *)&ARDroneHover_X, 0,
                  sizeof(X_ARDroneHover_T));
  }

  /* states (dwork) */
  ARDroneHover_M->ModelData.dwork = ((void *) &ARDroneHover_DW);
  (void) memset((void *)&ARDroneHover_DW, 0,
                sizeof(DW_ARDroneHover_T));
  ARDroneHover_DW.UnitDelaytoavoidalgebraicloop_DSTATE = 0.0;
  ARDroneHover_DW.yaw0 = 0.0;
  ARDroneHover_DW.mode = 0.0;
  ARDroneHover_DW.SequenceNumber = 0.0;
  ARDroneHover_DW.count = 0.0;
  ARDroneHover_DW.countHeader = 0.0;
  ARDroneHover_DW.countBuffer = 0.0;
  ARDroneHover_DW.hPrev = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    ARDroneHover_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  ARDroneHover_M->Sizes.numContStates = (2);/* Number of continuous states */
  ARDroneHover_M->Sizes.numY = (0);    /* Number of model outputs */
  ARDroneHover_M->Sizes.numU = (0);    /* Number of model inputs */
  ARDroneHover_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  ARDroneHover_M->Sizes.numSampTimes = (3);/* Number of sample times */
  ARDroneHover_M->Sizes.numBlocks = (69);/* Number of blocks */
  ARDroneHover_M->Sizes.numBlockIO = (27);/* Number of block outputs */
  ARDroneHover_M->Sizes.numBlockPrms = (43);/* Sum of parameter "widths" */
  return ARDroneHover_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/