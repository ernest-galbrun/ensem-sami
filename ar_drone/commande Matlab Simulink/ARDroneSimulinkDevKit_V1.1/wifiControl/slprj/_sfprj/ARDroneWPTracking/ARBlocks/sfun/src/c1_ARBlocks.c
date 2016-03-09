/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ARBlocks_sfun.h"
#include "c1_ARBlocks.h"
#include <string.h>
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ARBlocks_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[19] = { "strOut", "cmd", "strCmd",
  "aux", "strAux", "nargin", "nargout", "status", "fly", "rollAngRef",
  "pitchAngRef", "yawRateRef", "wRef", "enableRefs", "stop", "dataControl",
  "isFlying", "error", "SequenceNumber" };

static const char * c1_b_debug_family_names[9] = { "d", "digit", "resTotal", "k",
  "res1", "nargin", "nargout", "a", "strOut" };

static const char * c1_c_debug_family_names[8] = { "binData", "binData2", "k",
  "bit", "iVal", "nargin", "nargout", "fVal" };

/* Function Declarations */
static void initialize_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance);
static void initialize_params_c1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance);
static void enable_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance);
static void disable_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance);
static void set_sim_state_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_st);
static void finalize_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance);
static void sf_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance);
static void c1_chartstep_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance);
static void initSimStructsc1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance);
static void registerMessagesc1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_b_SequenceNumber, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_error, const char_T *c1_identifier);
static real_T c1_d_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_dataControl, const char_T *c1_identifier, uint8_T c1_y[150]);
static void c1_f_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[150]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, char_T
  c1_inData_data[11], int32_T c1_inData_sizes[2]);
static void c1_g_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y_data
  [11], int32_T c1_y_sizes[2]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, char_T c1_outData_data[11],
  int32_T c1_outData_sizes[2]);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, char_T
  c1_inData_data[144], int32_T c1_inData_sizes[2]);
static void c1_h_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y_data
  [144], int32_T c1_y_sizes[2]);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, char_T c1_outData_data[144],
  int32_T c1_outData_sizes[2]);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c1_inData_data[11], int32_T c1_inData_sizes[2]);
static void c1_i_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y_data
  [11], int32_T c1_y_sizes[2]);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, uint8_T c1_outData_data[11],
  int32_T c1_outData_sizes[2]);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_j_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_k_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[32]);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_l_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[32]);
static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[60]);
static real_T c1_mod(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_x,
                     real_T c1_y);
static void c1_eml_scalar_eg(SFc1_ARBlocksInstanceStruct *chartInstance);
static void c1_getString(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_a,
  char_T c1_strOut_data[11], int32_T c1_strOut_sizes[2]);
static real_T c1_mpower(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_a,
  real_T c1_b);
static void c1_char(SFc1_ARBlocksInstanceStruct *chartInstance);
static int32_T c1_float2IEEE754(SFc1_ARBlocksInstanceStruct *chartInstance,
  real_T c1_fVal);
static void c1_eml_error(SFc1_ARBlocksInstanceStruct *chartInstance, uint8_T
  c1_varargin_1);
static real_T c1_abs(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_x);
static void c1_b_char(SFc1_ARBlocksInstanceStruct *chartInstance);
static uint8_T c1_m_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_ARBlocks, const char_T *c1_identifier);
static uint8_T c1_n_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_ARBlocksInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_SequenceNumber_not_empty = FALSE;
  chartInstance->c1_is_active_c1_ARBlocks = 0U;
}

static void initialize_params_c1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void enable_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  uint8_T c1_u[150];
  const mxArray *c1_b_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  uint8_T c1_d_hoistedGlobal;
  uint8_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  real_T *c1_error;
  real_T *c1_isFlying;
  uint8_T (*c1_dataControl)[150];
  c1_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_isFlying = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_dataControl = (uint8_T (*)[150])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(5), FALSE);
  for (c1_i0 = 0; c1_i0 < 150; c1_i0++) {
    c1_u[c1_i0] = (*c1_dataControl)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 3, 0U, 1U, 0U, 1, 150), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = *c1_error;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_b_hoistedGlobal = *c1_isFlying;
  c1_c_u = c1_b_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_c_hoistedGlobal = chartInstance->c1_SequenceNumber;
  c1_d_u = c1_c_hoistedGlobal;
  c1_e_y = NULL;
  if (!chartInstance->c1_SequenceNumber_not_empty) {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_d_hoistedGlobal = chartInstance->c1_is_active_c1_ARBlocks;
  c1_e_u = c1_d_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  uint8_T c1_uv0[150];
  int32_T c1_i1;
  real_T *c1_error;
  real_T *c1_isFlying;
  uint8_T (*c1_dataControl)[150];
  c1_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_isFlying = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_dataControl = (uint8_T (*)[150])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                        "dataControl", c1_uv0);
  for (c1_i1 = 0; c1_i1 < 150; c1_i1++) {
    (*c1_dataControl)[c1_i1] = c1_uv0[c1_i1];
  }

  *c1_error = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 1)), "error");
  *c1_isFlying = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 2)), "isFlying");
  chartInstance->c1_SequenceNumber = c1_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 3)), "SequenceNumber");
  chartInstance->c1_is_active_c1_ARBlocks = c1_m_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 4)), "is_active_c1_ARBlocks");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_ARBlocks(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance)
{
}

static void sf_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  real_T *c1_fly;
  real_T *c1_rollAngRef;
  real_T *c1_pitchAngRef;
  real_T *c1_yawRateRef;
  real_T *c1_wRef;
  real_T *c1_enableRefs;
  real_T *c1_isFlying;
  real_T *c1_stop;
  real_T *c1_error;
  uint8_T (*c1_dataControl)[150];
  real_T (*c1_status)[32];
  c1_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_stop = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c1_isFlying = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_dataControl = (uint8_T (*)[150])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_enableRefs = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_wRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_yawRateRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_pitchAngRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_rollAngRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_fly = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_status = (real_T (*)[32])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 32; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_status)[c1_i2], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_fly, 1U);
  _SFD_DATA_RANGE_CHECK(*c1_rollAngRef, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_pitchAngRef, 3U);
  _SFD_DATA_RANGE_CHECK(*c1_yawRateRef, 4U);
  _SFD_DATA_RANGE_CHECK(*c1_wRef, 5U);
  _SFD_DATA_RANGE_CHECK(*c1_enableRefs, 6U);
  for (c1_i3 = 0; c1_i3 < 150; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c1_dataControl)[c1_i3], 7U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_isFlying, 8U);
  _SFD_DATA_RANGE_CHECK(*c1_stop, 9U);
  _SFD_DATA_RANGE_CHECK(*c1_error, 10U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_ARBlocks(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ARBlocksMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  real_T c1_e_hoistedGlobal;
  real_T c1_f_hoistedGlobal;
  real_T c1_g_hoistedGlobal;
  int32_T c1_i4;
  real_T c1_status[32];
  real_T c1_fly;
  real_T c1_rollAngRef;
  real_T c1_pitchAngRef;
  real_T c1_yawRateRef;
  real_T c1_wRef;
  real_T c1_enableRefs;
  real_T c1_stop;
  uint32_T c1_debug_family_var_map[19];
  uint8_T c1_strOut[150];
  int32_T c1_cmd_sizes[2];
  char_T c1_cmd_data[144];
  int32_T c1_strCmd_sizes[2];
  char_T c1_strCmd_data[11];
  real_T c1_aux;
  int32_T c1_strAux_sizes[2];
  char_T c1_strAux_data[11];
  real_T c1_nargin = 8.0;
  real_T c1_nargout = 3.0;
  uint8_T c1_dataControl[150];
  real_T c1_isFlying;
  real_T c1_error;
  int32_T c1_i5;
  int32_T c1_cmd;
  int32_T c1_b_cmd;
  int32_T c1_tmp_sizes[2];
  char_T c1_tmp_data[11];
  int32_T c1_strCmd;
  int32_T c1_b_strCmd;
  int32_T c1_loop_ub;
  int32_T c1_i6;
  int32_T c1_i7;
  static char_T c1_cv0[10] = { 'A', 'T', '*', 'C', 'O', 'N', 'F', 'I', 'G', '='
  };

  int32_T c1_b_loop_ub;
  int32_T c1_i8;
  int32_T c1_i9;
  static char_T c1_cv1[30] = { ',', '\"', 'g', 'e', 'n', 'e', 'r', 'a', 'l', ':',
    'n', 'a', 'v', 'd', 'a', 't', 'a', '_', 'd', 'e', 'm', 'o', '\"', ',', '\"',
    'T', 'R', 'U', 'E', '\"' };

  int32_T c1_b_tmp_sizes[2];
  char_T c1_b_tmp_data[11];
  int32_T c1_c_strCmd;
  int32_T c1_d_strCmd;
  int32_T c1_c_loop_ub;
  int32_T c1_i10;
  int32_T c1_b_cmd_sizes[2];
  int32_T c1_d_loop_ub;
  int32_T c1_i11;
  char_T c1_b_cmd_data[144];
  int32_T c1_i12;
  static char_T c1_cv2[10] = { 'A', 'T', '*', 'C', 'O', 'M', 'W', 'D', 'G', '='
  };

  int32_T c1_e_loop_ub;
  int32_T c1_i13;
  int32_T c1_f_loop_ub;
  int32_T c1_i14;
  int32_T c1_i15;
  static char_T c1_cv3[7] = { 'A', 'T', '*', 'R', 'E', 'F', '=' };

  int32_T c1_g_loop_ub;
  int32_T c1_i16;
  int32_T c1_i17;
  static char_T c1_cv4[10] = { ',', '2', '9', '0', '7', '1', '7', '9', '5', '2'
  };

  int32_T c1_c_tmp_sizes[2];
  char_T c1_c_tmp_data[11];
  int32_T c1_e_strCmd;
  int32_T c1_f_strCmd;
  int32_T c1_h_loop_ub;
  int32_T c1_i18;
  int32_T c1_c_cmd_sizes[2];
  int32_T c1_i_loop_ub;
  int32_T c1_i19;
  char_T c1_c_cmd_data[144];
  int32_T c1_i20;
  static char_T c1_cv5[9] = { 'A', 'T', '*', 'F', 'T', 'R', 'I', 'M', '=' };

  int32_T c1_j_loop_ub;
  int32_T c1_i21;
  int32_T c1_k_loop_ub;
  int32_T c1_i22;
  int32_T c1_d_cmd_sizes[2];
  int32_T c1_l_loop_ub;
  int32_T c1_i23;
  char_T c1_d_cmd_data[144];
  int32_T c1_i24;
  int32_T c1_m_loop_ub;
  int32_T c1_i25;
  int32_T c1_i26;
  static char_T c1_cv6[30] = { '\"', 'c', 'o', 'n', 'r', 'o', 'l', ':', 'a', 'l',
    't', 'i', 't', 'u', 'd', 'e', '_', 'm', 'a', 'x', '\"', ',', '\"', '1', '0',
    '0', '0', '0', '0', '\"' };

  int32_T c1_n_loop_ub;
  int32_T c1_i27;
  int32_T c1_d_tmp_sizes[2];
  char_T c1_d_tmp_data[11];
  int32_T c1_g_strCmd;
  int32_T c1_h_strCmd;
  int32_T c1_o_loop_ub;
  int32_T c1_i28;
  int32_T c1_e_cmd_sizes[2];
  int32_T c1_p_loop_ub;
  int32_T c1_i29;
  char_T c1_e_cmd_data[144];
  int32_T c1_i30;
  int32_T c1_q_loop_ub;
  int32_T c1_i31;
  int32_T c1_i32;
  static char_T c1_cv7[10] = { ',', '2', '9', '0', '7', '1', '8', '2', '0', '8'
  };

  int32_T c1_r_loop_ub;
  int32_T c1_i33;
  int32_T c1_e_tmp_sizes[2];
  char_T c1_e_tmp_data[11];
  int32_T c1_i_strCmd;
  int32_T c1_j_strCmd;
  int32_T c1_s_loop_ub;
  int32_T c1_i34;
  int32_T c1_f_cmd_sizes[2];
  int32_T c1_t_loop_ub;
  int32_T c1_i35;
  char_T c1_f_cmd_data[144];
  int32_T c1_i36;
  static char_T c1_cv8[8] = { 'A', 'T', '*', 'P', 'C', 'M', 'D', '=' };

  int32_T c1_u_loop_ub;
  int32_T c1_i37;
  int32_T c1_i38;
  static char_T c1_cv9[3] = { ',', '1', ',' };

  int32_T c1_v_loop_ub;
  int32_T c1_i39;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_y;
  int32_T c1_f_tmp_sizes[2];
  char_T c1_f_tmp_data[11];
  int32_T c1_strAux;
  int32_T c1_b_strAux;
  int32_T c1_w_loop_ub;
  int32_T c1_i40;
  int32_T c1_g_tmp_sizes[2];
  char_T c1_g_tmp_data[11];
  int32_T c1_x_loop_ub;
  int32_T c1_i41;
  int32_T c1_y_loop_ub;
  int32_T c1_i42;
  int32_T c1_g_cmd_sizes[2];
  int32_T c1_ab_loop_ub;
  int32_T c1_i43;
  char_T c1_g_cmd_data[144];
  int32_T c1_bb_loop_ub;
  int32_T c1_i44;
  int32_T c1_cb_loop_ub;
  int32_T c1_i45;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_b_y;
  int32_T c1_h_tmp_sizes[2];
  char_T c1_h_tmp_data[11];
  int32_T c1_c_strAux;
  int32_T c1_d_strAux;
  int32_T c1_db_loop_ub;
  int32_T c1_i46;
  int32_T c1_i_tmp_sizes[2];
  char_T c1_i_tmp_data[11];
  int32_T c1_eb_loop_ub;
  int32_T c1_i47;
  int32_T c1_fb_loop_ub;
  int32_T c1_i48;
  int32_T c1_h_cmd_sizes[2];
  int32_T c1_gb_loop_ub;
  int32_T c1_i49;
  char_T c1_h_cmd_data[144];
  int32_T c1_hb_loop_ub;
  int32_T c1_i50;
  int32_T c1_ib_loop_ub;
  int32_T c1_i51;
  int32_T c1_j_tmp_sizes[2];
  char_T c1_j_tmp_data[11];
  int32_T c1_e_strAux;
  int32_T c1_f_strAux;
  int32_T c1_jb_loop_ub;
  int32_T c1_i52;
  int32_T c1_k_tmp_sizes[2];
  char_T c1_k_tmp_data[11];
  int32_T c1_kb_loop_ub;
  int32_T c1_i53;
  int32_T c1_lb_loop_ub;
  int32_T c1_i54;
  int32_T c1_i_cmd_sizes[2];
  int32_T c1_mb_loop_ub;
  int32_T c1_i55;
  char_T c1_i_cmd_data[144];
  int32_T c1_nb_loop_ub;
  int32_T c1_i56;
  int32_T c1_ob_loop_ub;
  int32_T c1_i57;
  int32_T c1_l_tmp_sizes[2];
  char_T c1_l_tmp_data[11];
  int32_T c1_g_strAux;
  int32_T c1_h_strAux;
  int32_T c1_pb_loop_ub;
  int32_T c1_i58;
  int32_T c1_m_tmp_sizes[2];
  char_T c1_m_tmp_data[11];
  int32_T c1_qb_loop_ub;
  int32_T c1_i59;
  int32_T c1_rb_loop_ub;
  int32_T c1_i60;
  int32_T c1_j_cmd_sizes[2];
  int32_T c1_sb_loop_ub;
  int32_T c1_i61;
  char_T c1_j_cmd_data[144];
  int32_T c1_tb_loop_ub;
  int32_T c1_i62;
  int32_T c1_ub_loop_ub;
  int32_T c1_i63;
  int32_T c1_n_tmp_sizes[2];
  char_T c1_n_tmp_data[11];
  int32_T c1_k_strCmd;
  int32_T c1_l_strCmd;
  int32_T c1_vb_loop_ub;
  int32_T c1_i64;
  int32_T c1_k_cmd_sizes[2];
  int32_T c1_wb_loop_ub;
  int32_T c1_i65;
  char_T c1_k_cmd_data[144];
  int32_T c1_i66;
  int32_T c1_xb_loop_ub;
  int32_T c1_i67;
  int32_T c1_i68;
  static char_T c1_cv10[10] = { ',', '2', '9', '0', '7', '1', '7', '6', '9', '6'
  };

  int32_T c1_yb_loop_ub;
  int32_T c1_i69;
  int32_T c1_x_sizes[2];
  int32_T c1_e_x;
  int32_T c1_f_x;
  int32_T c1_ac_loop_ub;
  int32_T c1_i70;
  char_T c1_x_data[144];
  real_T c1_n;
  int32_T c1_g_x;
  int32_T c1_h_x;
  int32_T c1_bc_loop_ub;
  int32_T c1_i71;
  real_T c1_d0;
  int32_T c1_i72;
  int32_T c1_o_tmp_sizes;
  int32_T c1_cc_loop_ub;
  int32_T c1_i73;
  int32_T c1_o_tmp_data[144];
  int32_T c1_l_cmd_sizes[2];
  int32_T c1_c_cmd;
  int32_T c1_d_cmd;
  int32_T c1_dc_loop_ub;
  int32_T c1_i74;
  uint8_T c1_l_cmd_data[144];
  int32_T c1_ec_loop_ub;
  int32_T c1_i75;
  int32_T c1_i76;
  int32_T c1_i77;
  real_T *c1_b_fly;
  real_T *c1_b_rollAngRef;
  real_T *c1_b_pitchAngRef;
  real_T *c1_b_yawRateRef;
  real_T *c1_b_wRef;
  real_T *c1_b_enableRefs;
  real_T *c1_b_stop;
  real_T *c1_b_isFlying;
  real_T *c1_b_error;
  uint8_T (*c1_b_dataControl)[150];
  real_T (*c1_b_status)[32];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  boolean_T guard4 = FALSE;
  c1_b_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_stop = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c1_b_isFlying = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_dataControl = (uint8_T (*)[150])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_enableRefs = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_b_wRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_b_yawRateRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_b_pitchAngRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_rollAngRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_fly = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_status = (real_T (*)[32])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_fly;
  c1_b_hoistedGlobal = *c1_b_rollAngRef;
  c1_c_hoistedGlobal = *c1_b_pitchAngRef;
  c1_d_hoistedGlobal = *c1_b_yawRateRef;
  c1_e_hoistedGlobal = *c1_b_wRef;
  c1_f_hoistedGlobal = *c1_b_enableRefs;
  c1_g_hoistedGlobal = *c1_b_stop;
  for (c1_i4 = 0; c1_i4 < 32; c1_i4++) {
    c1_status[c1_i4] = (*c1_b_status)[c1_i4];
  }

  c1_fly = c1_hoistedGlobal;
  c1_rollAngRef = c1_b_hoistedGlobal;
  c1_pitchAngRef = c1_c_hoistedGlobal;
  c1_yawRateRef = c1_d_hoistedGlobal;
  c1_wRef = c1_e_hoistedGlobal;
  c1_enableRefs = c1_f_hoistedGlobal;
  c1_stop = c1_g_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 19U, 19U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_strOut, 0U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_cmd_data, (const int32_T *)
    &c1_cmd_sizes, NULL, 0, 1, (void *)c1_f_sf_marshallOut, (void *)
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_strCmd_data, (const int32_T *)
    &c1_strCmd_sizes, NULL, 0, 2, (void *)c1_e_sf_marshallOut, (void *)
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_aux, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_strAux_data, (const int32_T *)
    &c1_strAux_sizes, NULL, 0, 4, (void *)c1_e_sf_marshallOut, (void *)
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 6U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_status, 7U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_fly, 8U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_rollAngRef, 9U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_pitchAngRef, 10U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_yawRateRef, 11U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_wRef, 12U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_enableRefs, 13U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_stop, 14U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_dataControl, 15U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_isFlying, 16U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_error, 17U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_SequenceNumber, 18U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c1_SequenceNumber_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
    chartInstance->c1_SequenceNumber = 1.0;
    chartInstance->c1_SequenceNumber_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_error = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
  c1_isFlying = c1_status[31];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  for (c1_i5 = 0; c1_i5 < 150; c1_i5++) {
    c1_strOut[c1_i5] = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
  c1_cmd_sizes[0] = 1;
  c1_cmd_sizes[1] = 0;
  c1_cmd = c1_cmd_sizes[0];
  c1_b_cmd = c1_cmd_sizes[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
  guard4 = FALSE;
  if (CV_EML_COND(0, 1, 0, chartInstance->c1_SequenceNumber <= 1.0)) {
    guard4 = TRUE;
  } else if (CV_EML_COND(0, 1, 1, c1_mod(chartInstance,
               chartInstance->c1_SequenceNumber, 100.0) == 0.0)) {
    guard4 = TRUE;
  } else {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 1, FALSE);
  }

  if (guard4 == TRUE) {
    CV_EML_MCDC(0, 1, 0, TRUE);
    CV_EML_IF(0, 1, 1, TRUE);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 30);
    chartInstance->c1_SequenceNumber++;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 31);
    c1_getString(chartInstance, chartInstance->c1_SequenceNumber, c1_tmp_data,
                 c1_tmp_sizes);
    c1_strCmd_sizes[0] = 1;
    c1_strCmd_sizes[1] = c1_tmp_sizes[1];
    c1_strCmd = c1_strCmd_sizes[0];
    c1_b_strCmd = c1_strCmd_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i6 = 0; c1_i6 <= c1_loop_ub; c1_i6++) {
      c1_strCmd_data[c1_i6] = c1_tmp_data[c1_i6];
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
    c1_cmd_sizes[0] = 1;
    c1_cmd_sizes[1] = c1_strCmd_sizes[1] + 41;
    for (c1_i7 = 0; c1_i7 < 10; c1_i7++) {
      c1_cmd_data[c1_cmd_sizes[0] * c1_i7] = c1_cv0[c1_i7];
    }

    c1_b_loop_ub = c1_strCmd_sizes[1] - 1;
    for (c1_i8 = 0; c1_i8 <= c1_b_loop_ub; c1_i8++) {
      c1_cmd_data[c1_cmd_sizes[0] * (c1_i8 + 10)] =
        c1_strCmd_data[c1_strCmd_sizes[0] * c1_i8];
    }

    for (c1_i9 = 0; c1_i9 < 30; c1_i9++) {
      c1_cmd_data[c1_cmd_sizes[0] * ((c1_i9 + c1_strCmd_sizes[1]) + 10)] =
        c1_cv1[c1_i9];
    }

    c1_cmd_data[c1_cmd_sizes[0] * (c1_strCmd_sizes[1] + 40)] = '\x0d';
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
  chartInstance->c1_SequenceNumber++;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 37);
  c1_getString(chartInstance, chartInstance->c1_SequenceNumber, c1_b_tmp_data,
               c1_b_tmp_sizes);
  c1_strCmd_sizes[0] = 1;
  c1_strCmd_sizes[1] = c1_b_tmp_sizes[1];
  c1_c_strCmd = c1_strCmd_sizes[0];
  c1_d_strCmd = c1_strCmd_sizes[1];
  c1_c_loop_ub = c1_b_tmp_sizes[0] * c1_b_tmp_sizes[1] - 1;
  for (c1_i10 = 0; c1_i10 <= c1_c_loop_ub; c1_i10++) {
    c1_strCmd_data[c1_i10] = c1_b_tmp_data[c1_i10];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  c1_b_cmd_sizes[0] = 1;
  c1_b_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strCmd_sizes[1]) + 11;
  c1_d_loop_ub = c1_cmd_sizes[1] - 1;
  for (c1_i11 = 0; c1_i11 <= c1_d_loop_ub; c1_i11++) {
    c1_b_cmd_data[c1_b_cmd_sizes[0] * c1_i11] = c1_cmd_data[c1_cmd_sizes[0] *
      c1_i11];
  }

  for (c1_i12 = 0; c1_i12 < 10; c1_i12++) {
    c1_b_cmd_data[c1_b_cmd_sizes[0] * (c1_i12 + c1_cmd_sizes[1])] =
      c1_cv2[c1_i12];
  }

  c1_e_loop_ub = c1_strCmd_sizes[1] - 1;
  for (c1_i13 = 0; c1_i13 <= c1_e_loop_ub; c1_i13++) {
    c1_b_cmd_data[c1_b_cmd_sizes[0] * ((c1_i13 + c1_cmd_sizes[1]) + 10)] =
      c1_strCmd_data[c1_strCmd_sizes[0] * c1_i13];
  }

  c1_b_cmd_data[c1_b_cmd_sizes[0] * ((c1_cmd_sizes[1] + c1_strCmd_sizes[1]) + 10)]
    = '\x0d';
  c1_cmd_sizes[0] = 1;
  c1_cmd_sizes[1] = c1_b_cmd_sizes[1];
  c1_f_loop_ub = c1_b_cmd_sizes[1] - 1;
  for (c1_i14 = 0; c1_i14 <= c1_f_loop_ub; c1_i14++) {
    c1_cmd_data[c1_cmd_sizes[0] * c1_i14] = c1_b_cmd_data[c1_b_cmd_sizes[0] *
      c1_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 41);
  if (CV_EML_IF(0, 1, 2, c1_stop == 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
    c1_cmd_sizes[0] = 1;
    c1_cmd_sizes[1] = c1_strCmd_sizes[1] + 18;
    for (c1_i15 = 0; c1_i15 < 7; c1_i15++) {
      c1_cmd_data[c1_cmd_sizes[0] * c1_i15] = c1_cv3[c1_i15];
    }

    c1_g_loop_ub = c1_strCmd_sizes[1] - 1;
    for (c1_i16 = 0; c1_i16 <= c1_g_loop_ub; c1_i16++) {
      c1_cmd_data[c1_cmd_sizes[0] * (c1_i16 + 7)] =
        c1_strCmd_data[c1_strCmd_sizes[0] * c1_i16];
    }

    for (c1_i17 = 0; c1_i17 < 10; c1_i17++) {
      c1_cmd_data[c1_cmd_sizes[0] * ((c1_i17 + c1_strCmd_sizes[1]) + 7)] =
        c1_cv4[c1_i17];
    }

    c1_cmd_data[c1_cmd_sizes[0] * (c1_strCmd_sizes[1] + 17)] = '\x0d';
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 46);
    guard1 = FALSE;
    if (CV_EML_COND(0, 1, 2, chartInstance->c1_SequenceNumber > 20.0)) {
      if (CV_EML_COND(0, 1, 3, chartInstance->c1_SequenceNumber < 22.0)) {
        CV_EML_MCDC(0, 1, 1, TRUE);
        CV_EML_IF(0, 1, 3, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 49);
        chartInstance->c1_SequenceNumber = 22.0;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 50);
        c1_getString(chartInstance, 22.0, c1_c_tmp_data, c1_c_tmp_sizes);
        c1_strCmd_sizes[0] = 1;
        c1_strCmd_sizes[1] = c1_c_tmp_sizes[1];
        c1_e_strCmd = c1_strCmd_sizes[0];
        c1_f_strCmd = c1_strCmd_sizes[1];
        c1_h_loop_ub = c1_c_tmp_sizes[0] * c1_c_tmp_sizes[1] - 1;
        for (c1_i18 = 0; c1_i18 <= c1_h_loop_ub; c1_i18++) {
          c1_strCmd_data[c1_i18] = c1_c_tmp_data[c1_i18];
        }

        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 51);
        c1_c_cmd_sizes[0] = 1;
        c1_c_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strCmd_sizes[1]) + 10;
        c1_i_loop_ub = c1_cmd_sizes[1] - 1;
        for (c1_i19 = 0; c1_i19 <= c1_i_loop_ub; c1_i19++) {
          c1_c_cmd_data[c1_c_cmd_sizes[0] * c1_i19] = c1_cmd_data[c1_cmd_sizes[0]
            * c1_i19];
        }

        for (c1_i20 = 0; c1_i20 < 9; c1_i20++) {
          c1_c_cmd_data[c1_c_cmd_sizes[0] * (c1_i20 + c1_cmd_sizes[1])] =
            c1_cv5[c1_i20];
        }

        c1_j_loop_ub = c1_strCmd_sizes[1] - 1;
        for (c1_i21 = 0; c1_i21 <= c1_j_loop_ub; c1_i21++) {
          c1_c_cmd_data[c1_c_cmd_sizes[0] * ((c1_i21 + c1_cmd_sizes[1]) + 9)] =
            c1_strCmd_data[c1_strCmd_sizes[0] * c1_i21];
        }

        c1_c_cmd_data[c1_c_cmd_sizes[0] * ((c1_cmd_sizes[1] + c1_strCmd_sizes[1])
          + 9)] = '\x0d';
        c1_cmd_sizes[0] = 1;
        c1_cmd_sizes[1] = c1_c_cmd_sizes[1];
        c1_k_loop_ub = c1_c_cmd_sizes[1] - 1;
        for (c1_i22 = 0; c1_i22 <= c1_k_loop_ub; c1_i22++) {
          c1_cmd_data[c1_cmd_sizes[0] * c1_i22] = c1_c_cmd_data[c1_c_cmd_sizes[0]
            * c1_i22];
        }
      } else {
        guard1 = TRUE;
      }
    } else {
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      CV_EML_MCDC(0, 1, 1, FALSE);
      CV_EML_IF(0, 1, 3, FALSE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 53);
      guard2 = FALSE;
      if (CV_EML_COND(0, 1, 4, chartInstance->c1_SequenceNumber >= 22.0)) {
        if (CV_EML_COND(0, 1, 5, chartInstance->c1_SequenceNumber < 25.0)) {
          CV_EML_MCDC(0, 1, 2, TRUE);
          CV_EML_IF(0, 1, 4, TRUE);
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 54);
          c1_d_cmd_sizes[0] = 1;
          c1_d_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strCmd_sizes[1]) + 41;
          c1_l_loop_ub = c1_cmd_sizes[1] - 1;
          for (c1_i23 = 0; c1_i23 <= c1_l_loop_ub; c1_i23++) {
            c1_d_cmd_data[c1_d_cmd_sizes[0] * c1_i23] =
              c1_cmd_data[c1_cmd_sizes[0] * c1_i23];
          }

          for (c1_i24 = 0; c1_i24 < 10; c1_i24++) {
            c1_d_cmd_data[c1_d_cmd_sizes[0] * (c1_i24 + c1_cmd_sizes[1])] =
              c1_cv0[c1_i24];
          }

          c1_m_loop_ub = c1_strCmd_sizes[1] - 1;
          for (c1_i25 = 0; c1_i25 <= c1_m_loop_ub; c1_i25++) {
            c1_d_cmd_data[c1_d_cmd_sizes[0] * ((c1_i25 + c1_cmd_sizes[1]) + 10)]
              = c1_strCmd_data[c1_strCmd_sizes[0] * c1_i25];
          }

          for (c1_i26 = 0; c1_i26 < 30; c1_i26++) {
            c1_d_cmd_data[c1_d_cmd_sizes[0] * (((c1_i26 + c1_cmd_sizes[1]) +
              c1_strCmd_sizes[1]) + 10)] = c1_cv6[c1_i26];
          }

          c1_d_cmd_data[c1_d_cmd_sizes[0] * ((c1_cmd_sizes[1] + c1_strCmd_sizes
            [1]) + 40)] = '\x0d';
          c1_cmd_sizes[0] = 1;
          c1_cmd_sizes[1] = c1_d_cmd_sizes[1];
          c1_n_loop_ub = c1_d_cmd_sizes[1] - 1;
          for (c1_i27 = 0; c1_i27 <= c1_n_loop_ub; c1_i27++) {
            c1_cmd_data[c1_cmd_sizes[0] * c1_i27] =
              c1_d_cmd_data[c1_d_cmd_sizes[0] * c1_i27];
          }
        } else {
          guard2 = TRUE;
        }
      } else {
        guard2 = TRUE;
      }

      if (guard2 == TRUE) {
        CV_EML_MCDC(0, 1, 2, FALSE);
        CV_EML_IF(0, 1, 4, FALSE);
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 57);
        if (CV_EML_IF(0, 1, 5, chartInstance->c1_SequenceNumber >= 25.0)) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 59);
          if (CV_EML_IF(0, 1, 6, c1_fly == 1.0)) {
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 61);
            if (CV_EML_IF(0, 1, 7, c1_isFlying == 0.0)) {
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 63);
              chartInstance->c1_SequenceNumber++;
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 64);
              c1_getString(chartInstance, chartInstance->c1_SequenceNumber,
                           c1_d_tmp_data, c1_d_tmp_sizes);
              c1_strCmd_sizes[0] = 1;
              c1_strCmd_sizes[1] = c1_d_tmp_sizes[1];
              c1_g_strCmd = c1_strCmd_sizes[0];
              c1_h_strCmd = c1_strCmd_sizes[1];
              c1_o_loop_ub = c1_d_tmp_sizes[0] * c1_d_tmp_sizes[1] - 1;
              for (c1_i28 = 0; c1_i28 <= c1_o_loop_ub; c1_i28++) {
                c1_strCmd_data[c1_i28] = c1_d_tmp_data[c1_i28];
              }

              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 65);
              c1_e_cmd_sizes[0] = 1;
              c1_e_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strCmd_sizes[1]) + 18;
              c1_p_loop_ub = c1_cmd_sizes[1] - 1;
              for (c1_i29 = 0; c1_i29 <= c1_p_loop_ub; c1_i29++) {
                c1_e_cmd_data[c1_e_cmd_sizes[0] * c1_i29] =
                  c1_cmd_data[c1_cmd_sizes[0] * c1_i29];
              }

              for (c1_i30 = 0; c1_i30 < 7; c1_i30++) {
                c1_e_cmd_data[c1_e_cmd_sizes[0] * (c1_i30 + c1_cmd_sizes[1])] =
                  c1_cv3[c1_i30];
              }

              c1_q_loop_ub = c1_strCmd_sizes[1] - 1;
              for (c1_i31 = 0; c1_i31 <= c1_q_loop_ub; c1_i31++) {
                c1_e_cmd_data[c1_e_cmd_sizes[0] * ((c1_i31 + c1_cmd_sizes[1]) +
                  7)] = c1_strCmd_data[c1_strCmd_sizes[0] * c1_i31];
              }

              for (c1_i32 = 0; c1_i32 < 10; c1_i32++) {
                c1_e_cmd_data[c1_e_cmd_sizes[0] * (((c1_i32 + c1_cmd_sizes[1]) +
                  c1_strCmd_sizes[1]) + 7)] = c1_cv7[c1_i32];
              }

              c1_e_cmd_data[c1_e_cmd_sizes[0] * ((c1_cmd_sizes[1] +
                c1_strCmd_sizes[1]) + 17)] = '\x0d';
              c1_cmd_sizes[0] = 1;
              c1_cmd_sizes[1] = c1_e_cmd_sizes[1];
              c1_r_loop_ub = c1_e_cmd_sizes[1] - 1;
              for (c1_i33 = 0; c1_i33 <= c1_r_loop_ub; c1_i33++) {
                c1_cmd_data[c1_cmd_sizes[0] * c1_i33] =
                  c1_e_cmd_data[c1_e_cmd_sizes[0] * c1_i33];
              }
            } else {
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 67);
              guard3 = FALSE;
              if (CV_EML_COND(0, 1, 6, c1_isFlying == 1.0)) {
                if (CV_EML_COND(0, 1, 7, c1_enableRefs == 1.0)) {
                  CV_EML_MCDC(0, 1, 3, TRUE);
                  CV_EML_IF(0, 1, 8, TRUE);
                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 69);
                  chartInstance->c1_SequenceNumber++;
                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 70);
                  c1_getString(chartInstance, chartInstance->c1_SequenceNumber,
                               c1_e_tmp_data, c1_e_tmp_sizes);
                  c1_strCmd_sizes[0] = 1;
                  c1_strCmd_sizes[1] = c1_e_tmp_sizes[1];
                  c1_i_strCmd = c1_strCmd_sizes[0];
                  c1_j_strCmd = c1_strCmd_sizes[1];
                  c1_s_loop_ub = c1_e_tmp_sizes[0] * c1_e_tmp_sizes[1] - 1;
                  for (c1_i34 = 0; c1_i34 <= c1_s_loop_ub; c1_i34++) {
                    c1_strCmd_data[c1_i34] = c1_e_tmp_data[c1_i34];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 72);
                  c1_f_cmd_sizes[0] = 1;
                  c1_f_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strCmd_sizes[1]) +
                    11;
                  c1_t_loop_ub = c1_cmd_sizes[1] - 1;
                  for (c1_i35 = 0; c1_i35 <= c1_t_loop_ub; c1_i35++) {
                    c1_f_cmd_data[c1_f_cmd_sizes[0] * c1_i35] =
                      c1_cmd_data[c1_cmd_sizes[0] * c1_i35];
                  }

                  for (c1_i36 = 0; c1_i36 < 8; c1_i36++) {
                    c1_f_cmd_data[c1_f_cmd_sizes[0] * (c1_i36 + c1_cmd_sizes[1])]
                      = c1_cv8[c1_i36];
                  }

                  c1_u_loop_ub = c1_strCmd_sizes[1] - 1;
                  for (c1_i37 = 0; c1_i37 <= c1_u_loop_ub; c1_i37++) {
                    c1_f_cmd_data[c1_f_cmd_sizes[0] * ((c1_i37 + c1_cmd_sizes[1])
                      + 8)] = c1_strCmd_data[c1_strCmd_sizes[0] * c1_i37];
                  }

                  for (c1_i38 = 0; c1_i38 < 3; c1_i38++) {
                    c1_f_cmd_data[c1_f_cmd_sizes[0] * (((c1_i38 + c1_cmd_sizes[1])
                      + c1_strCmd_sizes[1]) + 8)] = c1_cv9[c1_i38];
                  }

                  c1_cmd_sizes[0] = 1;
                  c1_cmd_sizes[1] = c1_f_cmd_sizes[1];
                  c1_v_loop_ub = c1_f_cmd_sizes[1] - 1;
                  for (c1_i39 = 0; c1_i39 <= c1_v_loop_ub; c1_i39++) {
                    c1_cmd_data[c1_cmd_sizes[0] * c1_i39] =
                      c1_f_cmd_data[c1_f_cmd_sizes[0] * c1_i39];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 74);
                  c1_aux = (real_T)c1_float2IEEE754(chartInstance, c1_rollAngRef);
                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 75);
                  c1_x = c1_aux;
                  c1_b_x = c1_x;
                  c1_y = muDoubleScalarAbs(c1_b_x);
                  c1_getString(chartInstance, c1_y, c1_f_tmp_data,
                               c1_f_tmp_sizes);
                  c1_strAux_sizes[0] = 1;
                  c1_strAux_sizes[1] = c1_f_tmp_sizes[1];
                  c1_strAux = c1_strAux_sizes[0];
                  c1_b_strAux = c1_strAux_sizes[1];
                  c1_w_loop_ub = c1_f_tmp_sizes[0] * c1_f_tmp_sizes[1] - 1;
                  for (c1_i40 = 0; c1_i40 <= c1_w_loop_ub; c1_i40++) {
                    c1_strAux_data[c1_i40] = c1_f_tmp_data[c1_i40];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 76);
                  if (CV_EML_IF(0, 1, 9, c1_rollAngRef < 0.0)) {
                    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 77);
                    c1_g_tmp_sizes[0] = 1;
                    c1_g_tmp_sizes[1] = 1 + c1_strAux_sizes[1];
                    c1_g_tmp_data[0] = '-';
                    c1_x_loop_ub = c1_strAux_sizes[1] - 1;
                    for (c1_i41 = 0; c1_i41 <= c1_x_loop_ub; c1_i41++) {
                      c1_g_tmp_data[c1_g_tmp_sizes[0] * (c1_i41 + 1)] =
                        c1_strAux_data[c1_strAux_sizes[0] * c1_i41];
                    }

                    c1_strAux_sizes[0] = 1;
                    c1_strAux_sizes[1] = c1_g_tmp_sizes[1];
                    c1_y_loop_ub = c1_g_tmp_sizes[1] - 1;
                    for (c1_i42 = 0; c1_i42 <= c1_y_loop_ub; c1_i42++) {
                      c1_strAux_data[c1_strAux_sizes[0] * c1_i42] =
                        c1_g_tmp_data[c1_g_tmp_sizes[0] * c1_i42];
                    }
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 79);
                  c1_g_cmd_sizes[0] = 1;
                  c1_g_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strAux_sizes[1]) + 1;
                  c1_ab_loop_ub = c1_cmd_sizes[1] - 1;
                  for (c1_i43 = 0; c1_i43 <= c1_ab_loop_ub; c1_i43++) {
                    c1_g_cmd_data[c1_g_cmd_sizes[0] * c1_i43] =
                      c1_cmd_data[c1_cmd_sizes[0] * c1_i43];
                  }

                  c1_bb_loop_ub = c1_strAux_sizes[1] - 1;
                  for (c1_i44 = 0; c1_i44 <= c1_bb_loop_ub; c1_i44++) {
                    c1_g_cmd_data[c1_g_cmd_sizes[0] * (c1_i44 + c1_cmd_sizes[1])]
                      = c1_strAux_data[c1_strAux_sizes[0] * c1_i44];
                  }

                  c1_g_cmd_data[c1_g_cmd_sizes[0] * (c1_cmd_sizes[1] +
                    c1_strAux_sizes[1])] = ',';
                  c1_cmd_sizes[0] = 1;
                  c1_cmd_sizes[1] = c1_g_cmd_sizes[1];
                  c1_cb_loop_ub = c1_g_cmd_sizes[1] - 1;
                  for (c1_i45 = 0; c1_i45 <= c1_cb_loop_ub; c1_i45++) {
                    c1_cmd_data[c1_cmd_sizes[0] * c1_i45] =
                      c1_g_cmd_data[c1_g_cmd_sizes[0] * c1_i45];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 81);
                  c1_aux = (real_T)c1_float2IEEE754(chartInstance,
                    c1_pitchAngRef);
                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 82);
                  c1_c_x = c1_aux;
                  c1_d_x = c1_c_x;
                  c1_b_y = muDoubleScalarAbs(c1_d_x);
                  c1_getString(chartInstance, c1_b_y, c1_h_tmp_data,
                               c1_h_tmp_sizes);
                  c1_strAux_sizes[0] = 1;
                  c1_strAux_sizes[1] = c1_h_tmp_sizes[1];
                  c1_c_strAux = c1_strAux_sizes[0];
                  c1_d_strAux = c1_strAux_sizes[1];
                  c1_db_loop_ub = c1_h_tmp_sizes[0] * c1_h_tmp_sizes[1] - 1;
                  for (c1_i46 = 0; c1_i46 <= c1_db_loop_ub; c1_i46++) {
                    c1_strAux_data[c1_i46] = c1_h_tmp_data[c1_i46];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 83);
                  if (CV_EML_IF(0, 1, 10, c1_pitchAngRef < 0.0)) {
                    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 84);
                    c1_b_char(chartInstance);
                    c1_i_tmp_sizes[0] = 1;
                    c1_i_tmp_sizes[1] = 1 + c1_strAux_sizes[1];
                    c1_i_tmp_data[0] = '-';
                    c1_eb_loop_ub = c1_strAux_sizes[1] - 1;
                    for (c1_i47 = 0; c1_i47 <= c1_eb_loop_ub; c1_i47++) {
                      c1_i_tmp_data[c1_i_tmp_sizes[0] * (c1_i47 + 1)] =
                        c1_strAux_data[c1_strAux_sizes[0] * c1_i47];
                    }

                    c1_strAux_sizes[0] = 1;
                    c1_strAux_sizes[1] = c1_i_tmp_sizes[1];
                    c1_fb_loop_ub = c1_i_tmp_sizes[1] - 1;
                    for (c1_i48 = 0; c1_i48 <= c1_fb_loop_ub; c1_i48++) {
                      c1_strAux_data[c1_strAux_sizes[0] * c1_i48] =
                        c1_i_tmp_data[c1_i_tmp_sizes[0] * c1_i48];
                    }
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 86);
                  c1_h_cmd_sizes[0] = 1;
                  c1_h_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strAux_sizes[1]) + 1;
                  c1_gb_loop_ub = c1_cmd_sizes[1] - 1;
                  for (c1_i49 = 0; c1_i49 <= c1_gb_loop_ub; c1_i49++) {
                    c1_h_cmd_data[c1_h_cmd_sizes[0] * c1_i49] =
                      c1_cmd_data[c1_cmd_sizes[0] * c1_i49];
                  }

                  c1_hb_loop_ub = c1_strAux_sizes[1] - 1;
                  for (c1_i50 = 0; c1_i50 <= c1_hb_loop_ub; c1_i50++) {
                    c1_h_cmd_data[c1_h_cmd_sizes[0] * (c1_i50 + c1_cmd_sizes[1])]
                      = c1_strAux_data[c1_strAux_sizes[0] * c1_i50];
                  }

                  c1_h_cmd_data[c1_h_cmd_sizes[0] * (c1_cmd_sizes[1] +
                    c1_strAux_sizes[1])] = ',';
                  c1_cmd_sizes[0] = 1;
                  c1_cmd_sizes[1] = c1_h_cmd_sizes[1];
                  c1_ib_loop_ub = c1_h_cmd_sizes[1] - 1;
                  for (c1_i51 = 0; c1_i51 <= c1_ib_loop_ub; c1_i51++) {
                    c1_cmd_data[c1_cmd_sizes[0] * c1_i51] =
                      c1_h_cmd_data[c1_h_cmd_sizes[0] * c1_i51];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 88);
                  c1_aux = (real_T)c1_float2IEEE754(chartInstance, c1_wRef);
                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 89);
                  c1_getString(chartInstance, c1_abs(chartInstance, c1_aux),
                               c1_j_tmp_data, c1_j_tmp_sizes);
                  c1_strAux_sizes[0] = 1;
                  c1_strAux_sizes[1] = c1_j_tmp_sizes[1];
                  c1_e_strAux = c1_strAux_sizes[0];
                  c1_f_strAux = c1_strAux_sizes[1];
                  c1_jb_loop_ub = c1_j_tmp_sizes[0] * c1_j_tmp_sizes[1] - 1;
                  for (c1_i52 = 0; c1_i52 <= c1_jb_loop_ub; c1_i52++) {
                    c1_strAux_data[c1_i52] = c1_j_tmp_data[c1_i52];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 90);
                  if (CV_EML_IF(0, 1, 11, c1_wRef < 0.0)) {
                    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 91);
                    c1_b_char(chartInstance);
                    c1_k_tmp_sizes[0] = 1;
                    c1_k_tmp_sizes[1] = 1 + c1_strAux_sizes[1];
                    c1_k_tmp_data[0] = '-';
                    c1_kb_loop_ub = c1_strAux_sizes[1] - 1;
                    for (c1_i53 = 0; c1_i53 <= c1_kb_loop_ub; c1_i53++) {
                      c1_k_tmp_data[c1_k_tmp_sizes[0] * (c1_i53 + 1)] =
                        c1_strAux_data[c1_strAux_sizes[0] * c1_i53];
                    }

                    c1_strAux_sizes[0] = 1;
                    c1_strAux_sizes[1] = c1_k_tmp_sizes[1];
                    c1_lb_loop_ub = c1_k_tmp_sizes[1] - 1;
                    for (c1_i54 = 0; c1_i54 <= c1_lb_loop_ub; c1_i54++) {
                      c1_strAux_data[c1_strAux_sizes[0] * c1_i54] =
                        c1_k_tmp_data[c1_k_tmp_sizes[0] * c1_i54];
                    }
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 93);
                  c1_i_cmd_sizes[0] = 1;
                  c1_i_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strAux_sizes[1]) + 1;
                  c1_mb_loop_ub = c1_cmd_sizes[1] - 1;
                  for (c1_i55 = 0; c1_i55 <= c1_mb_loop_ub; c1_i55++) {
                    c1_i_cmd_data[c1_i_cmd_sizes[0] * c1_i55] =
                      c1_cmd_data[c1_cmd_sizes[0] * c1_i55];
                  }

                  c1_nb_loop_ub = c1_strAux_sizes[1] - 1;
                  for (c1_i56 = 0; c1_i56 <= c1_nb_loop_ub; c1_i56++) {
                    c1_i_cmd_data[c1_i_cmd_sizes[0] * (c1_i56 + c1_cmd_sizes[1])]
                      = c1_strAux_data[c1_strAux_sizes[0] * c1_i56];
                  }

                  c1_i_cmd_data[c1_i_cmd_sizes[0] * (c1_cmd_sizes[1] +
                    c1_strAux_sizes[1])] = ',';
                  c1_cmd_sizes[0] = 1;
                  c1_cmd_sizes[1] = c1_i_cmd_sizes[1];
                  c1_ob_loop_ub = c1_i_cmd_sizes[1] - 1;
                  for (c1_i57 = 0; c1_i57 <= c1_ob_loop_ub; c1_i57++) {
                    c1_cmd_data[c1_cmd_sizes[0] * c1_i57] =
                      c1_i_cmd_data[c1_i_cmd_sizes[0] * c1_i57];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 96);
                  c1_aux = (real_T)c1_float2IEEE754(chartInstance, c1_yawRateRef);
                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 97);
                  c1_getString(chartInstance, c1_abs(chartInstance, c1_aux),
                               c1_l_tmp_data, c1_l_tmp_sizes);
                  c1_strAux_sizes[0] = 1;
                  c1_strAux_sizes[1] = c1_l_tmp_sizes[1];
                  c1_g_strAux = c1_strAux_sizes[0];
                  c1_h_strAux = c1_strAux_sizes[1];
                  c1_pb_loop_ub = c1_l_tmp_sizes[0] * c1_l_tmp_sizes[1] - 1;
                  for (c1_i58 = 0; c1_i58 <= c1_pb_loop_ub; c1_i58++) {
                    c1_strAux_data[c1_i58] = c1_l_tmp_data[c1_i58];
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 98);
                  if (CV_EML_IF(0, 1, 12, c1_yawRateRef < 0.0)) {
                    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 99);
                    c1_error = 2.0;
                    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 100);
                    c1_b_char(chartInstance);
                    c1_m_tmp_sizes[0] = 1;
                    c1_m_tmp_sizes[1] = 1 + c1_strAux_sizes[1];
                    c1_m_tmp_data[0] = '-';
                    c1_qb_loop_ub = c1_strAux_sizes[1] - 1;
                    for (c1_i59 = 0; c1_i59 <= c1_qb_loop_ub; c1_i59++) {
                      c1_m_tmp_data[c1_m_tmp_sizes[0] * (c1_i59 + 1)] =
                        c1_strAux_data[c1_strAux_sizes[0] * c1_i59];
                    }

                    c1_strAux_sizes[0] = 1;
                    c1_strAux_sizes[1] = c1_m_tmp_sizes[1];
                    c1_rb_loop_ub = c1_m_tmp_sizes[1] - 1;
                    for (c1_i60 = 0; c1_i60 <= c1_rb_loop_ub; c1_i60++) {
                      c1_strAux_data[c1_strAux_sizes[0] * c1_i60] =
                        c1_m_tmp_data[c1_m_tmp_sizes[0] * c1_i60];
                    }
                  }

                  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 102);
                  c1_char(chartInstance);
                  c1_j_cmd_sizes[0] = 1;
                  c1_j_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strAux_sizes[1]) + 1;
                  c1_sb_loop_ub = c1_cmd_sizes[1] - 1;
                  for (c1_i61 = 0; c1_i61 <= c1_sb_loop_ub; c1_i61++) {
                    c1_j_cmd_data[c1_j_cmd_sizes[0] * c1_i61] =
                      c1_cmd_data[c1_cmd_sizes[0] * c1_i61];
                  }

                  c1_tb_loop_ub = c1_strAux_sizes[1] - 1;
                  for (c1_i62 = 0; c1_i62 <= c1_tb_loop_ub; c1_i62++) {
                    c1_j_cmd_data[c1_j_cmd_sizes[0] * (c1_i62 + c1_cmd_sizes[1])]
                      = c1_strAux_data[c1_strAux_sizes[0] * c1_i62];
                  }

                  c1_j_cmd_data[c1_j_cmd_sizes[0] * (c1_cmd_sizes[1] +
                    c1_strAux_sizes[1])] = '\x0d';
                  c1_cmd_sizes[0] = 1;
                  c1_cmd_sizes[1] = c1_j_cmd_sizes[1];
                  c1_ub_loop_ub = c1_j_cmd_sizes[1] - 1;
                  for (c1_i63 = 0; c1_i63 <= c1_ub_loop_ub; c1_i63++) {
                    c1_cmd_data[c1_cmd_sizes[0] * c1_i63] =
                      c1_j_cmd_data[c1_j_cmd_sizes[0] * c1_i63];
                  }
                } else {
                  guard3 = TRUE;
                }
              } else {
                guard3 = TRUE;
              }

              if (guard3 == TRUE) {
                CV_EML_MCDC(0, 1, 3, FALSE);
                CV_EML_IF(0, 1, 8, FALSE);
              }
            }
          } else {
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 108);
            if (CV_EML_IF(0, 1, 13, c1_fly == 0.0)) {
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 110);
              if (CV_EML_IF(0, 1, 14, c1_isFlying == 1.0)) {
                _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 111);
                chartInstance->c1_SequenceNumber++;
                _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 112);
                c1_getString(chartInstance, chartInstance->c1_SequenceNumber,
                             c1_n_tmp_data, c1_n_tmp_sizes);
                c1_strCmd_sizes[0] = 1;
                c1_strCmd_sizes[1] = c1_n_tmp_sizes[1];
                c1_k_strCmd = c1_strCmd_sizes[0];
                c1_l_strCmd = c1_strCmd_sizes[1];
                c1_vb_loop_ub = c1_n_tmp_sizes[0] * c1_n_tmp_sizes[1] - 1;
                for (c1_i64 = 0; c1_i64 <= c1_vb_loop_ub; c1_i64++) {
                  c1_strCmd_data[c1_i64] = c1_n_tmp_data[c1_i64];
                }

                _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 113);
                c1_char(chartInstance);
                c1_k_cmd_sizes[0] = 1;
                c1_k_cmd_sizes[1] = (c1_cmd_sizes[1] + c1_strCmd_sizes[1]) + 18;
                c1_wb_loop_ub = c1_cmd_sizes[1] - 1;
                for (c1_i65 = 0; c1_i65 <= c1_wb_loop_ub; c1_i65++) {
                  c1_k_cmd_data[c1_k_cmd_sizes[0] * c1_i65] =
                    c1_cmd_data[c1_cmd_sizes[0] * c1_i65];
                }

                for (c1_i66 = 0; c1_i66 < 7; c1_i66++) {
                  c1_k_cmd_data[c1_k_cmd_sizes[0] * (c1_i66 + c1_cmd_sizes[1])] =
                    c1_cv3[c1_i66];
                }

                c1_xb_loop_ub = c1_strCmd_sizes[1] - 1;
                for (c1_i67 = 0; c1_i67 <= c1_xb_loop_ub; c1_i67++) {
                  c1_k_cmd_data[c1_k_cmd_sizes[0] * ((c1_i67 + c1_cmd_sizes[1])
                    + 7)] = c1_strCmd_data[c1_strCmd_sizes[0] * c1_i67];
                }

                for (c1_i68 = 0; c1_i68 < 10; c1_i68++) {
                  c1_k_cmd_data[c1_k_cmd_sizes[0] * (((c1_i68 + c1_cmd_sizes[1])
                    + c1_strCmd_sizes[1]) + 7)] = c1_cv10[c1_i68];
                }

                c1_k_cmd_data[c1_k_cmd_sizes[0] * ((c1_cmd_sizes[1] +
                  c1_strCmd_sizes[1]) + 17)] = '\x0d';
                c1_cmd_sizes[0] = 1;
                c1_cmd_sizes[1] = c1_k_cmd_sizes[1];
                c1_yb_loop_ub = c1_k_cmd_sizes[1] - 1;
                for (c1_i69 = 0; c1_i69 <= c1_yb_loop_ub; c1_i69++) {
                  c1_cmd_data[c1_cmd_sizes[0] * c1_i69] =
                    c1_k_cmd_data[c1_k_cmd_sizes[0] * c1_i69];
                }
              }
            }
          }
        }
      }
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 125);
  c1_x_sizes[0] = 1;
  c1_x_sizes[1] = c1_cmd_sizes[1];
  c1_e_x = c1_x_sizes[0];
  c1_f_x = c1_x_sizes[1];
  c1_ac_loop_ub = c1_cmd_sizes[0] * c1_cmd_sizes[1] - 1;
  for (c1_i70 = 0; c1_i70 <= c1_ac_loop_ub; c1_i70++) {
    c1_x_data[c1_i70] = c1_cmd_data[c1_i70];
  }

  c1_n = (real_T)c1_x_sizes[1];
  CV_EML_IF(0, 1, 15, c1_n < 150.0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 126);
  c1_x_sizes[0] = 1;
  c1_x_sizes[1] = c1_cmd_sizes[1];
  c1_g_x = c1_x_sizes[0];
  c1_h_x = c1_x_sizes[1];
  c1_bc_loop_ub = c1_cmd_sizes[0] * c1_cmd_sizes[1] - 1;
  for (c1_i71 = 0; c1_i71 <= c1_bc_loop_ub; c1_i71++) {
    c1_x_data[c1_i71] = c1_cmd_data[c1_i71];
  }

  c1_d0 = (real_T)c1_x_sizes[1];
  c1_i72 = (int32_T)c1_d0;
  c1_o_tmp_sizes = c1_i72;
  c1_cc_loop_ub = c1_i72 - 1;
  for (c1_i73 = 0; c1_i73 <= c1_cc_loop_ub; c1_i73++) {
    c1_o_tmp_data[c1_i73] = 1 + c1_i73;
  }

  c1_l_cmd_sizes[0] = 1;
  c1_l_cmd_sizes[1] = c1_cmd_sizes[1];
  c1_c_cmd = c1_l_cmd_sizes[0];
  c1_d_cmd = c1_l_cmd_sizes[1];
  c1_dc_loop_ub = c1_cmd_sizes[0] * c1_cmd_sizes[1] - 1;
  for (c1_i74 = 0; c1_i74 <= c1_dc_loop_ub; c1_i74++) {
    c1_l_cmd_data[c1_i74] = (uint8_T)c1_cmd_data[c1_i74];
  }

  _SFD_SIZE_EQ_CHECK_1D(c1_o_tmp_sizes, c1_l_cmd_sizes[1]);
  c1_ec_loop_ub = c1_cmd_sizes[0] * c1_cmd_sizes[1] - 1;
  for (c1_i75 = 0; c1_i75 <= c1_ec_loop_ub; c1_i75++) {
    c1_strOut[c1_o_tmp_data[c1_i75] - 1] = (uint8_T)c1_cmd_data[c1_i75];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 131U);
  for (c1_i76 = 0; c1_i76 < 150; c1_i76++) {
    c1_dataControl[c1_i76] = c1_strOut[c1_i76];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -131);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i77 = 0; c1_i77 < 150; c1_i77++) {
    (*c1_b_dataControl)[c1_i77] = c1_dataControl[c1_i77];
  }

  *c1_b_isFlying = c1_isFlying;
  *c1_b_error = c1_error;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_ARBlocks(SFc1_ARBlocksInstanceStruct *chartInstance)
{
}

static void registerMessagesc1_ARBlocks(SFc1_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_SequenceNumber_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_b_SequenceNumber, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_SequenceNumber),
    &c1_thisId);
  sf_mex_destroy(&c1_b_SequenceNumber);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d1;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_SequenceNumber_not_empty = FALSE;
  } else {
    chartInstance->c1_SequenceNumber_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d1, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d1;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_SequenceNumber;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_b_SequenceNumber = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_SequenceNumber),
    &c1_thisId);
  sf_mex_destroy(&c1_b_SequenceNumber);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_error, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_error), &c1_thisId);
  sf_mex_destroy(&c1_error);
  return c1_y;
}

static real_T c1_d_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d2;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d2, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_error;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_error = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_error), &c1_thisId);
  sf_mex_destroy(&c1_error);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i78;
  uint8_T c1_b_inData[150];
  int32_T c1_i79;
  uint8_T c1_u[150];
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i78 = 0; c1_i78 < 150; c1_i78++) {
    c1_b_inData[c1_i78] = (*(uint8_T (*)[150])c1_inData)[c1_i78];
  }

  for (c1_i79 = 0; c1_i79 < 150; c1_i79++) {
    c1_u[c1_i79] = c1_b_inData[c1_i79];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 3, 0U, 1U, 0U, 1, 150), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_dataControl, const char_T *c1_identifier, uint8_T c1_y[150])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_dataControl), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_dataControl);
}

static void c1_f_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[150])
{
  uint8_T c1_uv1[150];
  int32_T c1_i80;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv1, 1, 3, 0U, 1, 0U, 1, 150);
  for (c1_i80 = 0; c1_i80 < 150; c1_i80++) {
    c1_y[c1_i80] = c1_uv1[c1_i80];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_dataControl;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_y[150];
  int32_T c1_i81;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_dataControl = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_dataControl), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_dataControl);
  for (c1_i81 = 0; c1_i81 < 150; c1_i81++) {
    (*(uint8_T (*)[150])c1_outData)[c1_i81] = c1_y[c1_i81];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i82;
  real_T c1_b_inData[32];
  int32_T c1_i83;
  real_T c1_u[32];
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i82 = 0; c1_i82 < 32; c1_i82++) {
    c1_b_inData[c1_i82] = (*(real_T (*)[32])c1_inData)[c1_i82];
  }

  for (c1_i83 = 0; c1_i83 < 32; c1_i83++) {
    c1_u[c1_i83] = c1_b_inData[c1_i83];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 32), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, char_T
  c1_inData_data[11], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes[2];
  int32_T c1_loop_ub;
  int32_T c1_i84;
  char_T c1_b_inData_data[11];
  int32_T c1_u_sizes[2];
  int32_T c1_b_loop_ub;
  int32_T c1_i85;
  char_T c1_u_data[11];
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes[0] = 1;
  c1_b_inData_sizes[1] = c1_inData_sizes[1];
  c1_loop_ub = c1_inData_sizes[1] - 1;
  for (c1_i84 = 0; c1_i84 <= c1_loop_ub; c1_i84++) {
    c1_b_inData_data[c1_b_inData_sizes[0] * c1_i84] =
      c1_inData_data[c1_inData_sizes[0] * c1_i84];
  }

  c1_u_sizes[0] = 1;
  c1_u_sizes[1] = c1_b_inData_sizes[1];
  c1_b_loop_ub = c1_b_inData_sizes[1] - 1;
  for (c1_i85 = 0; c1_i85 <= c1_b_loop_ub; c1_i85++) {
    c1_u_data[c1_u_sizes[0] * c1_i85] = c1_b_inData_data[c1_b_inData_sizes[0] *
      c1_i85];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 10, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_g_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y_data
  [11], int32_T c1_y_sizes[2])
{
  int32_T c1_i86;
  uint32_T c1_uv2[2];
  int32_T c1_i87;
  static boolean_T c1_bv0[2] = { FALSE, TRUE };

  boolean_T c1_bv1[2];
  int32_T c1_tmp_sizes[2];
  char_T c1_tmp_data[11];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i88;
  for (c1_i86 = 0; c1_i86 < 2; c1_i86++) {
    c1_uv2[c1_i86] = 1U + 10U * (uint32_T)c1_i86;
  }

  for (c1_i87 = 0; c1_i87 < 2; c1_i87++) {
    c1_bv1[c1_i87] = c1_bv0[c1_i87];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 10, 0U, 1, 0U,
                   2, c1_bv1, c1_uv2, c1_tmp_sizes);
  c1_y_sizes[0] = 1;
  c1_y_sizes[1] = c1_tmp_sizes[1];
  c1_y = c1_y_sizes[0];
  c1_b_y = c1_y_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i88 = 0; c1_i88 <= c1_loop_ub; c1_i88++) {
    c1_y_data[c1_i88] = c1_tmp_data[c1_i88];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, char_T c1_outData_data[11],
  int32_T c1_outData_sizes[2])
{
  const mxArray *c1_strAux;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes[2];
  char_T c1_y_data[11];
  int32_T c1_loop_ub;
  int32_T c1_i89;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_strAux = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_strAux), &c1_thisId,
                        c1_y_data, c1_y_sizes);
  sf_mex_destroy(&c1_strAux);
  c1_outData_sizes[0] = 1;
  c1_outData_sizes[1] = c1_y_sizes[1];
  c1_loop_ub = c1_y_sizes[1] - 1;
  for (c1_i89 = 0; c1_i89 <= c1_loop_ub; c1_i89++) {
    c1_outData_data[c1_outData_sizes[0] * c1_i89] = c1_y_data[c1_y_sizes[0] *
      c1_i89];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, char_T
  c1_inData_data[144], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes[2];
  int32_T c1_loop_ub;
  int32_T c1_i90;
  char_T c1_b_inData_data[144];
  int32_T c1_u_sizes[2];
  int32_T c1_b_loop_ub;
  int32_T c1_i91;
  char_T c1_u_data[144];
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes[0] = 1;
  c1_b_inData_sizes[1] = c1_inData_sizes[1];
  c1_loop_ub = c1_inData_sizes[1] - 1;
  for (c1_i90 = 0; c1_i90 <= c1_loop_ub; c1_i90++) {
    c1_b_inData_data[c1_b_inData_sizes[0] * c1_i90] =
      c1_inData_data[c1_inData_sizes[0] * c1_i90];
  }

  c1_u_sizes[0] = 1;
  c1_u_sizes[1] = c1_b_inData_sizes[1];
  c1_b_loop_ub = c1_b_inData_sizes[1] - 1;
  for (c1_i91 = 0; c1_i91 <= c1_b_loop_ub; c1_i91++) {
    c1_u_data[c1_u_sizes[0] * c1_i91] = c1_b_inData_data[c1_b_inData_sizes[0] *
      c1_i91];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 10, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_h_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y_data
  [144], int32_T c1_y_sizes[2])
{
  int32_T c1_i92;
  uint32_T c1_uv3[2];
  int32_T c1_i93;
  static boolean_T c1_bv2[2] = { FALSE, TRUE };

  boolean_T c1_bv3[2];
  int32_T c1_tmp_sizes[2];
  char_T c1_tmp_data[144];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i94;
  for (c1_i92 = 0; c1_i92 < 2; c1_i92++) {
    c1_uv3[c1_i92] = 1U + 143U * (uint32_T)c1_i92;
  }

  for (c1_i93 = 0; c1_i93 < 2; c1_i93++) {
    c1_bv3[c1_i93] = c1_bv2[c1_i93];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 10, 0U, 1, 0U,
                   2, c1_bv3, c1_uv3, c1_tmp_sizes);
  c1_y_sizes[0] = 1;
  c1_y_sizes[1] = c1_tmp_sizes[1];
  c1_y = c1_y_sizes[0];
  c1_b_y = c1_y_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i94 = 0; c1_i94 <= c1_loop_ub; c1_i94++) {
    c1_y_data[c1_i94] = c1_tmp_data[c1_i94];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, char_T c1_outData_data[144],
  int32_T c1_outData_sizes[2])
{
  const mxArray *c1_cmd;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes[2];
  char_T c1_y_data[144];
  int32_T c1_loop_ub;
  int32_T c1_i95;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_cmd = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_cmd), &c1_thisId, c1_y_data,
                        c1_y_sizes);
  sf_mex_destroy(&c1_cmd);
  c1_outData_sizes[0] = 1;
  c1_outData_sizes[1] = c1_y_sizes[1];
  c1_loop_ub = c1_y_sizes[1] - 1;
  for (c1_i95 = 0; c1_i95 <= c1_loop_ub; c1_i95++) {
    c1_outData_data[c1_outData_sizes[0] * c1_i95] = c1_y_data[c1_y_sizes[0] *
      c1_i95];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c1_inData_data[11], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes[2];
  int32_T c1_loop_ub;
  int32_T c1_i96;
  uint8_T c1_b_inData_data[11];
  int32_T c1_u_sizes[2];
  int32_T c1_b_loop_ub;
  int32_T c1_i97;
  uint8_T c1_u_data[11];
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes[0] = 1;
  c1_b_inData_sizes[1] = c1_inData_sizes[1];
  c1_loop_ub = c1_inData_sizes[1] - 1;
  for (c1_i96 = 0; c1_i96 <= c1_loop_ub; c1_i96++) {
    c1_b_inData_data[c1_b_inData_sizes[0] * c1_i96] =
      c1_inData_data[c1_inData_sizes[0] * c1_i96];
  }

  c1_u_sizes[0] = 1;
  c1_u_sizes[1] = c1_b_inData_sizes[1];
  c1_b_loop_ub = c1_b_inData_sizes[1] - 1;
  for (c1_i97 = 0; c1_i97 <= c1_b_loop_ub; c1_i97++) {
    c1_u_data[c1_u_sizes[0] * c1_i97] = c1_b_inData_data[c1_b_inData_sizes[0] *
      c1_i97];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 3, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_i_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y_data
  [11], int32_T c1_y_sizes[2])
{
  int32_T c1_i98;
  uint32_T c1_uv4[2];
  int32_T c1_i99;
  static boolean_T c1_bv4[2] = { FALSE, TRUE };

  boolean_T c1_bv5[2];
  int32_T c1_tmp_sizes[2];
  uint8_T c1_tmp_data[11];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i100;
  for (c1_i98 = 0; c1_i98 < 2; c1_i98++) {
    c1_uv4[c1_i98] = 1U + 10U * (uint32_T)c1_i98;
  }

  for (c1_i99 = 0; c1_i99 < 2; c1_i99++) {
    c1_bv5[c1_i99] = c1_bv4[c1_i99];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c1_bv5, c1_uv4, c1_tmp_sizes);
  c1_y_sizes[0] = 1;
  c1_y_sizes[1] = c1_tmp_sizes[1];
  c1_y = c1_y_sizes[0];
  c1_b_y = c1_y_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i100 = 0; c1_i100 <= c1_loop_ub; c1_i100++) {
    c1_y_data[c1_i100] = c1_tmp_data[c1_i100];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, uint8_T c1_outData_data[11],
  int32_T c1_outData_sizes[2])
{
  const mxArray *c1_digit;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes[2];
  uint8_T c1_y_data[11];
  int32_T c1_loop_ub;
  int32_T c1_i101;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_digit = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_digit), &c1_thisId,
                        c1_y_data, c1_y_sizes);
  sf_mex_destroy(&c1_digit);
  c1_outData_sizes[0] = 1;
  c1_outData_sizes[1] = c1_y_sizes[1];
  c1_loop_ub = c1_y_sizes[1] - 1;
  for (c1_i101 = 0; c1_i101 <= c1_loop_ub; c1_i101++) {
    c1_outData_data[c1_outData_sizes[0] * c1_i101] = c1_y_data[c1_y_sizes[0] *
      c1_i101];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_j_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i102;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i102, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i102;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_iVal;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_iVal = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_iVal), &c1_thisId);
  sf_mex_destroy(&c1_iVal);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i103;
  char_T c1_b_inData[32];
  int32_T c1_i104;
  char_T c1_u[32];
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i103 = 0; c1_i103 < 32; c1_i103++) {
    c1_b_inData[c1_i103] = (*(char_T (*)[32])c1_inData)[c1_i103];
  }

  for (c1_i104 = 0; c1_i104 < 32; c1_i104++) {
    c1_u[c1_i104] = c1_b_inData[c1_i104];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 32), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_k_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[32])
{
  char_T c1_cv11[32];
  int32_T c1_i105;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_cv11, 1, 10, 0U, 1, 0U, 2, 1,
                32);
  for (c1_i105 = 0; c1_i105 < 32; c1_i105++) {
    c1_y[c1_i105] = c1_cv11[c1_i105];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_binData2;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  char_T c1_y[32];
  int32_T c1_i106;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_binData2 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_binData2), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_binData2);
  for (c1_i106 = 0; c1_i106 < 32; c1_i106++) {
    (*(char_T (*)[32])c1_outData)[c1_i106] = c1_y[c1_i106];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i107;
  int32_T c1_i108;
  int32_T c1_i109;
  char_T c1_b_inData[32];
  int32_T c1_i110;
  int32_T c1_i111;
  int32_T c1_i112;
  char_T c1_u[32];
  const mxArray *c1_y = NULL;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i107 = 0;
  for (c1_i108 = 0; c1_i108 < 8; c1_i108++) {
    for (c1_i109 = 0; c1_i109 < 4; c1_i109++) {
      c1_b_inData[c1_i109 + c1_i107] = (*(char_T (*)[32])c1_inData)[c1_i109 +
        c1_i107];
    }

    c1_i107 += 4;
  }

  c1_i110 = 0;
  for (c1_i111 = 0; c1_i111 < 8; c1_i111++) {
    for (c1_i112 = 0; c1_i112 < 4; c1_i112++) {
      c1_u[c1_i112 + c1_i110] = c1_b_inData[c1_i112 + c1_i110];
    }

    c1_i110 += 4;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 4, 8), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_l_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[32])
{
  char_T c1_cv12[32];
  int32_T c1_i113;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_cv12, 1, 10, 0U, 1, 0U, 2, 4,
                8);
  for (c1_i113 = 0; c1_i113 < 32; c1_i113++) {
    c1_y[c1_i113] = c1_cv12[c1_i113];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_binData;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  char_T c1_y[32];
  int32_T c1_i114;
  int32_T c1_i115;
  int32_T c1_i116;
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)chartInstanceVoid;
  c1_binData = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_binData), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_binData);
  c1_i114 = 0;
  for (c1_i115 = 0; c1_i115 < 8; c1_i115++) {
    for (c1_i116 = 0; c1_i116 < 4; c1_i116++) {
      (*(char_T (*)[32])c1_outData)[c1_i116 + c1_i114] = c1_y[c1_i116 + c1_i114];
    }

    c1_i114 += 4;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_ARBlocks_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[60];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i117;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 60), FALSE);
  for (c1_i117 = 0; c1_i117 < 60; c1_i117++) {
    c1_r0 = &c1_info[c1_i117];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i117);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i117);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i117);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i117);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i117);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i117);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i117);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i117);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[60])
{
  c1_info[0].context = "";
  c1_info[0].name = "mod";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c1_info[0].fileTimeLo = 1343830382U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c1_info[1].name = "eml_scalar_eg";
  c1_info[1].dominantType = "double";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[1].fileTimeLo = 1286818796U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c1_info[2].name = "eml_scalexp_alloc";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[2].fileTimeLo = 1352424860U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c1_info[3].name = "eml_scalar_eg";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[3].fileTimeLo = 1286818796U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c1_info[4].name = "eml_scalar_floor";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[4].fileTimeLo = 1286818726U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c1_info[5].name = "eml_scalar_round";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  c1_info[5].fileTimeLo = 1307651238U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c1_info[6].name = "eml_scalar_abs";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[6].fileTimeLo = 1286818712U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c1_info[7].name = "eps";
  c1_info[7].dominantType = "char";
  c1_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[7].fileTimeLo = 1326727996U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[8].name = "eml_is_float_class";
  c1_info[8].dominantType = "char";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c1_info[8].fileTimeLo = 1286818782U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[9].name = "eml_eps";
  c1_info[9].dominantType = "char";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c1_info[9].fileTimeLo = 1326727996U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c1_info[10].name = "eml_float_model";
  c1_info[10].dominantType = "char";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[10].fileTimeLo = 1326727996U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  c1_info[11].name = "mtimes";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[11].fileTimeLo = 1289519692U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context = "";
  c1_info[12].name = "mpower";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[12].fileTimeLo = 1286818842U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[13].name = "power";
  c1_info[13].dominantType = "double";
  c1_info[13].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[13].fileTimeLo = 1348191930U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[14].name = "eml_scalar_eg";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[14].fileTimeLo = 1286818796U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[15].name = "eml_scalexp_alloc";
  c1_info[15].dominantType = "double";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[15].fileTimeLo = 1352424860U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[16].name = "floor";
  c1_info[16].dominantType = "double";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[16].fileTimeLo = 1343830380U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[17].name = "eml_scalar_floor";
  c1_info[17].dominantType = "double";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[17].fileTimeLo = 1286818726U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[18].name = "eml_error";
  c1_info[18].dominantType = "char";
  c1_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[18].fileTimeLo = 1343830358U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c1_info[19].name = "eml_scalar_eg";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[19].fileTimeLo = 1286818796U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context = "";
  c1_info[20].name = "mrdivide";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[20].fileTimeLo = 1357951548U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 1319729966U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[21].name = "rdivide";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[21].fileTimeLo = 1346510388U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[22].name = "eml_scalexp_compatible";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c1_info[22].fileTimeLo = 1286818796U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[23].name = "eml_div";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[23].fileTimeLo = 1313347810U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context = "";
  c1_info[24].name = "char";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c1_info[24].fileTimeLo = 1319729968U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context = "";
  c1_info[25].name = "mtimes";
  c1_info[25].dominantType = "double";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[25].fileTimeLo = 1289519692U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context = "";
  c1_info[26].name = "char";
  c1_info[26].dominantType = "uint8";
  c1_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c1_info[26].fileTimeLo = 1319729968U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context = "";
  c1_info[27].name = "typecast";
  c1_info[27].dominantType = "single";
  c1_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c1_info[27].fileTimeLo = 1323170576U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c1_info[28].name = "eml_float_nbits";
  c1_info[28].dominantType = "char";
  c1_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_nbits.m";
  c1_info[28].fileTimeLo = 1307651242U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
  c1_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_nbits.m";
  c1_info[29].name = "eml_float_model";
  c1_info[29].dominantType = "char";
  c1_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[29].fileTimeLo = 1326727996U;
  c1_info[29].fileTimeHi = 0U;
  c1_info[29].mFileTimeLo = 0U;
  c1_info[29].mFileTimeHi = 0U;
  c1_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c1_info[30].name = "eml_index_rdivide";
  c1_info[30].dominantType = "int32";
  c1_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c1_info[30].fileTimeLo = 1286818780U;
  c1_info[30].fileTimeHi = 0U;
  c1_info[30].mFileTimeLo = 0U;
  c1_info[30].mFileTimeHi = 0U;
  c1_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c1_info[31].name = "eml_index_class";
  c1_info[31].dominantType = "";
  c1_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[31].fileTimeLo = 1323170578U;
  c1_info[31].fileTimeHi = 0U;
  c1_info[31].mFileTimeLo = 0U;
  c1_info[31].mFileTimeHi = 0U;
  c1_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c1_info[32].name = "eml_int_nbits";
  c1_info[32].dominantType = "char";
  c1_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c1_info[32].fileTimeLo = 1323170578U;
  c1_info[32].fileTimeHi = 0U;
  c1_info[32].mFileTimeLo = 0U;
  c1_info[32].mFileTimeHi = 0U;
  c1_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c1_info[33].name = "eml_index_rdivide";
  c1_info[33].dominantType = "uint8";
  c1_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c1_info[33].fileTimeLo = 1286818780U;
  c1_info[33].fileTimeHi = 0U;
  c1_info[33].mFileTimeLo = 0U;
  c1_info[33].mFileTimeHi = 0U;
  c1_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c1_info[34].name = "eml_index_times";
  c1_info[34].dominantType = "double";
  c1_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[34].fileTimeLo = 1286818780U;
  c1_info[34].fileTimeHi = 0U;
  c1_info[34].mFileTimeLo = 0U;
  c1_info[34].mFileTimeHi = 0U;
  c1_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[35].name = "eml_index_class";
  c1_info[35].dominantType = "";
  c1_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[35].fileTimeLo = 1323170578U;
  c1_info[35].fileTimeHi = 0U;
  c1_info[35].mFileTimeLo = 0U;
  c1_info[35].mFileTimeHi = 0U;
  c1_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c1_info[36].name = "eml_index_rdivide";
  c1_info[36].dominantType = "coder.internal.indexInt";
  c1_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c1_info[36].fileTimeLo = 1286818780U;
  c1_info[36].fileTimeHi = 0U;
  c1_info[36].mFileTimeLo = 0U;
  c1_info[36].mFileTimeHi = 0U;
  c1_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c1_info[37].name = "eml_index_times";
  c1_info[37].dominantType = "coder.internal.indexInt";
  c1_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[37].fileTimeLo = 1286818780U;
  c1_info[37].fileTimeHi = 0U;
  c1_info[37].mFileTimeLo = 0U;
  c1_info[37].mFileTimeHi = 0U;
  c1_info[38].context = "";
  c1_info[38].name = "dec2bin";
  c1_info[38].dominantType = "uint8";
  c1_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m";
  c1_info[38].fileTimeLo = 1346510390U;
  c1_info[38].fileTimeHi = 0U;
  c1_info[38].mFileTimeLo = 0U;
  c1_info[38].mFileTimeHi = 0U;
  c1_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m";
  c1_info[39].name = "eml_index_class";
  c1_info[39].dominantType = "";
  c1_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[39].fileTimeLo = 1323170578U;
  c1_info[39].fileTimeHi = 0U;
  c1_info[39].mFileTimeLo = 0U;
  c1_info[39].mFileTimeHi = 0U;
  c1_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!idec2bin";
  c1_info[40].name = "eml_index_class";
  c1_info[40].dominantType = "";
  c1_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[40].fileTimeLo = 1323170578U;
  c1_info[40].fileTimeHi = 0U;
  c1_info[40].mFileTimeLo = 0U;
  c1_info[40].mFileTimeHi = 0U;
  c1_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!idec2bin";
  c1_info[41].name = "eml_unsigned_class";
  c1_info[41].dominantType = "char";
  c1_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c1_info[41].fileTimeLo = 1323170580U;
  c1_info[41].fileTimeHi = 0U;
  c1_info[41].mFileTimeLo = 0U;
  c1_info[41].mFileTimeHi = 0U;
  c1_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!idec2bin";
  c1_info[42].name = "eml_int_nbits";
  c1_info[42].dominantType = "char";
  c1_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c1_info[42].fileTimeLo = 1323170578U;
  c1_info[42].fileTimeHi = 0U;
  c1_info[42].mFileTimeLo = 0U;
  c1_info[42].mFileTimeHi = 0U;
  c1_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!idec2bin";
  c1_info[43].name = "eml_int_forloop_overflow_check";
  c1_info[43].dominantType = "";
  c1_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[43].fileTimeLo = 1346510340U;
  c1_info[43].fileTimeHi = 0U;
  c1_info[43].mFileTimeLo = 0U;
  c1_info[43].mFileTimeHi = 0U;
  c1_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c1_info[44].name = "intmax";
  c1_info[44].dominantType = "char";
  c1_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[44].fileTimeLo = 1311255316U;
  c1_info[44].fileTimeHi = 0U;
  c1_info[44].mFileTimeLo = 0U;
  c1_info[44].mFileTimeHi = 0U;
  c1_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!idec2bin";
  c1_info[45].name = "bitget";
  c1_info[45].dominantType = "uint8";
  c1_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c1_info[45].fileTimeLo = 1344472036U;
  c1_info[45].fileTimeHi = 0U;
  c1_info[45].mFileTimeLo = 0U;
  c1_info[45].mFileTimeHi = 0U;
  c1_info[46].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c1_info[46].name = "eml_scalar_eg";
  c1_info[46].dominantType = "uint8";
  c1_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[46].fileTimeLo = 1286818796U;
  c1_info[46].fileTimeHi = 0U;
  c1_info[46].mFileTimeLo = 0U;
  c1_info[46].mFileTimeHi = 0U;
  c1_info[47].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c1_info[47].name = "eml_scalexp_alloc";
  c1_info[47].dominantType = "uint8";
  c1_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[47].fileTimeLo = 1352424860U;
  c1_info[47].fileTimeHi = 0U;
  c1_info[47].mFileTimeLo = 0U;
  c1_info[47].mFileTimeHi = 0U;
  c1_info[48].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c1_info[48].name = "eml_int_nbits";
  c1_info[48].dominantType = "char";
  c1_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c1_info[48].fileTimeLo = 1323170578U;
  c1_info[48].fileTimeHi = 0U;
  c1_info[48].mFileTimeLo = 0U;
  c1_info[48].mFileTimeHi = 0U;
  c1_info[49].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c1_info[49].name = "floor";
  c1_info[49].dominantType = "coder.internal.indexInt";
  c1_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[49].fileTimeLo = 1343830380U;
  c1_info[49].fileTimeHi = 0U;
  c1_info[49].mFileTimeLo = 0U;
  c1_info[49].mFileTimeHi = 0U;
  c1_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[50].name = "eml_scalar_floor";
  c1_info[50].dominantType = "coder.internal.indexInt";
  c1_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[50].fileTimeLo = 1286818726U;
  c1_info[50].fileTimeHi = 0U;
  c1_info[50].mFileTimeLo = 0U;
  c1_info[50].mFileTimeHi = 0U;
  c1_info[51].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c1_info[51].name = "eml_error";
  c1_info[51].dominantType = "uint8";
  c1_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[51].fileTimeLo = 1343830358U;
  c1_info[51].fileTimeHi = 0U;
  c1_info[51].mFileTimeLo = 0U;
  c1_info[51].mFileTimeHi = 0U;
  c1_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!idec2bin";
  c1_info[52].name = "eml_index_minus";
  c1_info[52].dominantType = "coder.internal.indexInt";
  c1_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[52].fileTimeLo = 1286818778U;
  c1_info[52].fileTimeHi = 0U;
  c1_info[52].mFileTimeLo = 0U;
  c1_info[52].mFileTimeHi = 0U;
  c1_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[53].name = "eml_index_class";
  c1_info[53].dominantType = "";
  c1_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[53].fileTimeLo = 1323170578U;
  c1_info[53].fileTimeHi = 0U;
  c1_info[53].mFileTimeLo = 0U;
  c1_info[53].mFileTimeHi = 0U;
  c1_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!idec2bin";
  c1_info[54].name = "eml_index_plus";
  c1_info[54].dominantType = "double";
  c1_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[54].fileTimeLo = 1286818778U;
  c1_info[54].fileTimeHi = 0U;
  c1_info[54].mFileTimeLo = 0U;
  c1_info[54].mFileTimeHi = 0U;
  c1_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[55].name = "eml_index_class";
  c1_info[55].dominantType = "";
  c1_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[55].fileTimeLo = 1323170578U;
  c1_info[55].fileTimeHi = 0U;
  c1_info[55].mFileTimeLo = 0U;
  c1_info[55].mFileTimeHi = 0U;
  c1_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2bin.m!trim";
  c1_info[56].name = "eml_index_class";
  c1_info[56].dominantType = "";
  c1_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[56].fileTimeLo = 1323170578U;
  c1_info[56].fileTimeHi = 0U;
  c1_info[56].mFileTimeLo = 0U;
  c1_info[56].mFileTimeHi = 0U;
  c1_info[57].context = "";
  c1_info[57].name = "abs";
  c1_info[57].dominantType = "double";
  c1_info[57].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[57].fileTimeLo = 1343830366U;
  c1_info[57].fileTimeHi = 0U;
  c1_info[57].mFileTimeLo = 0U;
  c1_info[57].mFileTimeHi = 0U;
  c1_info[58].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[58].name = "eml_scalar_abs";
  c1_info[58].dominantType = "double";
  c1_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[58].fileTimeLo = 1286818712U;
  c1_info[58].fileTimeHi = 0U;
  c1_info[58].mFileTimeLo = 0U;
  c1_info[58].mFileTimeHi = 0U;
  c1_info[59].context = "";
  c1_info[59].name = "length";
  c1_info[59].dominantType = "char";
  c1_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c1_info[59].fileTimeLo = 1303146206U;
  c1_info[59].fileTimeHi = 0U;
  c1_info[59].mFileTimeLo = 0U;
  c1_info[59].mFileTimeHi = 0U;
}

static real_T c1_mod(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_x,
                     real_T c1_y)
{
  real_T c1_r;
  real_T c1_xk;
  real_T c1_yk;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_i_x;
  real_T c1_c_y;
  real_T c1_j_x;
  real_T c1_d_y;
  real_T c1_b;
  real_T c1_e_y;
  real_T c1_k_x;
  real_T c1_l_x;
  c1_eml_scalar_eg(chartInstance);
  c1_xk = c1_x;
  c1_yk = c1_y;
  c1_b_x = c1_xk;
  c1_b_y = c1_yk;
  c1_eml_scalar_eg(chartInstance);
  c1_c_x = c1_b_y;
  c1_d_x = c1_c_x;
  c1_d_x = muDoubleScalarFloor(c1_d_x);
  if (c1_b_y == c1_d_x) {
    c1_e_x = c1_b_x / c1_b_y;
    c1_f_x = c1_e_x;
    c1_f_x = muDoubleScalarFloor(c1_f_x);
    c1_r = c1_b_x - c1_f_x * c1_b_y;
  } else {
    c1_r = c1_b_x / c1_b_y;
    c1_g_x = c1_r;
    c1_h_x = c1_g_x;
    c1_h_x = muDoubleScalarRound(c1_h_x);
    c1_i_x = c1_r - c1_h_x;
    c1_c_y = muDoubleScalarAbs(c1_i_x);
    c1_j_x = c1_r;
    c1_d_y = muDoubleScalarAbs(c1_j_x);
    c1_b = c1_d_y;
    c1_e_y = 2.2204460492503131E-16 * c1_b;
    if (c1_c_y <= c1_e_y) {
      c1_r = 0.0;
    } else {
      c1_k_x = c1_r;
      c1_l_x = c1_k_x;
      c1_l_x = muDoubleScalarFloor(c1_l_x);
      c1_r = (c1_r - c1_l_x) * c1_b_y;
    }
  }

  return c1_r;
}

static void c1_eml_scalar_eg(SFc1_ARBlocksInstanceStruct *chartInstance)
{
}

static void c1_getString(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_a,
  char_T c1_strOut_data[11], int32_T c1_strOut_sizes[2])
{
  uint32_T c1_debug_family_var_map[9];
  real_T c1_d;
  int32_T c1_digit_sizes[2];
  uint8_T c1_digit_data[11];
  real_T c1_resTotal;
  real_T c1_k;
  real_T c1_res1;
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  int32_T c1_iv0[2];
  int32_T c1_digit;
  int32_T c1_b_digit;
  int32_T c1_loop_ub;
  int32_T c1_i118;
  real_T c1_b_d;
  int32_T c1_i119;
  int32_T c1_b_k;
  real_T c1_A;
  real_T c1_B;
  real_T c1_x;
  real_T c1_y;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_varargin_1;
  real_T c1_s;
  real_T c1_d3;
  real_T c1_d4;
  char_T c1_c_y;
  real_T c1_b_a;
  real_T c1_b;
  real_T c1_d_y;
  int32_T c1_s_sizes[2];
  int32_T c1_b_s;
  int32_T c1_c_s;
  int32_T c1_b_loop_ub;
  int32_T c1_i120;
  uint8_T c1_s_data[11];
  int32_T c1_i121;
  real_T c1_dv0[2];
  int32_T c1_tmp_sizes[2];
  int32_T c1_iv1[2];
  int32_T c1_i122;
  int32_T c1_i123;
  int32_T c1_c_loop_ub;
  int32_T c1_i124;
  char_T c1_tmp_data[11];
  int32_T c1_i125;
  int32_T c1_b_tmp_sizes;
  int32_T c1_d_loop_ub;
  int32_T c1_i126;
  char_T c1_b_tmp_data[11];
  int32_T c1_i127;
  int32_T c1_strOut[2];
  int32_T c1_e_loop_ub;
  int32_T c1_i128;
  int32_T c1_f_loop_ub;
  int32_T c1_i129;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  boolean_T guard4 = FALSE;
  boolean_T guard5 = FALSE;
  boolean_T guard6 = FALSE;
  boolean_T guard7 = FALSE;
  boolean_T guard8 = FALSE;
  boolean_T guard9 = FALSE;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c1_b_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_digit_data, (const int32_T *)
    &c1_digit_sizes, NULL, 0, 1, (void *)c1_g_sf_marshallOut, (void *)
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_resTotal, 2U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_k, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_res1, 4U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 6U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_a, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_strOut_data, (const int32_T *)
    c1_strOut_sizes, NULL, 0, 8, (void *)c1_e_sf_marshallOut, (void *)
    c1_d_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 138U);
  c1_d = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 140U);
  if (CV_EML_IF(0, 1, 16, c1_a < 10.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 141U);
    c1_d = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 144U);
  guard9 = FALSE;
  if (CV_EML_COND(0, 1, 8, c1_a >= 10.0)) {
    if (CV_EML_COND(0, 1, 9, c1_a < 100.0)) {
      CV_EML_MCDC(0, 1, 4, TRUE);
      CV_EML_IF(0, 1, 17, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 145U);
      c1_d = 2.0;
    } else {
      guard9 = TRUE;
    }
  } else {
    guard9 = TRUE;
  }

  if (guard9 == TRUE) {
    CV_EML_MCDC(0, 1, 4, FALSE);
    CV_EML_IF(0, 1, 17, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 148U);
  guard8 = FALSE;
  if (CV_EML_COND(0, 1, 10, c1_a >= 100.0)) {
    if (CV_EML_COND(0, 1, 11, c1_a < 1000.0)) {
      CV_EML_MCDC(0, 1, 5, TRUE);
      CV_EML_IF(0, 1, 18, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 149U);
      c1_d = 3.0;
    } else {
      guard8 = TRUE;
    }
  } else {
    guard8 = TRUE;
  }

  if (guard8 == TRUE) {
    CV_EML_MCDC(0, 1, 5, FALSE);
    CV_EML_IF(0, 1, 18, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 152U);
  guard7 = FALSE;
  if (CV_EML_COND(0, 1, 12, c1_a >= 1000.0)) {
    if (CV_EML_COND(0, 1, 13, c1_a < 10000.0)) {
      CV_EML_MCDC(0, 1, 6, TRUE);
      CV_EML_IF(0, 1, 19, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 153U);
      c1_d = 4.0;
    } else {
      guard7 = TRUE;
    }
  } else {
    guard7 = TRUE;
  }

  if (guard7 == TRUE) {
    CV_EML_MCDC(0, 1, 6, FALSE);
    CV_EML_IF(0, 1, 19, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 156U);
  guard6 = FALSE;
  if (CV_EML_COND(0, 1, 14, c1_a >= 10000.0)) {
    if (CV_EML_COND(0, 1, 15, c1_a < 100000.0)) {
      CV_EML_MCDC(0, 1, 7, TRUE);
      CV_EML_IF(0, 1, 20, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 157U);
      c1_d = 5.0;
    } else {
      guard6 = TRUE;
    }
  } else {
    guard6 = TRUE;
  }

  if (guard6 == TRUE) {
    CV_EML_MCDC(0, 1, 7, FALSE);
    CV_EML_IF(0, 1, 20, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 160U);
  guard5 = FALSE;
  if (CV_EML_COND(0, 1, 16, c1_a >= 100000.0)) {
    if (CV_EML_COND(0, 1, 17, c1_a < 1.0E+6)) {
      CV_EML_MCDC(0, 1, 8, TRUE);
      CV_EML_IF(0, 1, 21, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 161U);
      c1_d = 6.0;
    } else {
      guard5 = TRUE;
    }
  } else {
    guard5 = TRUE;
  }

  if (guard5 == TRUE) {
    CV_EML_MCDC(0, 1, 8, FALSE);
    CV_EML_IF(0, 1, 21, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 164U);
  guard4 = FALSE;
  if (CV_EML_COND(0, 1, 18, c1_a >= 1.0E+6)) {
    if (CV_EML_COND(0, 1, 19, c1_a < 1.0E+7)) {
      CV_EML_MCDC(0, 1, 9, TRUE);
      CV_EML_IF(0, 1, 22, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 165U);
      c1_d = 7.0;
    } else {
      guard4 = TRUE;
    }
  } else {
    guard4 = TRUE;
  }

  if (guard4 == TRUE) {
    CV_EML_MCDC(0, 1, 9, FALSE);
    CV_EML_IF(0, 1, 22, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 168U);
  guard3 = FALSE;
  if (CV_EML_COND(0, 1, 20, c1_a >= 1.0E+7)) {
    if (CV_EML_COND(0, 1, 21, c1_a < 1.0E+8)) {
      CV_EML_MCDC(0, 1, 10, TRUE);
      CV_EML_IF(0, 1, 23, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 169U);
      c1_d = 8.0;
    } else {
      guard3 = TRUE;
    }
  } else {
    guard3 = TRUE;
  }

  if (guard3 == TRUE) {
    CV_EML_MCDC(0, 1, 10, FALSE);
    CV_EML_IF(0, 1, 23, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 172U);
  guard2 = FALSE;
  if (CV_EML_COND(0, 1, 22, c1_a >= 1.0E+8)) {
    if (CV_EML_COND(0, 1, 23, c1_a < 1.0E+9)) {
      CV_EML_MCDC(0, 1, 11, TRUE);
      CV_EML_IF(0, 1, 24, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 173U);
      c1_d = 9.0;
    } else {
      guard2 = TRUE;
    }
  } else {
    guard2 = TRUE;
  }

  if (guard2 == TRUE) {
    CV_EML_MCDC(0, 1, 11, FALSE);
    CV_EML_IF(0, 1, 24, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 176U);
  guard1 = FALSE;
  if (CV_EML_COND(0, 1, 24, c1_a >= 1.0E+9)) {
    if (CV_EML_COND(0, 1, 25, c1_a < 1.0E+10)) {
      CV_EML_MCDC(0, 1, 12, TRUE);
      CV_EML_IF(0, 1, 25, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 177U);
      c1_d = 10.0;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 12, FALSE);
    CV_EML_IF(0, 1, 25, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 180U);
  if (CV_EML_IF(0, 1, 26, c1_a >= 1.0E+10)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 181U);
    c1_d = 11.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 186U);
  c1_digit_sizes[0] = 1;
  c1_iv0[0] = 1;
  c1_iv0[1] = (int32_T)c1_d;
  c1_digit_sizes[1] = c1_iv0[1];
  c1_digit = c1_digit_sizes[0];
  c1_b_digit = c1_digit_sizes[1];
  c1_loop_ub = (int32_T)c1_d - 1;
  for (c1_i118 = 0; c1_i118 <= c1_loop_ub; c1_i118++) {
    c1_digit_data[c1_i118] = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 187U);
  c1_resTotal = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 189U);
  c1_b_d = c1_d;
  c1_i119 = (int32_T)c1_b_d - 1;
  c1_k = 1.0;
  c1_b_k = 0;
  while (c1_b_k <= c1_i119) {
    c1_k = 1.0 + (real_T)c1_b_k;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 191U);
    c1_A = c1_mod(chartInstance, c1_a, c1_mpower(chartInstance, 10.0, c1_k));
    c1_B = c1_mpower(chartInstance, 10.0, c1_k - 1.0);
    c1_x = c1_A;
    c1_y = c1_B;
    c1_b_x = c1_x;
    c1_b_y = c1_y;
    c1_res1 = c1_b_x / c1_b_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 194U);
    c1_varargin_1 = 48.0 + c1_res1;
    c1_s = c1_varargin_1;
    c1_d3 = muDoubleScalarFloor((real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("char",
      (int32_T)_SFD_INTEGER_CHECK("", c1_s), 0, 255, 0, 2));
    if (muDoubleScalarIsNaN(c1_d3) || muDoubleScalarIsInf(c1_d3)) {
      c1_d4 = 0.0;
    } else {
      c1_d4 = muDoubleScalarRem(c1_d3, 256.0);
    }

    if (c1_d4 < 0.0) {
      c1_c_y = (char_T)(int8_T)-(int8_T)(uint8_T)-c1_d4;
    } else {
      c1_c_y = (char_T)(int8_T)(uint8_T)c1_d4;
    }

    c1_digit_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("digit", (int32_T)
      ((c1_d - c1_k) + 1.0), 1, c1_digit_sizes[1], 1, 0) - 1] = (uint8_T)c1_c_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 195U);
    c1_b_a = c1_mpower(chartInstance, 10.0, c1_k - 1.0);
    c1_b = c1_res1;
    c1_d_y = c1_b_a * c1_b;
    c1_resTotal += c1_d_y;
    c1_b_k++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 199U);
  c1_s_sizes[0] = 1;
  c1_s_sizes[1] = c1_digit_sizes[1];
  c1_b_s = c1_s_sizes[0];
  c1_c_s = c1_s_sizes[1];
  c1_b_loop_ub = c1_digit_sizes[0] * c1_digit_sizes[1] - 1;
  for (c1_i120 = 0; c1_i120 <= c1_b_loop_ub; c1_i120++) {
    c1_s_data[c1_i120] = c1_digit_data[c1_i120];
  }

  for (c1_i121 = 0; c1_i121 < 2; c1_i121++) {
    c1_dv0[c1_i121] = (real_T)c1_s_sizes[c1_i121];
  }

  c1_tmp_sizes[0] = 1;
  c1_iv1[0] = 1;
  c1_iv1[1] = (int32_T)c1_dv0[1];
  c1_tmp_sizes[1] = c1_iv1[1];
  c1_i122 = c1_tmp_sizes[0];
  c1_i123 = c1_tmp_sizes[1];
  c1_c_loop_ub = (int32_T)c1_dv0[1] - 1;
  for (c1_i124 = 0; c1_i124 <= c1_c_loop_ub; c1_i124++) {
    c1_tmp_data[c1_i124] = ' ';
  }

  for (c1_i125 = 0; c1_i125 < 2; c1_i125++) {
    c1_strOut_sizes[c1_i125] = c1_tmp_sizes[c1_i125];
  }

  c1_b_tmp_sizes = c1_s_sizes[1];
  c1_d_loop_ub = c1_s_sizes[1] - 1;
  for (c1_i126 = 0; c1_i126 <= c1_d_loop_ub; c1_i126++) {
    c1_b_tmp_data[c1_i126] = (char_T)(int8_T)c1_s_data[c1_i126];
  }

  _SFD_SIZE_EQ_CHECK_1D(c1_strOut_sizes[1], c1_b_tmp_sizes);
  for (c1_i127 = 0; c1_i127 < 2; c1_i127++) {
    c1_strOut[c1_i127] = c1_strOut_sizes[c1_i127];
  }

  c1_strOut_sizes[0] = c1_strOut[0];
  c1_strOut_sizes[1] = c1_strOut[1];
  c1_e_loop_ub = c1_strOut[1] - 1;
  for (c1_i128 = 0; c1_i128 <= c1_e_loop_ub; c1_i128++) {
    c1_f_loop_ub = c1_strOut[0] - 1;
    for (c1_i129 = 0; c1_i129 <= c1_f_loop_ub; c1_i129++) {
      c1_strOut_data[c1_i129 + c1_strOut_sizes[0] * c1_i128] =
        c1_b_tmp_data[c1_i129 + c1_strOut[0] * c1_i128];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -199);
  _SFD_SYMBOL_SCOPE_POP();
}

static real_T c1_mpower(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_a,
  real_T c1_b)
{
  real_T c1_b_a;
  real_T c1_b_b;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_ak;
  real_T c1_bk;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_ar;
  real_T c1_br;
  c1_b_a = c1_a;
  c1_b_b = c1_b;
  c1_c_a = c1_b_a;
  c1_c_b = c1_b_b;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_c_a;
  c1_bk = c1_c_b;
  c1_d_a = c1_ak;
  c1_d_b = c1_bk;
  c1_eml_scalar_eg(chartInstance);
  c1_ar = c1_d_a;
  c1_br = c1_d_b;
  return muDoubleScalarPower(c1_ar, c1_br);
}

static void c1_char(SFc1_ARBlocksInstanceStruct *chartInstance)
{
}

static int32_T c1_float2IEEE754(SFc1_ARBlocksInstanceStruct *chartInstance,
  real_T c1_fVal)
{
  int32_T c1_iVal;
  uint32_T c1_debug_family_var_map[8];
  char_T c1_binData[32];
  char_T c1_binData2[32];
  real_T c1_k;
  real_T c1_bit;
  real_T c1_b_iVal;
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  real32_T c1_x;
  uint8_T c1_y[4];
  int32_T c1_i130;
  int32_T c1_b_k;
  int32_T c1_c_k;
  uint8_T c1_dk;
  int32_T c1_b;
  int32_T c1_b_b;
  uint8_T c1_a;
  int32_T c1_b_bit;
  int32_T c1_b_x;
  int32_T c1_c_x;
  uint8_T c1_ak;
  int32_T c1_i131;
  uint32_T c1_q0;
  uint32_T c1_qY;
  uint32_T c1_u0;
  uint8_T c1_bitkm1;
  uint8_T c1_c;
  int32_T c1_c_b;
  int32_T c1_b_c;
  int32_T c1_d_b;
  int32_T c1_c_c;
  int32_T c1_i132;
  char_T c1_s[32];
  int32_T c1_i133;
  int32_T c1_i134;
  char_T c1_u[32];
  const mxArray *c1_b_y = NULL;
  int32_T c1_i135;
  int32_T c1_i136;
  int32_T c1_i137;
  int32_T c1_i138;
  int32_T c1_i139;
  int32_T c1_i140;
  int32_T c1_i141;
  int32_T c1_i142;
  int32_T c1_i143;
  char_T c1_b_u[32];
  const mxArray *c1_c_y = NULL;
  int32_T c1_d_k;
  real_T c1_b_a;
  real_T c1_d_y;
  real_T c1_c_a;
  real_T c1_e_b;
  real_T c1_e_y;
  real_T c1_d5;
  int32_T c1_i144;
  int32_T c1_c_u;
  const mxArray *c1_f_y = NULL;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 9U, c1_c_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_binData, 0U, c1_j_sf_marshallOut,
    c1_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_binData2, 1U, c1_i_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_k, 2U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_bit, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_iVal, MAX_uint32_T,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 6U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_fVal, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_iVal, MAX_uint32_T,
    c1_h_sf_marshallOut, c1_g_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 207U);
  c1_x = (real32_T)c1_fVal;
  memcpy(&c1_y[0], &c1_x, 4U);
  for (c1_i130 = 0; c1_i130 < 32; c1_i130++) {
    c1_binData[c1_i130] = '0';
  }

  for (c1_b_k = 1; c1_b_k < 5; c1_b_k++) {
    c1_c_k = c1_b_k - 1;
    c1_dk = c1_y[c1_c_k];
    for (c1_b = 1; c1_b < 9; c1_b++) {
      c1_b_b = c1_b;
      c1_a = c1_dk;
      c1_b_bit = c1_b_b;
      c1_b_x = c1_b_bit;
      c1_c_x = c1_b_x;
      if (c1_b_bit != c1_c_x) {
        c1_eml_error(chartInstance, 8U);
      }

      c1_ak = c1_a;
      c1_i131 = c1_b_bit;
      if (CV_SATURATION_EVAL(4, 0, 0, 0, c1_i131 < 0)) {
        c1_i131 = 0;
      } else {
        if (c1_i131 > 255) {
          c1_i131 = 255;
        }
      }

      c1_q0 = (uint8_T)c1_i131;
      c1_qY = c1_q0 - 1U;
      if (CV_SATURATION_EVAL(4, 0, 0, 0, c1_qY > c1_q0)) {
        c1_qY = 0U;
      }

      c1_u0 = c1_qY;
      if (CV_SATURATION_EVAL(4, 0, 0, 0, c1_u0 > 255U)) {
        c1_u0 = 255U;
      }

      c1_bitkm1 = (uint8_T)c1_u0;
      c1_c = (uint8_T)((real_T)(uint8_T)(c1_ak & (uint8_T)(1 << c1_bitkm1)) !=
                       0.0);
      if (c1_c != 0) {
        c1_c_b = c1_b_b;
        c1_b_c = 8 - c1_c_b;
        c1_d_b = c1_b_c + 1;
        c1_c_c = c1_d_b - 1;
        c1_binData[c1_c_k + (c1_c_c << 2)] = '1';
      }
    }
  }

  for (c1_i132 = 0; c1_i132 < 32; c1_i132++) {
    c1_s[c1_i132] = c1_binData[c1_i132];
  }

  for (c1_i133 = 0; c1_i133 < 32; c1_i133++) {
    c1_binData[c1_i133] = c1_s[c1_i133];
  }

  sf_mex_printf("%s =\\n", "binData");
  for (c1_i134 = 0; c1_i134 < 32; c1_i134++) {
    c1_u[c1_i134] = c1_binData[c1_i134];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 4, 8),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c1_b_y);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 209U);
  c1_i135 = 0;
  for (c1_i136 = 0; c1_i136 < 8; c1_i136++) {
    c1_binData2[c1_i136] = c1_binData[c1_i135 + 3];
    c1_i135 += 4;
  }

  c1_i137 = 0;
  for (c1_i138 = 0; c1_i138 < 8; c1_i138++) {
    c1_binData2[c1_i138 + 8] = c1_binData[c1_i137 + 2];
    c1_i137 += 4;
  }

  c1_i139 = 0;
  for (c1_i140 = 0; c1_i140 < 8; c1_i140++) {
    c1_binData2[c1_i140 + 16] = c1_binData[c1_i139 + 1];
    c1_i139 += 4;
  }

  c1_i141 = 0;
  for (c1_i142 = 0; c1_i142 < 8; c1_i142++) {
    c1_binData2[c1_i142 + 24] = c1_binData[c1_i141];
    c1_i141 += 4;
  }

  sf_mex_printf("%s =\\n", "binData2");
  for (c1_i143 = 0; c1_i143 < 32; c1_i143++) {
    c1_b_u[c1_i143] = c1_binData2[c1_i143];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 32),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c1_c_y);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 210U);
  c1_b_iVal = 0.0;
  _SFD_SYMBOL_SWITCH(4U, 4U);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 211U);
  c1_k = 32.0;
  c1_d_k = 0;
  while (c1_d_k < 32) {
    c1_k = 32.0 + -(real_T)c1_d_k;
    CV_EML_FOR(0, 1, 1, 1);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 213U);
    if (CV_EML_IF(0, 1, 27, c1_binData2[(int32_T)c1_k - 1] == '1')) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 214U);
      c1_bit = 1.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 216U);
      c1_bit = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 219U);
    if (CV_EML_IF(0, 1, 28, c1_k == 1.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 220U);
      c1_b_a = c1_bit;
      c1_d_y = c1_b_a * 2.147483648E+9;
      c1_b_iVal -= c1_d_y;
      _SFD_SYMBOL_SWITCH(4U, 4U);
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 222U);
      c1_c_a = c1_bit;
      c1_e_b = c1_mpower(chartInstance, 2.0, 32.0 - c1_k);
      c1_e_y = c1_c_a * c1_e_b;
      c1_b_iVal += c1_e_y;
      _SFD_SYMBOL_SWITCH(4U, 4U);
    }

    c1_d_k++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 1, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 227U);
  c1_d5 = muDoubleScalarRound(c1_b_iVal);
  if (c1_d5 < 2.147483648E+9) {
    if (CV_SATURATION_EVAL(4, 0, 1, 1, c1_d5 >= -2.147483648E+9)) {
      c1_i144 = (int32_T)c1_d5;
    } else {
      c1_i144 = MIN_int32_T;
    }
  } else if (CV_SATURATION_EVAL(4, 0, 1, 0, c1_d5 >= 2.147483648E+9)) {
    c1_i144 = MAX_int32_T;
  } else {
    c1_i144 = 0;
  }

  c1_iVal = c1_i144;
  _SFD_SYMBOL_SWITCH(4U, 8U);
  sf_mex_printf("%s =\\n", "iVal");
  c1_c_u = c1_iVal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_c_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c1_f_y);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -227);
  _SFD_SYMBOL_SCOPE_POP();
  return c1_iVal;
}

static void c1_eml_error(SFc1_ARBlocksInstanceStruct *chartInstance, uint8_T
  c1_varargin_1)
{
  int32_T c1_i145;
  static char_T c1_cv13[36] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 'b', 'i', 't', 'S', 'e', 't', 'G', 'e', 't', '_', 'B', 'I',
    'T', 'O', 'u', 't', 'O', 'f', 'R', 'a', 'n', 'g', 'e' };

  char_T c1_u[36];
  const mxArray *c1_y = NULL;
  uint8_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  int32_T c1_i146;
  static char_T c1_cv14[5] = { 'u', 'i', 'n', 't', '8' };

  char_T c1_c_u[5];
  const mxArray *c1_c_y = NULL;
  for (c1_i145 = 0; c1_i145 < 36; c1_i145++) {
    c1_u[c1_i145] = c1_cv13[c1_i145];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 36), FALSE);
  c1_b_u = 8U;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  for (c1_i146 = 0; c1_i146 < 5; c1_i146++) {
    c1_c_u[c1_i146] = c1_cv14[c1_i146];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 5),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 3U, 14,
    c1_y, 14, c1_b_y, 14, c1_c_y));
}

static real_T c1_abs(SFc1_ARBlocksInstanceStruct *chartInstance, real_T c1_x)
{
  real_T c1_b_x;
  c1_b_x = c1_x;
  return muDoubleScalarAbs(c1_b_x);
}

static void c1_b_char(SFc1_ARBlocksInstanceStruct *chartInstance)
{
}

static uint8_T c1_m_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_ARBlocks, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_ARBlocks), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_ARBlocks);
  return c1_y;
}

static uint8_T c1_n_emlrt_marshallIn(SFc1_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u1;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u1, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u1;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_ARBlocksInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_ARBlocks_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(652692684U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3982932283U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(794561698U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1371882329U);
}

mxArray *sf_c1_ARBlocks_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("7QWtKIBzkt7jsSGFHoJkDC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(32);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(150);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_ARBlocks_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_ARBlocks(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"dataControl\",},{M[1],M[12],T\"error\",},{M[1],M[10],T\"isFlying\",},{M[4],M[0],T\"SequenceNumber\",S'l','i','p'{{M1x2[167 181],M[0],}}},{M[8],M[0],T\"is_active_c1_ARBlocks\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_ARBlocks_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_ARBlocksInstanceStruct *chartInstance;
    chartInstance = (SFc1_ARBlocksInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ARBlocksMachineNumber_,
           1,
           1,
           1,
           11,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_ARBlocksMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ARBlocksMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ARBlocksMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"status");
          _SFD_SET_DATA_PROPS(1,1,1,0,"fly");
          _SFD_SET_DATA_PROPS(2,1,1,0,"rollAngRef");
          _SFD_SET_DATA_PROPS(3,1,1,0,"pitchAngRef");
          _SFD_SET_DATA_PROPS(4,1,1,0,"yawRateRef");
          _SFD_SET_DATA_PROPS(5,1,1,0,"wRef");
          _SFD_SET_DATA_PROPS(6,1,1,0,"enableRefs");
          _SFD_SET_DATA_PROPS(7,2,0,1,"dataControl");
          _SFD_SET_DATA_PROPS(8,2,0,1,"isFlying");
          _SFD_SET_DATA_PROPS(9,1,1,0,"stop");
          _SFD_SET_DATA_PROPS(10,2,0,1,"error");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,3,29,0,2,0,2,0,26,13);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,3804);
        _SFD_CV_INIT_EML_FCN(0,1,"getString",3862,-1,4635);
        _SFD_CV_INIT_EML_FCN(0,2,"float2IEEE754",4702,-1,5114);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,4755,-1,4798);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,5098,-1,5109);
        _SFD_CV_INIT_EML_IF(0,1,0,248,274,-1,303);
        _SFD_CV_INIT_EML_IF(0,1,1,677,731,-1,898);
        _SFD_CV_INIT_EML_IF(0,1,2,1016,1027,1103,3655);
        _SFD_CV_INIT_EML_IF(0,1,3,1138,1181,1402,1450);
        _SFD_CV_INIT_EML_IF(0,1,4,1402,1450,1557,3636);
        _SFD_CV_INIT_EML_IF(0,1,5,1557,1583,-1,1583);
        _SFD_CV_INIT_EML_IF(0,1,6,1601,1614,3318,3335);
        _SFD_CV_INIT_EML_IF(0,1,7,1643,1660,1875,1910);
        _SFD_CV_INIT_EML_IF(0,1,8,1875,1910,-1,1910);
        _SFD_CV_INIT_EML_IF(0,1,9,2252,2267,-1,2336);
        _SFD_CV_INIT_EML_IF(0,1,10,2523,2539,-1,2608);
        _SFD_CV_INIT_EML_IF(0,1,11,2786,2795,-1,2864);
        _SFD_CV_INIT_EML_IF(0,1,12,3073,3089,-1,3190);
        _SFD_CV_INIT_EML_IF(0,1,13,3318,3333,-1,3335);
        _SFD_CV_INIT_EML_IF(0,1,14,3368,3383,-1,3607);
        _SFD_CV_INIT_EML_IF(0,1,15,3698,3718,3753,3776);
        _SFD_CV_INIT_EML_IF(0,1,16,3904,3913,-1,3926);
        _SFD_CV_INIT_EML_IF(0,1,17,3928,3949,-1,3962);
        _SFD_CV_INIT_EML_IF(0,1,18,3964,3987,-1,4000);
        _SFD_CV_INIT_EML_IF(0,1,19,4002,4027,-1,4040);
        _SFD_CV_INIT_EML_IF(0,1,20,4042,4069,-1,4082);
        _SFD_CV_INIT_EML_IF(0,1,21,4084,4113,-1,4126);
        _SFD_CV_INIT_EML_IF(0,1,22,4128,4159,-1,4172);
        _SFD_CV_INIT_EML_IF(0,1,23,4174,4207,-1,4220);
        _SFD_CV_INIT_EML_IF(0,1,24,4222,4257,-1,4270);
        _SFD_CV_INIT_EML_IF(0,1,25,4272,4309,-1,4323);
        _SFD_CV_INIT_EML_IF(0,1,26,4325,4344,-1,4360);
        _SFD_CV_INIT_EML_IF(0,1,27,4900,4922,4944,4972);
        _SFD_CV_INIT_EML_IF(0,1,28,4982,4991,5030,5080);
        _SFD_CV_INIT_EML_FOR(0,1,0,4423,4433,4605);
        _SFD_CV_INIT_EML_FOR(0,1,1,4877,4891,5089);

        {
          static int condStart[] = { 681, 703 };

          static int condEnd[] = { 699, 731 };

          static int pfixExpr[] = { 0, 1, -2 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,681,731,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1141, 1163 };

          static int condEnd[] = { 1159, 1181 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,1141,1181,2,2,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1409, 1432 };

          static int condEnd[] = { 1428, 1450 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,2,1409,1450,2,4,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1882, 1897 };

          static int condEnd[] = { 1893, 1910 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,3,1882,1910,2,6,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 3932, 3942 };

          static int condEnd[] = { 3938, 3948 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,4,3932,3948,2,8,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 3968, 3979 };

          static int condEnd[] = { 3975, 3986 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,5,3968,3986,2,10,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 4006, 4018 };

          static int condEnd[] = { 4014, 4026 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,6,4006,4026,2,12,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 4046, 4059 };

          static int condEnd[] = { 4055, 4068 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,7,4046,4068,2,14,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 4088, 4102 };

          static int condEnd[] = { 4098, 4112 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,8,4088,4112,2,16,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 4132, 4147 };

          static int condEnd[] = { 4143, 4158 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,9,4132,4158,2,18,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 4178, 4194 };

          static int condEnd[] = { 4190, 4206 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,10,4178,4206,2,20,&(condStart[0]),&(condEnd
            [0]),3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 4226, 4243 };

          static int condEnd[] = { 4239, 4256 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,11,4226,4256,2,22,&(condStart[0]),&(condEnd
            [0]),3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 4276, 4294 };

          static int condEnd[] = { 4290, 4308 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,12,4276,4308,2,24,&(condStart[0]),&(condEnd
            [0]),3,&(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 32;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 150;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)
            c1_c_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);

        {
          real_T *c1_fly;
          real_T *c1_rollAngRef;
          real_T *c1_pitchAngRef;
          real_T *c1_yawRateRef;
          real_T *c1_wRef;
          real_T *c1_enableRefs;
          real_T *c1_isFlying;
          real_T *c1_stop;
          real_T *c1_error;
          real_T (*c1_status)[32];
          uint8_T (*c1_dataControl)[150];
          c1_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c1_stop = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
          c1_isFlying = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_dataControl = (uint8_T (*)[150])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c1_enableRefs = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c1_wRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c1_yawRateRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c1_pitchAngRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c1_rollAngRef = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_fly = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_status = (real_T (*)[32])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_status);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_fly);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_rollAngRef);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_pitchAngRef);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_yawRateRef);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_wRef);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_enableRefs);
          _SFD_SET_DATA_VALUE_PTR(7U, *c1_dataControl);
          _SFD_SET_DATA_VALUE_PTR(8U, c1_isFlying);
          _SFD_SET_DATA_VALUE_PTR(9U, c1_stop);
          _SFD_SET_DATA_VALUE_PTR(10U, c1_error);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ARBlocksMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "1iQHuDZd1agg9VKAsv8VCH";
}

static void sf_opaque_initialize_c1_ARBlocks(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_ARBlocksInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*) chartInstanceVar);
  initialize_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_ARBlocks(void *chartInstanceVar)
{
  enable_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_ARBlocks(void *chartInstanceVar)
{
  disable_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_ARBlocks(void *chartInstanceVar)
{
  sf_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_ARBlocks(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_ARBlocks();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_ARBlocks(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_ARBlocks();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_ARBlocks(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_ARBlocks(S);
}

static void sf_opaque_set_sim_state_c1_ARBlocks(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_ARBlocks(S, st);
}

static void sf_opaque_terminate_c1_ARBlocks(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_ARBlocksInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ARBlocks_optimization_info();
    }

    finalize_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_ARBlocks((SFc1_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_ARBlocks(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_ARBlocks((SFc1_ARBlocksInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ARBlocks_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3760816231U));
  ssSetChecksum1(S,(1705995982U));
  ssSetChecksum2(S,(350734802U));
  ssSetChecksum3(S,(1813171093U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_ARBlocks(SimStruct *S)
{
  SFc1_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc1_ARBlocksInstanceStruct *)utMalloc(sizeof
    (SFc1_ARBlocksInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_ARBlocksInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_ARBlocks;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_ARBlocks;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_ARBlocks;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_ARBlocks;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_ARBlocks;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_ARBlocks;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_ARBlocks;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_ARBlocks;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_ARBlocks;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_ARBlocks;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_ARBlocks;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_ARBlocks_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_ARBlocks(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_ARBlocks(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_ARBlocks(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_ARBlocks_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
