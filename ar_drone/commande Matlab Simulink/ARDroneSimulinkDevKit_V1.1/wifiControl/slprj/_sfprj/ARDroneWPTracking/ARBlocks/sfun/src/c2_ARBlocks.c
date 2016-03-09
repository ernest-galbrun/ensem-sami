/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ARBlocks_sfun.h"
#include "c2_ARBlocks.h"
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
static const char * c2_debug_family_names[16] = { "cksum", "nargin", "nargout",
  "data", "status", "battery", "rollAngle", "pitchAngle", "yawAngle", "height",
  "u", "v", "w", "cksumError", "hPrev", "dataPrev" };

static const char * c2_b_debug_family_names[6] = { "hex", "i", "nargin",
  "nargout", "input", "bin" };

static const char * c2_c_debug_family_names[6] = { "hex_value", "mark", "nargin",
  "nargout", "input", "res" };

static const char * c2_d_debug_family_names[6] = { "hex_value", "mark", "nargin",
  "nargout", "input", "res" };

/* Function Declarations */
static void initialize_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance);
static void initialize_params_c2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance);
static void enable_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance);
static void disable_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance);
static void set_sim_state_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance);
static void sf_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance);
static void c2_chartstep_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance);
static void initSimStructsc2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance);
static void registerMessagesc2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_b_dataPrev, const char_T *c2_identifier, uint8_T c2_y[496]);
static void c2_b_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[496]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_b_hPrev, const char_T *c2_identifier);
static real_T c2_d_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_cksumError, const char_T *c2_identifier);
static real_T c2_f_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real32_T c2_g_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_w, const char_T *c2_identifier);
static real32_T c2_h_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_i_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_status, const char_T *c2_identifier, real_T c2_y[32]);
static void c2_j_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[32]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_k_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[2]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_l_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[4]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, char_T
  c2_inData_data[8], int32_T c2_inData_sizes[2]);
static void c2_m_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y_data[8],
  int32_T c2_y_sizes[2]);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, char_T c2_outData_data[8],
  int32_T c2_outData_sizes[2]);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, char_T
  c2_inData_data[8], int32_T c2_inData_sizes[2]);
static void c2_n_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y_data[8],
  int32_T c2_y_sizes[2]);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, char_T c2_outData_data[8],
  int32_T c2_outData_sizes[2]);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[58]);
static void c2_getDroneState(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T
  c2_input[4], real_T c2_bin[32]);
static void c2_dec2hex(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T c2_d
  [4], char_T c2_s_data[8], int32_T c2_s_sizes[2]);
static real_T c2_decode(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T
  c2_input[4]);
static real_T c2_hex2dec(SFc2_ARBlocksInstanceStruct *chartInstance, char_T
  c2_s_data[8], int32_T c2_s_sizes[2]);
static real32_T c2_b_decode(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T
  c2_input[4]);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_o_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_p_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_ARBlocks, const char_T *c2_identifier);
static uint8_T c2_q_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_ARBlocksInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_hPrev_not_empty = FALSE;
  chartInstance->c2_dataPrev_not_empty = FALSE;
  chartInstance->c2_is_active_c2_ARBlocks = 0U;
}

static void initialize_params_c2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void enable_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_c_hoistedGlobal;
  real_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real32_T c2_d_hoistedGlobal;
  real32_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real32_T c2_e_hoistedGlobal;
  real32_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  int32_T c2_i0;
  real_T c2_f_u[32];
  const mxArray *c2_g_y = NULL;
  real32_T c2_f_hoistedGlobal;
  real32_T c2_g_u;
  const mxArray *c2_h_y = NULL;
  real32_T c2_g_hoistedGlobal;
  real32_T c2_h_u;
  const mxArray *c2_i_y = NULL;
  real32_T c2_h_hoistedGlobal;
  real32_T c2_i_u;
  const mxArray *c2_j_y = NULL;
  real32_T c2_i_hoistedGlobal;
  real32_T c2_j_u;
  const mxArray *c2_k_y = NULL;
  int32_T c2_i1;
  uint8_T c2_k_u[496];
  const mxArray *c2_l_y = NULL;
  real_T c2_j_hoistedGlobal;
  real_T c2_l_u;
  const mxArray *c2_m_y = NULL;
  uint8_T c2_k_hoistedGlobal;
  uint8_T c2_m_u;
  const mxArray *c2_n_y = NULL;
  real_T *c2_battery;
  real_T *c2_cksumError;
  real_T *c2_height;
  real32_T *c2_pitchAngle;
  real32_T *c2_rollAngle;
  real32_T *c2_n_u;
  real32_T *c2_v;
  real32_T *c2_w;
  real32_T *c2_yawAngle;
  real_T (*c2_status)[32];
  c2_cksumError = (real_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_w = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_v = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_n_u = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_height = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_yawAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_pitchAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_rollAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_battery = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_status = (real_T (*)[32])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(13), FALSE);
  c2_hoistedGlobal = *c2_battery;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = *c2_cksumError;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = *c2_height;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_d_hoistedGlobal = *c2_pitchAngle;
  c2_d_u = c2_d_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_e_hoistedGlobal = *c2_rollAngle;
  c2_e_u = c2_e_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  for (c2_i0 = 0; c2_i0 < 32; c2_i0++) {
    c2_f_u[c2_i0] = (*c2_status)[c2_i0];
  }

  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_f_u, 0, 0U, 1U, 0U, 1, 32), FALSE);
  sf_mex_setcell(c2_y, 5, c2_g_y);
  c2_f_hoistedGlobal = *c2_n_u;
  c2_g_u = c2_f_hoistedGlobal;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_g_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 6, c2_h_y);
  c2_g_hoistedGlobal = *c2_v;
  c2_h_u = c2_g_hoistedGlobal;
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_h_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 7, c2_i_y);
  c2_h_hoistedGlobal = *c2_w;
  c2_i_u = c2_h_hoistedGlobal;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_i_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 8, c2_j_y);
  c2_i_hoistedGlobal = *c2_yawAngle;
  c2_j_u = c2_i_hoistedGlobal;
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_j_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 9, c2_k_y);
  for (c2_i1 = 0; c2_i1 < 496; c2_i1++) {
    c2_k_u[c2_i1] = chartInstance->c2_dataPrev[c2_i1];
  }

  c2_l_y = NULL;
  if (!chartInstance->c2_dataPrev_not_empty) {
    sf_mex_assign(&c2_l_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_l_y, sf_mex_create("y", c2_k_u, 3, 0U, 1U, 0U, 1, 496),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 10, c2_l_y);
  c2_j_hoistedGlobal = chartInstance->c2_hPrev;
  c2_l_u = c2_j_hoistedGlobal;
  c2_m_y = NULL;
  if (!chartInstance->c2_hPrev_not_empty) {
    sf_mex_assign(&c2_m_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_m_y, sf_mex_create("y", &c2_l_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c2_y, 11, c2_m_y);
  c2_k_hoistedGlobal = chartInstance->c2_is_active_c2_ARBlocks;
  c2_m_u = c2_k_hoistedGlobal;
  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", &c2_m_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 12, c2_n_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[32];
  int32_T c2_i2;
  uint8_T c2_uv0[496];
  int32_T c2_i3;
  real_T *c2_battery;
  real_T *c2_cksumError;
  real_T *c2_height;
  real32_T *c2_pitchAngle;
  real32_T *c2_rollAngle;
  real32_T *c2_b_u;
  real32_T *c2_v;
  real32_T *c2_w;
  real32_T *c2_yawAngle;
  real_T (*c2_status)[32];
  c2_cksumError = (real_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_w = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_v = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_b_u = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_height = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_yawAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_pitchAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_rollAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_battery = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_status = (real_T (*)[32])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  *c2_battery = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 0)), "battery");
  *c2_cksumError = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 1)), "cksumError");
  *c2_height = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 2)), "height");
  *c2_pitchAngle = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 3)), "pitchAngle");
  *c2_rollAngle = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 4)), "rollAngle");
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 5)),
                        "status", c2_dv0);
  for (c2_i2 = 0; c2_i2 < 32; c2_i2++) {
    (*c2_status)[c2_i2] = c2_dv0[c2_i2];
  }

  *c2_b_u = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    6)), "u");
  *c2_v = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 7)),
    "v");
  *c2_w = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 8)),
    "w");
  *c2_yawAngle = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 9)), "yawAngle");
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 10)),
                      "dataPrev", c2_uv0);
  for (c2_i3 = 0; c2_i3 < 496; c2_i3++) {
    chartInstance->c2_dataPrev[c2_i3] = c2_uv0[c2_i3];
  }

  chartInstance->c2_hPrev = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 11)), "hPrev");
  chartInstance->c2_is_active_c2_ARBlocks = c2_p_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 12)), "is_active_c2_ARBlocks");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_ARBlocks(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance)
{
}

static void sf_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  real_T *c2_battery;
  real32_T *c2_rollAngle;
  real32_T *c2_pitchAngle;
  real32_T *c2_yawAngle;
  real_T *c2_height;
  real32_T *c2_u;
  real32_T *c2_v;
  real32_T *c2_w;
  real_T *c2_cksumError;
  uint8_T (*c2_data)[496];
  real_T (*c2_status)[32];
  c2_cksumError = (real_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_w = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_v = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_u = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_height = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_yawAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_data = (uint8_T (*)[496])ssGetInputPortSignal(chartInstance->S, 0);
  c2_pitchAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_rollAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_battery = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_status = (real_T (*)[32])ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 32; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*c2_status)[c2_i4], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_battery, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_rollAngle, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_pitchAngle, 3U);
  for (c2_i5 = 0; c2_i5 < 496; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c2_data)[c2_i5], 4U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*c2_yawAngle, 5U);
  _SFD_DATA_RANGE_CHECK(*c2_height, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_u, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_v, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_w, 9U);
  _SFD_DATA_RANGE_CHECK(*c2_cksumError, 10U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_ARBlocks(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ARBlocksMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance)
{
  int32_T c2_i6;
  uint8_T c2_data[496];
  uint32_T c2_debug_family_var_map[16];
  real_T c2_cksum[2];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 10.0;
  real_T c2_status[32];
  real_T c2_battery;
  real32_T c2_rollAngle;
  real32_T c2_pitchAngle;
  real32_T c2_yawAngle;
  real_T c2_height;
  real32_T c2_u;
  real32_T c2_v;
  real32_T c2_w;
  real_T c2_cksumError;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  real_T c2_x[488];
  real_T c2_y;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_a;
  real_T c2_b_y;
  real_T c2_b_a;
  real_T c2_c_y;
  real_T c2_c_a;
  real_T c2_d_y;
  real_T c2_b_x;
  real_T c2_c_x;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  uint8_T c2_b_data[4];
  real_T c2_dv1[32];
  int32_T c2_i13;
  int32_T c2_i14;
  uint8_T c2_c_data[4];
  int32_T c2_i15;
  uint8_T c2_d_data[4];
  real32_T c2_A;
  real32_T c2_d_x;
  real32_T c2_e_x;
  int32_T c2_i16;
  uint8_T c2_e_data[4];
  real32_T c2_b_A;
  real32_T c2_f_x;
  real32_T c2_g_x;
  int32_T c2_i17;
  uint8_T c2_f_data[4];
  real32_T c2_c_A;
  real32_T c2_h_x;
  real32_T c2_i_x;
  int32_T c2_i18;
  uint8_T c2_g_data[4];
  real_T c2_d_A;
  real_T c2_j_x;
  real_T c2_k_x;
  int32_T c2_i19;
  uint8_T c2_h_data[4];
  real32_T c2_e_A;
  real32_T c2_l_x;
  real32_T c2_m_x;
  int32_T c2_i20;
  uint8_T c2_i_data[4];
  real32_T c2_f_A;
  real32_T c2_n_x;
  real32_T c2_o_x;
  int32_T c2_i21;
  uint8_T c2_j_data[4];
  real32_T c2_g_A;
  real32_T c2_p_x;
  real32_T c2_q_x;
  int32_T c2_i22;
  real_T *c2_b_battery;
  real32_T *c2_b_rollAngle;
  real32_T *c2_b_pitchAngle;
  real32_T *c2_b_yawAngle;
  real_T *c2_b_height;
  real32_T *c2_b_u;
  real32_T *c2_b_v;
  real32_T *c2_b_w;
  real_T *c2_b_cksumError;
  real_T (*c2_b_status)[32];
  uint8_T (*c2_k_data)[496];
  boolean_T guard1 = FALSE;
  c2_b_cksumError = (real_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_b_w = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_b_v = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_b_u = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_b_height = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_b_yawAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_k_data = (uint8_T (*)[496])ssGetInputPortSignal(chartInstance->S, 0);
  c2_b_pitchAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_b_rollAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_b_battery = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_status = (real_T (*)[32])ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i6 = 0; c2_i6 < 496; c2_i6++) {
    c2_data[c2_i6] = (*c2_k_data)[c2_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 16U, 16U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_cksum, 0U, c2_g_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_data, 3U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_status, 4U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_battery, 5U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_rollAngle, 6U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_pitchAngle, 7U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_yawAngle, 8U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_height, 9U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_u, 10U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v, 11U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_w, 12U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cksumError, 13U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_hPrev, 14U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_dataPrev, 15U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  for (c2_i7 = 0; c2_i7 < 2; c2_i7++) {
    c2_cksum[c2_i7] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_hPrev_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
    chartInstance->c2_hPrev = 0.0;
    chartInstance->c2_hPrev_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c2_dataPrev_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
    for (c2_i8 = 0; c2_i8 < 496; c2_i8++) {
      chartInstance->c2_dataPrev[c2_i8] = 0U;
    }

    chartInstance->c2_dataPrev_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  for (c2_i9 = 0; c2_i9 < 488; c2_i9++) {
    c2_x[c2_i9] = (real_T)c2_data[c2_i9];
  }

  c2_y = c2_x[0];
  for (c2_k = 2; c2_k < 489; c2_k++) {
    c2_b_k = c2_k - 1;
    c2_y += c2_x[c2_b_k];
  }

  c2_cksum[0] = c2_y + 442.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
  c2_a = (real_T)c2_data[493];
  c2_b_y = c2_a * 256.0;
  c2_b_a = (real_T)c2_data[494];
  c2_c_y = c2_b_a * 65536.0;
  c2_c_a = (real_T)c2_data[495];
  c2_d_y = c2_c_a * 1.6777216E+7;
  c2_cksum[1] = (((real_T)c2_data[492] + c2_b_y) + c2_c_y) + c2_d_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  c2_b_x = c2_cksum[0] - c2_cksum[1];
  c2_c_x = c2_b_x;
  c2_cksumError = muDoubleScalarAbs(c2_c_x);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  if (CV_EML_IF(0, 1, 2, (real_T)c2_data[14] == 148.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
    for (c2_i10 = 0; c2_i10 < 496; c2_i10++) {
      chartInstance->c2_dataPrev[c2_i10] = c2_data[c2_i10];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
    for (c2_i11 = 0; c2_i11 < 496; c2_i11++) {
      c2_data[c2_i11] = chartInstance->c2_dataPrev[c2_i11];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
  for (c2_i12 = 0; c2_i12 < 4; c2_i12++) {
    c2_b_data[c2_i12] = c2_data[c2_i12];
  }

  c2_getDroneState(chartInstance, c2_b_data, c2_dv1);
  for (c2_i13 = 0; c2_i13 < 32; c2_i13++) {
    c2_status[c2_i13] = c2_dv1[c2_i13];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
  for (c2_i14 = 0; c2_i14 < 4; c2_i14++) {
    c2_c_data[c2_i14] = c2_data[c2_i14 + 20];
  }

  c2_battery = c2_decode(chartInstance, c2_c_data);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_d_data[c2_i15] = c2_data[c2_i15 + 24];
  }

  c2_A = c2_b_decode(chartInstance, c2_d_data);
  c2_d_x = c2_A;
  c2_e_x = c2_d_x;
  c2_pitchAngle = c2_e_x / 1000.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 40);
  for (c2_i16 = 0; c2_i16 < 4; c2_i16++) {
    c2_e_data[c2_i16] = c2_data[c2_i16 + 28];
  }

  c2_b_A = c2_b_decode(chartInstance, c2_e_data);
  c2_f_x = c2_b_A;
  c2_g_x = c2_f_x;
  c2_rollAngle = c2_g_x / 1000.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 41);
  for (c2_i17 = 0; c2_i17 < 4; c2_i17++) {
    c2_f_data[c2_i17] = c2_data[c2_i17 + 32];
  }

  c2_c_A = c2_b_decode(chartInstance, c2_f_data);
  c2_h_x = c2_c_A;
  c2_i_x = c2_h_x;
  c2_yawAngle = c2_i_x / 1000.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
  for (c2_i18 = 0; c2_i18 < 4; c2_i18++) {
    c2_g_data[c2_i18] = c2_data[c2_i18 + 36];
  }

  c2_d_A = c2_decode(chartInstance, c2_g_data);
  c2_j_x = c2_d_A;
  c2_k_x = c2_j_x;
  c2_height = c2_k_x / 1000.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
    c2_h_data[c2_i19] = c2_data[c2_i19 + 40];
  }

  c2_e_A = c2_b_decode(chartInstance, c2_h_data);
  c2_l_x = c2_e_A;
  c2_m_x = c2_l_x;
  c2_u = c2_m_x / 1000.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
  for (c2_i20 = 0; c2_i20 < 4; c2_i20++) {
    c2_i_data[c2_i20] = c2_data[c2_i20 + 44];
  }

  c2_f_A = c2_b_decode(chartInstance, c2_i_data);
  c2_n_x = c2_f_A;
  c2_o_x = c2_n_x;
  c2_v = c2_o_x / 1000.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 45);
  for (c2_i21 = 0; c2_i21 < 4; c2_i21++) {
    c2_j_data[c2_i21] = c2_data[c2_i21 + 48];
  }

  c2_g_A = c2_b_decode(chartInstance, c2_j_data);
  c2_p_x = c2_g_A;
  c2_q_x = c2_p_x;
  c2_w = c2_q_x / 1000.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
  guard1 = FALSE;
  if (CV_EML_COND(0, 1, 0, c2_status[31] == 1.0)) {
    if (CV_EML_COND(0, 1, 1, c2_height < 0.2)) {
      CV_EML_MCDC(0, 1, 0, TRUE);
      CV_EML_IF(0, 1, 3, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
      c2_height = chartInstance->c2_hPrev;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 3, FALSE);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
    if (CV_EML_IF(0, 1, 4, c2_status[31] == 1.0)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
      chartInstance->c2_hPrev = c2_height;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -52);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i22 = 0; c2_i22 < 32; c2_i22++) {
    (*c2_b_status)[c2_i22] = c2_status[c2_i22];
  }

  *c2_b_battery = c2_battery;
  *c2_b_rollAngle = c2_rollAngle;
  *c2_b_pitchAngle = c2_pitchAngle;
  *c2_b_yawAngle = c2_yawAngle;
  *c2_b_height = c2_height;
  *c2_b_u = c2_u;
  *c2_b_v = c2_v;
  *c2_b_w = c2_w;
  *c2_b_cksumError = c2_cksumError;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_ARBlocks(SFc2_ARBlocksInstanceStruct *chartInstance)
{
}

static void registerMessagesc2_ARBlocks(SFc2_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i23;
  uint8_T c2_b_inData[496];
  int32_T c2_i24;
  uint8_T c2_u[496];
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i23 = 0; c2_i23 < 496; c2_i23++) {
    c2_b_inData[c2_i23] = (*(uint8_T (*)[496])c2_inData)[c2_i23];
  }

  for (c2_i24 = 0; c2_i24 < 496; c2_i24++) {
    c2_u[c2_i24] = c2_b_inData[c2_i24];
  }

  c2_y = NULL;
  if (!chartInstance->c2_dataPrev_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 3, 0U, 1U, 0U, 1, 496), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_b_dataPrev, const char_T *c2_identifier, uint8_T c2_y[496])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dataPrev), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_b_dataPrev);
}

static void c2_b_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[496])
{
  uint8_T c2_uv1[496];
  int32_T c2_i25;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_dataPrev_not_empty = FALSE;
  } else {
    chartInstance->c2_dataPrev_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_uv1, 1, 3, 0U, 1, 0U, 1, 496);
    for (c2_i25 = 0; c2_i25 < 496; c2_i25++) {
      c2_y[c2_i25] = c2_uv1[c2_i25];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_dataPrev;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y[496];
  int32_T c2_i26;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_b_dataPrev = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dataPrev), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_b_dataPrev);
  for (c2_i26 = 0; c2_i26 < 496; c2_i26++) {
    (*(uint8_T (*)[496])c2_outData)[c2_i26] = c2_y[c2_i26];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_hPrev_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_b_hPrev, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_hPrev), &c2_thisId);
  sf_mex_destroy(&c2_b_hPrev);
  return c2_y;
}

static real_T c2_d_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_hPrev_not_empty = FALSE;
  } else {
    chartInstance->c2_hPrev_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d0;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_hPrev;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_b_hPrev = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_hPrev), &c2_thisId);
  sf_mex_destroy(&c2_b_hPrev);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_cksumError, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_cksumError),
    &c2_thisId);
  sf_mex_destroy(&c2_cksumError);
  return c2_y;
}

static real_T c2_f_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d1;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d1, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d1;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_cksumError;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_cksumError = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_cksumError),
    &c2_thisId);
  sf_mex_destroy(&c2_cksumError);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real32_T c2_g_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_w, const char_T *c2_identifier)
{
  real32_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_w), &c2_thisId);
  sf_mex_destroy(&c2_w);
  return c2_y;
}

static real32_T c2_h_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real32_T c2_y;
  real32_T c2_f0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_f0, 1, 1, 0U, 0, 0U, 0);
  c2_y = c2_f0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_w;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real32_T c2_y;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_w = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_w), &c2_thisId);
  sf_mex_destroy(&c2_w);
  *(real32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i27;
  real_T c2_b_inData[32];
  int32_T c2_i28;
  real_T c2_u[32];
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i27 = 0; c2_i27 < 32; c2_i27++) {
    c2_b_inData[c2_i27] = (*(real_T (*)[32])c2_inData)[c2_i27];
  }

  for (c2_i28 = 0; c2_i28 < 32; c2_i28++) {
    c2_u[c2_i28] = c2_b_inData[c2_i28];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 32), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_status, const char_T *c2_identifier, real_T c2_y[32])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_status), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_status);
}

static void c2_j_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[32])
{
  real_T c2_dv2[32];
  int32_T c2_i29;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 1, 0, 0U, 1, 0U, 1, 32);
  for (c2_i29 = 0; c2_i29 < 32; c2_i29++) {
    c2_y[c2_i29] = c2_dv2[c2_i29];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_status;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[32];
  int32_T c2_i30;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_status = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_status), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_status);
  for (c2_i30 = 0; c2_i30 < 32; c2_i30++) {
    (*(real_T (*)[32])c2_outData)[c2_i30] = c2_y[c2_i30];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i31;
  uint8_T c2_b_inData[496];
  int32_T c2_i32;
  uint8_T c2_u[496];
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i31 = 0; c2_i31 < 496; c2_i31++) {
    c2_b_inData[c2_i31] = (*(uint8_T (*)[496])c2_inData)[c2_i31];
  }

  for (c2_i32 = 0; c2_i32 < 496; c2_i32++) {
    c2_u[c2_i32] = c2_b_inData[c2_i32];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 3, 0U, 1U, 0U, 1, 496), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i33;
  real_T c2_b_inData[2];
  int32_T c2_i34;
  real_T c2_u[2];
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i33 = 0; c2_i33 < 2; c2_i33++) {
    c2_b_inData[c2_i33] = (*(real_T (*)[2])c2_inData)[c2_i33];
  }

  for (c2_i34 = 0; c2_i34 < 2; c2_i34++) {
    c2_u[c2_i34] = c2_b_inData[c2_i34];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 2), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_k_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[2])
{
  real_T c2_dv3[2];
  int32_T c2_i35;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv3, 1, 0, 0U, 1, 0U, 2, 1, 2);
  for (c2_i35 = 0; c2_i35 < 2; c2_i35++) {
    c2_y[c2_i35] = c2_dv3[c2_i35];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_cksum;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[2];
  int32_T c2_i36;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_cksum = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_cksum), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_cksum);
  for (c2_i36 = 0; c2_i36 < 2; c2_i36++) {
    (*(real_T (*)[2])c2_outData)[c2_i36] = c2_y[c2_i36];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i37;
  uint8_T c2_b_inData[4];
  int32_T c2_i38;
  uint8_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i37 = 0; c2_i37 < 4; c2_i37++) {
    c2_b_inData[c2_i37] = (*(uint8_T (*)[4])c2_inData)[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 4; c2_i38++) {
    c2_u[c2_i38] = c2_b_inData[c2_i38];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 3, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_l_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[4])
{
  uint8_T c2_uv2[4];
  int32_T c2_i39;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_uv2, 1, 3, 0U, 1, 0U, 1, 4);
  for (c2_i39 = 0; c2_i39 < 4; c2_i39++) {
    c2_y[c2_i39] = c2_uv2[c2_i39];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_input;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y[4];
  int32_T c2_i40;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_input = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_input), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_input);
  for (c2_i40 = 0; c2_i40 < 4; c2_i40++) {
    (*(uint8_T (*)[4])c2_outData)[c2_i40] = c2_y[c2_i40];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, char_T
  c2_inData_data[8], int32_T c2_inData_sizes[2])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_inData_sizes[2];
  int32_T c2_loop_ub;
  int32_T c2_i41;
  char_T c2_b_inData_data[8];
  int32_T c2_u_sizes[2];
  int32_T c2_b_loop_ub;
  int32_T c2_i42;
  char_T c2_u_data[8];
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_inData_sizes[0] = 1;
  c2_b_inData_sizes[1] = c2_inData_sizes[1];
  c2_loop_ub = c2_inData_sizes[1] - 1;
  for (c2_i41 = 0; c2_i41 <= c2_loop_ub; c2_i41++) {
    c2_b_inData_data[c2_b_inData_sizes[0] * c2_i41] =
      c2_inData_data[c2_inData_sizes[0] * c2_i41];
  }

  c2_u_sizes[0] = 1;
  c2_u_sizes[1] = c2_b_inData_sizes[1];
  c2_b_loop_ub = c2_b_inData_sizes[1] - 1;
  for (c2_i42 = 0; c2_i42 <= c2_b_loop_ub; c2_i42++) {
    c2_u_data[c2_u_sizes[0] * c2_i42] = c2_b_inData_data[c2_b_inData_sizes[0] *
      c2_i42];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 10, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_m_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y_data[8],
  int32_T c2_y_sizes[2])
{
  int32_T c2_i43;
  uint32_T c2_uv3[2];
  int32_T c2_i44;
  static boolean_T c2_bv0[2] = { FALSE, TRUE };

  boolean_T c2_bv1[2];
  int32_T c2_tmp_sizes[2];
  char_T c2_tmp_data[8];
  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i45;
  for (c2_i43 = 0; c2_i43 < 2; c2_i43++) {
    c2_uv3[c2_i43] = 1U + 7U * (uint32_T)c2_i43;
  }

  for (c2_i44 = 0; c2_i44 < 2; c2_i44++) {
    c2_bv1[c2_i44] = c2_bv0[c2_i44];
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_u), c2_tmp_data, 1, 10, 0U, 1, 0U,
                   2, c2_bv1, c2_uv3, c2_tmp_sizes);
  c2_y_sizes[0] = 1;
  c2_y_sizes[1] = c2_tmp_sizes[1];
  c2_y = c2_y_sizes[0];
  c2_b_y = c2_y_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i45 = 0; c2_i45 <= c2_loop_ub; c2_i45++) {
    c2_y_data[c2_i45] = c2_tmp_data[c2_i45];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, char_T c2_outData_data[8],
  int32_T c2_outData_sizes[2])
{
  const mxArray *c2_hex;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y_sizes[2];
  char_T c2_y_data[8];
  int32_T c2_loop_ub;
  int32_T c2_i46;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_hex = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_hex), &c2_thisId, c2_y_data,
                        c2_y_sizes);
  sf_mex_destroy(&c2_hex);
  c2_outData_sizes[0] = 1;
  c2_outData_sizes[1] = c2_y_sizes[1];
  c2_loop_ub = c2_y_sizes[1] - 1;
  for (c2_i46 = 0; c2_i46 <= c2_loop_ub; c2_i46++) {
    c2_outData_data[c2_outData_sizes[0] * c2_i46] = c2_y_data[c2_y_sizes[0] *
      c2_i46];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, char_T
  c2_inData_data[8], int32_T c2_inData_sizes[2])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_inData_sizes[2];
  int32_T c2_loop_ub;
  int32_T c2_i47;
  int32_T c2_i48;
  char_T c2_b_inData_data[8];
  int32_T c2_u_sizes[2];
  int32_T c2_b_loop_ub;
  int32_T c2_i49;
  int32_T c2_i50;
  char_T c2_u_data[8];
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_inData_sizes[0] = 4;
  c2_b_inData_sizes[1] = c2_inData_sizes[1];
  c2_loop_ub = c2_inData_sizes[1] - 1;
  for (c2_i47 = 0; c2_i47 <= c2_loop_ub; c2_i47++) {
    for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
      c2_b_inData_data[c2_i48 + c2_b_inData_sizes[0] * c2_i47] =
        c2_inData_data[c2_i48 + c2_inData_sizes[0] * c2_i47];
    }
  }

  c2_u_sizes[0] = 4;
  c2_u_sizes[1] = c2_b_inData_sizes[1];
  c2_b_loop_ub = c2_b_inData_sizes[1] - 1;
  for (c2_i49 = 0; c2_i49 <= c2_b_loop_ub; c2_i49++) {
    for (c2_i50 = 0; c2_i50 < 4; c2_i50++) {
      c2_u_data[c2_i50 + c2_u_sizes[0] * c2_i49] = c2_b_inData_data[c2_i50 +
        c2_b_inData_sizes[0] * c2_i49];
    }
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 10, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_n_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_y_data[8],
  int32_T c2_y_sizes[2])
{
  int32_T c2_i51;
  static uint32_T c2_uv4[2] = { 4U, 2U };

  uint32_T c2_uv5[2];
  int32_T c2_i52;
  static boolean_T c2_bv2[2] = { FALSE, TRUE };

  boolean_T c2_bv3[2];
  int32_T c2_tmp_sizes[2];
  char_T c2_tmp_data[8];
  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i53;
  for (c2_i51 = 0; c2_i51 < 2; c2_i51++) {
    c2_uv5[c2_i51] = c2_uv4[c2_i51];
  }

  for (c2_i52 = 0; c2_i52 < 2; c2_i52++) {
    c2_bv3[c2_i52] = c2_bv2[c2_i52];
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_u), c2_tmp_data, 1, 10, 0U, 1, 0U,
                   2, c2_bv3, c2_uv5, c2_tmp_sizes);
  c2_y_sizes[0] = 4;
  c2_y_sizes[1] = c2_tmp_sizes[1];
  c2_y = c2_y_sizes[0];
  c2_b_y = c2_y_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i53 = 0; c2_i53 <= c2_loop_ub; c2_i53++) {
    c2_y_data[c2_i53] = c2_tmp_data[c2_i53];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, char_T c2_outData_data[8],
  int32_T c2_outData_sizes[2])
{
  const mxArray *c2_hex;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y_sizes[2];
  char_T c2_y_data[8];
  int32_T c2_loop_ub;
  int32_T c2_i54;
  int32_T c2_i55;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_hex = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_hex), &c2_thisId, c2_y_data,
                        c2_y_sizes);
  sf_mex_destroy(&c2_hex);
  c2_outData_sizes[0] = 4;
  c2_outData_sizes[1] = c2_y_sizes[1];
  c2_loop_ub = c2_y_sizes[1] - 1;
  for (c2_i54 = 0; c2_i54 <= c2_loop_ub; c2_i54++) {
    for (c2_i55 = 0; c2_i55 < 4; c2_i55++) {
      c2_outData_data[c2_i55 + c2_outData_sizes[0] * c2_i54] = c2_y_data[c2_i55
        + c2_y_sizes[0] * c2_i54];
    }
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_ARBlocks_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[58];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i56;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 58), FALSE);
  for (c2_i56 = 0; c2_i56 < 58; c2_i56++) {
    c2_r0 = &c2_info[c2_i56];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i56);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i56);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i56);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i56);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i56);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i56);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i56);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i56);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[58])
{
  c2_info[0].context = "";
  c2_info[0].name = "sum";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[0].fileTimeLo = 1314736612U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[1].name = "isequal";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[1].fileTimeLo = 1286818758U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[2].name = "eml_isequal_core";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[2].fileTimeLo = 1286818786U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[3].name = "eml_const_nonsingleton_dim";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c2_info[3].fileTimeLo = 1286818696U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[4].name = "eml_scalar_eg";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[4].fileTimeLo = 1286818796U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[5].name = "eml_index_class";
  c2_info[5].dominantType = "";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[5].fileTimeLo = 1323170578U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[6].name = "eml_int_forloop_overflow_check";
  c2_info[6].dominantType = "";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[6].fileTimeLo = 1346510340U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[7].name = "intmax";
  c2_info[7].dominantType = "char";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[7].fileTimeLo = 1311255316U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context = "";
  c2_info[8].name = "mtimes";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[8].fileTimeLo = 1289519692U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context = "";
  c2_info[9].name = "mpower";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[9].fileTimeLo = 1286818842U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[10].name = "power";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[10].fileTimeLo = 1348191930U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c2_info[11].name = "eml_scalar_eg";
  c2_info[11].dominantType = "double";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[11].fileTimeLo = 1286818796U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c2_info[12].name = "eml_scalexp_alloc";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[12].fileTimeLo = 1352424860U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c2_info[13].name = "floor";
  c2_info[13].dominantType = "double";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[13].fileTimeLo = 1343830380U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[14].name = "eml_scalar_floor";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[14].fileTimeLo = 1286818726U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c2_info[15].name = "eml_scalar_eg";
  c2_info[15].dominantType = "double";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[15].fileTimeLo = 1286818796U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c2_info[16].name = "mtimes";
  c2_info[16].dominantType = "double";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[16].fileTimeLo = 1289519692U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context = "";
  c2_info[17].name = "abs";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[17].fileTimeLo = 1343830366U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[18].name = "eml_scalar_abs";
  c2_info[18].dominantType = "double";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[18].fileTimeLo = 1286818712U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context = "";
  c2_info[19].name = "dec2hex";
  c2_info[19].dominantType = "uint8";
  c2_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m";
  c2_info[19].fileTimeLo = 1346510390U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m";
  c2_info[20].name = "eml_index_class";
  c2_info[20].dominantType = "";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[20].fileTimeLo = 1323170578U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m!char_nbits";
  c2_info[21].name = "eml_index_class";
  c2_info[21].dominantType = "";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[21].fileTimeLo = 1323170578U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m";
  c2_info[22].name = "eml_int_nbits";
  c2_info[22].dominantType = "char";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c2_info[22].fileTimeLo = 1323170578U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m";
  c2_info[23].name = "mrdivide";
  c2_info[23].dominantType = "double";
  c2_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[23].fileTimeLo = 1357951548U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 1319729966U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[24].name = "rdivide";
  c2_info[24].dominantType = "double";
  c2_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[24].fileTimeLo = 1346510388U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[25].name = "eml_scalexp_compatible";
  c2_info[25].dominantType = "double";
  c2_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[25].fileTimeLo = 1286818796U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[26].name = "eml_div";
  c2_info[26].dominantType = "double";
  c2_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[26].fileTimeLo = 1313347810U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m";
  c2_info[27].name = "ceil";
  c2_info[27].dominantType = "double";
  c2_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c2_info[27].fileTimeLo = 1343830372U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c2_info[28].name = "eml_scalar_ceil";
  c2_info[28].dominantType = "double";
  c2_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_ceil.m";
  c2_info[28].fileTimeLo = 1286818720U;
  c2_info[28].fileTimeHi = 0U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m";
  c2_info[29].name = "eml_int_forloop_overflow_check";
  c2_info[29].dominantType = "";
  c2_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[29].fileTimeLo = 1346510340U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 0U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[30].name = "intmin";
  c2_info[30].dominantType = "char";
  c2_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c2_info[30].fileTimeLo = 1311255318U;
  c2_info[30].fileTimeHi = 0U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m";
  c2_info[31].name = "floor";
  c2_info[31].dominantType = "uint8";
  c2_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[31].fileTimeLo = 1343830380U;
  c2_info[31].fileTimeHi = 0U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
  c2_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[32].name = "eml_scalar_floor";
  c2_info[32].dominantType = "uint8";
  c2_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[32].fileTimeLo = 1286818726U;
  c2_info[32].fileTimeHi = 0U;
  c2_info[32].mFileTimeLo = 0U;
  c2_info[32].mFileTimeHi = 0U;
  c2_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m!trim";
  c2_info[33].name = "eml_index_class";
  c2_info[33].dominantType = "";
  c2_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[33].fileTimeLo = 1323170578U;
  c2_info[33].fileTimeHi = 0U;
  c2_info[33].mFileTimeLo = 0U;
  c2_info[33].mFileTimeHi = 0U;
  c2_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m!trim";
  c2_info[34].name = "eml_index_minus";
  c2_info[34].dominantType = "coder.internal.indexInt";
  c2_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[34].fileTimeLo = 1286818778U;
  c2_info[34].fileTimeHi = 0U;
  c2_info[34].mFileTimeLo = 0U;
  c2_info[34].mFileTimeHi = 0U;
  c2_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[35].name = "eml_index_class";
  c2_info[35].dominantType = "";
  c2_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[35].fileTimeLo = 1323170578U;
  c2_info[35].fileTimeHi = 0U;
  c2_info[35].mFileTimeLo = 0U;
  c2_info[35].mFileTimeHi = 0U;
  c2_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m!trim";
  c2_info[36].name = "eml_index_plus";
  c2_info[36].dominantType = "double";
  c2_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[36].fileTimeLo = 1286818778U;
  c2_info[36].fileTimeHi = 0U;
  c2_info[36].mFileTimeLo = 0U;
  c2_info[36].mFileTimeHi = 0U;
  c2_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[37].name = "eml_index_class";
  c2_info[37].dominantType = "";
  c2_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[37].fileTimeLo = 1323170578U;
  c2_info[37].fileTimeHi = 0U;
  c2_info[37].mFileTimeLo = 0U;
  c2_info[37].mFileTimeHi = 0U;
  c2_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/dec2hex.m!trim";
  c2_info[38].name = "eml_int_forloop_overflow_check";
  c2_info[38].dominantType = "";
  c2_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[38].fileTimeLo = 1346510340U;
  c2_info[38].fileTimeHi = 0U;
  c2_info[38].mFileTimeLo = 0U;
  c2_info[38].mFileTimeHi = 0U;
  c2_info[39].context = "";
  c2_info[39].name = "length";
  c2_info[39].dominantType = "char";
  c2_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[39].fileTimeLo = 1303146206U;
  c2_info[39].fileTimeHi = 0U;
  c2_info[39].mFileTimeLo = 0U;
  c2_info[39].mFileTimeHi = 0U;
  c2_info[40].context = "";
  c2_info[40].name = "hex2dec";
  c2_info[40].dominantType = "char";
  c2_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/hex2dec.m";
  c2_info[40].fileTimeLo = 1311255326U;
  c2_info[40].fileTimeHi = 0U;
  c2_info[40].mFileTimeLo = 0U;
  c2_info[40].mFileTimeHi = 0U;
  c2_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/hex2dec.m!local_hex2dec";
  c2_info[41].name = "mtimes";
  c2_info[41].dominantType = "double";
  c2_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[41].fileTimeLo = 1289519692U;
  c2_info[41].fileTimeHi = 0U;
  c2_info[41].mFileTimeLo = 0U;
  c2_info[41].mFileTimeHi = 0U;
  c2_info[42].context = "";
  c2_info[42].name = "typecast";
  c2_info[42].dominantType = "uint32";
  c2_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c2_info[42].fileTimeLo = 1323170576U;
  c2_info[42].fileTimeHi = 0U;
  c2_info[42].mFileTimeLo = 0U;
  c2_info[42].mFileTimeHi = 0U;
  c2_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c2_info[43].name = "eml_int_nbits";
  c2_info[43].dominantType = "char";
  c2_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c2_info[43].fileTimeLo = 1323170578U;
  c2_info[43].fileTimeHi = 0U;
  c2_info[43].mFileTimeLo = 0U;
  c2_info[43].mFileTimeHi = 0U;
  c2_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c2_info[44].name = "eml_index_rdivide";
  c2_info[44].dominantType = "uint8";
  c2_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c2_info[44].fileTimeLo = 1286818780U;
  c2_info[44].fileTimeHi = 0U;
  c2_info[44].mFileTimeLo = 0U;
  c2_info[44].mFileTimeHi = 0U;
  c2_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c2_info[45].name = "eml_index_class";
  c2_info[45].dominantType = "";
  c2_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[45].fileTimeLo = 1323170578U;
  c2_info[45].fileTimeHi = 0U;
  c2_info[45].mFileTimeLo = 0U;
  c2_info[45].mFileTimeHi = 0U;
  c2_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c2_info[46].name = "eml_float_nbits";
  c2_info[46].dominantType = "char";
  c2_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_nbits.m";
  c2_info[46].fileTimeLo = 1307651242U;
  c2_info[46].fileTimeHi = 0U;
  c2_info[46].mFileTimeLo = 0U;
  c2_info[46].mFileTimeHi = 0U;
  c2_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_nbits.m";
  c2_info[47].name = "eml_float_model";
  c2_info[47].dominantType = "char";
  c2_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[47].fileTimeLo = 1326727996U;
  c2_info[47].fileTimeHi = 0U;
  c2_info[47].mFileTimeLo = 0U;
  c2_info[47].mFileTimeHi = 0U;
  c2_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m!bytes_per_element";
  c2_info[48].name = "eml_index_rdivide";
  c2_info[48].dominantType = "int32";
  c2_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c2_info[48].fileTimeLo = 1286818780U;
  c2_info[48].fileTimeHi = 0U;
  c2_info[48].mFileTimeLo = 0U;
  c2_info[48].mFileTimeHi = 0U;
  c2_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c2_info[49].name = "eml_index_times";
  c2_info[49].dominantType = "double";
  c2_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[49].fileTimeLo = 1286818780U;
  c2_info[49].fileTimeHi = 0U;
  c2_info[49].mFileTimeLo = 0U;
  c2_info[49].mFileTimeHi = 0U;
  c2_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[50].name = "eml_index_class";
  c2_info[50].dominantType = "";
  c2_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[50].fileTimeLo = 1323170578U;
  c2_info[50].fileTimeHi = 0U;
  c2_info[50].mFileTimeLo = 0U;
  c2_info[50].mFileTimeHi = 0U;
  c2_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c2_info[51].name = "eml_index_rdivide";
  c2_info[51].dominantType = "coder.internal.indexInt";
  c2_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m";
  c2_info[51].fileTimeLo = 1286818780U;
  c2_info[51].fileTimeHi = 0U;
  c2_info[51].mFileTimeLo = 0U;
  c2_info[51].mFileTimeHi = 0U;
  c2_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c2_info[52].name = "eml_index_times";
  c2_info[52].dominantType = "coder.internal.indexInt";
  c2_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[52].fileTimeLo = 1286818780U;
  c2_info[52].fileTimeHi = 0U;
  c2_info[52].mFileTimeLo = 0U;
  c2_info[52].mFileTimeHi = 0U;
  c2_info[53].context = "";
  c2_info[53].name = "mrdivide";
  c2_info[53].dominantType = "single";
  c2_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[53].fileTimeLo = 1357951548U;
  c2_info[53].fileTimeHi = 0U;
  c2_info[53].mFileTimeLo = 1319729966U;
  c2_info[53].mFileTimeHi = 0U;
  c2_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[54].name = "rdivide";
  c2_info[54].dominantType = "single";
  c2_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[54].fileTimeLo = 1346510388U;
  c2_info[54].fileTimeHi = 0U;
  c2_info[54].mFileTimeLo = 0U;
  c2_info[54].mFileTimeHi = 0U;
  c2_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[55].name = "eml_scalexp_compatible";
  c2_info[55].dominantType = "single";
  c2_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[55].fileTimeLo = 1286818796U;
  c2_info[55].fileTimeHi = 0U;
  c2_info[55].mFileTimeLo = 0U;
  c2_info[55].mFileTimeHi = 0U;
  c2_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[56].name = "eml_div";
  c2_info[56].dominantType = "single";
  c2_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[56].fileTimeLo = 1313347810U;
  c2_info[56].fileTimeHi = 0U;
  c2_info[56].mFileTimeLo = 0U;
  c2_info[56].mFileTimeHi = 0U;
  c2_info[57].context = "";
  c2_info[57].name = "mrdivide";
  c2_info[57].dominantType = "double";
  c2_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[57].fileTimeLo = 1357951548U;
  c2_info[57].fileTimeHi = 0U;
  c2_info[57].mFileTimeLo = 1319729966U;
  c2_info[57].mFileTimeHi = 0U;
}

static void c2_getDroneState(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T
  c2_input[4], real_T c2_bin[32])
{
  uint32_T c2_debug_family_var_map[6];
  int32_T c2_hex_sizes[2];
  char_T c2_hex_data[8];
  real_T c2_i;
  int32_T c2_b_hex_sizes[2];
  char_T c2_b_hex_data[8];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i57;
  int32_T c2_i58;
  uint8_T c2_b_input[4];
  int32_T c2_tmp_sizes[2];
  char_T c2_tmp_data[8];
  int32_T c2_hex;
  int32_T c2_b_hex;
  int32_T c2_loop_ub;
  int32_T c2_i59;
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_b_loop_ub;
  int32_T c2_i64;
  int32_T c2_c_loop_ub;
  int32_T c2_i65;
  int32_T c2_d_loop_ub;
  int32_T c2_i66;
  int32_T c2_e_loop_ub;
  int32_T c2_i67;
  int32_T c2_x_sizes[2];
  int32_T c2_x;
  int32_T c2_b_x;
  int32_T c2_f_loop_ub;
  int32_T c2_i68;
  char_T c2_x_data[8];
  real_T c2_d2;
  int32_T c2_i69;
  int32_T c2_b_i;
  real_T c2_a;
  real_T c2_d3;
  real_T c2_b_a;
  real_T c2_d4;
  int32_T c2_i70;
  real_T c2_c_a;
  real_T c2_d5;
  real_T c2_d_a;
  real_T c2_d6;
  int32_T c2_i71;
  static real_T c2_dv4[4] = { 1.0, 1.0, 1.0, 0.0 };

  real_T c2_e_a;
  real_T c2_d7;
  real_T c2_f_a;
  real_T c2_d8;
  int32_T c2_i72;
  static real_T c2_dv5[4] = { 1.0, 1.0, 0.0, 1.0 };

  real_T c2_g_a;
  real_T c2_d9;
  real_T c2_h_a;
  real_T c2_d10;
  int32_T c2_i73;
  static real_T c2_dv6[4] = { 1.0, 1.0, 0.0, 0.0 };

  real_T c2_i_a;
  real_T c2_d11;
  real_T c2_j_a;
  real_T c2_d12;
  int32_T c2_i74;
  static real_T c2_dv7[4] = { 1.0, 0.0, 1.0, 1.0 };

  real_T c2_k_a;
  real_T c2_d13;
  real_T c2_l_a;
  real_T c2_d14;
  int32_T c2_i75;
  static real_T c2_dv8[4] = { 1.0, 0.0, 1.0, 0.0 };

  real_T c2_m_a;
  real_T c2_d15;
  real_T c2_n_a;
  real_T c2_d16;
  int32_T c2_i76;
  static real_T c2_dv9[4] = { 1.0, 0.0, 0.0, 1.0 };

  real_T c2_o_a;
  real_T c2_d17;
  real_T c2_p_a;
  real_T c2_d18;
  int32_T c2_i77;
  static real_T c2_dv10[4] = { 1.0, 0.0, 0.0, 0.0 };

  real_T c2_q_a;
  real_T c2_d19;
  real_T c2_r_a;
  real_T c2_d20;
  int32_T c2_i78;
  static real_T c2_dv11[4] = { 0.0, 1.0, 1.0, 1.0 };

  real_T c2_s_a;
  real_T c2_d21;
  real_T c2_t_a;
  real_T c2_d22;
  int32_T c2_i79;
  static real_T c2_dv12[4] = { 0.0, 1.0, 1.0, 0.0 };

  real_T c2_u_a;
  real_T c2_d23;
  real_T c2_v_a;
  real_T c2_d24;
  int32_T c2_i80;
  static real_T c2_dv13[4] = { 0.0, 1.0, 0.0, 1.0 };

  real_T c2_w_a;
  real_T c2_d25;
  real_T c2_x_a;
  real_T c2_d26;
  int32_T c2_i81;
  static real_T c2_dv14[4] = { 0.0, 1.0, 0.0, 0.0 };

  real_T c2_y_a;
  real_T c2_d27;
  real_T c2_ab_a;
  real_T c2_d28;
  int32_T c2_i82;
  static real_T c2_dv15[4] = { 0.0, 0.0, 1.0, 1.0 };

  real_T c2_bb_a;
  real_T c2_d29;
  real_T c2_cb_a;
  real_T c2_d30;
  int32_T c2_i83;
  static real_T c2_dv16[4] = { 0.0, 0.0, 1.0, 0.0 };

  real_T c2_db_a;
  real_T c2_d31;
  real_T c2_eb_a;
  real_T c2_d32;
  int32_T c2_i84;
  static real_T c2_dv17[4] = { 0.0, 0.0, 0.0, 1.0 };

  real_T c2_fb_a;
  real_T c2_d33;
  real_T c2_gb_a;
  real_T c2_d34;
  int32_T c2_i85;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 7U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_hex_data, (const int32_T *)
    &c2_hex_sizes, NULL, 0, -1, (void *)c2_j_sf_marshallOut, (void *)
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_b_hex_data, (const int32_T *)
    &c2_b_hex_sizes, NULL, 0, -1, (void *)c2_i_sf_marshallOut, (void *)
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_input, 4U, c2_h_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_bin, 5U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 74);
  for (c2_i57 = 0; c2_i57 < 32; c2_i57++) {
    c2_bin[c2_i57] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 75);
  for (c2_i58 = 0; c2_i58 < 4; c2_i58++) {
    c2_b_input[c2_i58] = c2_input[c2_i58];
  }

  c2_dec2hex(chartInstance, c2_b_input, c2_tmp_data, c2_tmp_sizes);
  c2_hex_sizes[0] = 4;
  c2_hex_sizes[1] = c2_tmp_sizes[1];
  c2_hex = c2_hex_sizes[0];
  c2_b_hex = c2_hex_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i59 = 0; c2_i59 <= c2_loop_ub; c2_i59++) {
    c2_hex_data[c2_i59] = c2_tmp_data[c2_i59];
  }

  _SFD_SYMBOL_SWITCH(0U, 0U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
  c2_i60 = c2_hex_sizes[1];
  c2_i61 = c2_hex_sizes[1];
  c2_i62 = c2_hex_sizes[1];
  c2_i63 = c2_hex_sizes[1];
  c2_b_hex_sizes[0] = 1;
  c2_b_hex_sizes[1] = ((c2_i60 + c2_i61) + c2_i62) + c2_i63;
  c2_b_loop_ub = c2_i60 - 1;
  for (c2_i64 = 0; c2_i64 <= c2_b_loop_ub; c2_i64++) {
    c2_b_hex_data[c2_b_hex_sizes[0] * c2_i64] = c2_hex_data[3 + c2_hex_sizes[0] *
      c2_i64];
  }

  c2_c_loop_ub = c2_i61 - 1;
  for (c2_i65 = 0; c2_i65 <= c2_c_loop_ub; c2_i65++) {
    c2_b_hex_data[c2_b_hex_sizes[0] * (c2_i65 + c2_i60)] = c2_hex_data[2 +
      c2_hex_sizes[0] * c2_i65];
  }

  c2_d_loop_ub = c2_i62 - 1;
  for (c2_i66 = 0; c2_i66 <= c2_d_loop_ub; c2_i66++) {
    c2_b_hex_data[c2_b_hex_sizes[0] * ((c2_i66 + c2_i60) + c2_i61)] =
      c2_hex_data[1 + c2_hex_sizes[0] * c2_i66];
  }

  c2_e_loop_ub = c2_i63 - 1;
  for (c2_i67 = 0; c2_i67 <= c2_e_loop_ub; c2_i67++) {
    c2_b_hex_data[c2_b_hex_sizes[0] * (((c2_i67 + c2_i60) + c2_i61) + c2_i62)] =
      c2_hex_data[c2_hex_sizes[0] * c2_i67];
  }

  _SFD_SYMBOL_SWITCH(0U, 2U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
  c2_x_sizes[0] = 1;
  c2_x_sizes[1] = c2_b_hex_sizes[1];
  c2_x = c2_x_sizes[0];
  c2_b_x = c2_x_sizes[1];
  c2_f_loop_ub = c2_b_hex_sizes[0] * c2_b_hex_sizes[1] - 1;
  for (c2_i68 = 0; c2_i68 <= c2_f_loop_ub; c2_i68++) {
    c2_x_data[c2_i68] = c2_b_hex_data[c2_i68];
  }

  c2_d2 = (real_T)c2_x_sizes[1];
  c2_i69 = (int32_T)c2_d2 - 1;
  c2_i = 1.0;
  c2_b_i = 0;
  while (c2_b_i <= c2_i69) {
    c2_i = 1.0 + (real_T)c2_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 79);
    if (CV_EML_IF(0, 1, 6, c2_b_hex_data[(int32_T)(real_T)
                  _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i, 1,
          c2_b_hex_sizes[1], 1, 0) - 1] == 'F')) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 80);
      c2_a = c2_i;
      c2_d3 = c2_a * 4.0;
      c2_b_a = c2_i;
      c2_d4 = c2_b_a * 4.0;
      if (c2_d3 == c2_d4) {
      } else {
        _SFD_RUNTIME_ERROR_MSGID(
          "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
      }

      for (c2_i70 = 0; c2_i70 < 4; c2_i70++) {
        c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin", (int32_T)
          (c2_d3 + (-3.0 + (real_T)c2_i70)), 1, 32, 1, 0) - 1] = 1.0;
      }
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
      if (CV_EML_IF(0, 1, 7, c2_b_hex_data[(int32_T)(real_T)
                    _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i, 1,
            c2_b_hex_sizes[1], 1, 0) - 1] == 'E')) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
        c2_c_a = c2_i;
        c2_d5 = c2_c_a * 4.0;
        c2_d_a = c2_i;
        c2_d6 = c2_d_a * 4.0;
        if (c2_d5 == c2_d6) {
        } else {
          _SFD_RUNTIME_ERROR_MSGID(
            "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
        }

        for (c2_i71 = 0; c2_i71 < 4; c2_i71++) {
          c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin", (int32_T)
            (c2_d5 + (-3.0 + (real_T)c2_i71)), 1, 32, 1, 0) - 1] = c2_dv4[c2_i71];
        }
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 83);
        if (CV_EML_IF(0, 1, 8, c2_b_hex_data[(int32_T)(real_T)
                      _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i, 1,
              c2_b_hex_sizes[1], 1, 0) - 1] == 'D')) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 84);
          c2_e_a = c2_i;
          c2_d7 = c2_e_a * 4.0;
          c2_f_a = c2_i;
          c2_d8 = c2_f_a * 4.0;
          if (c2_d7 == c2_d8) {
          } else {
            _SFD_RUNTIME_ERROR_MSGID(
              "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
          }

          for (c2_i72 = 0; c2_i72 < 4; c2_i72++) {
            c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin", (int32_T)
              (c2_d7 + (-3.0 + (real_T)c2_i72)), 1, 32, 1, 0) - 1] =
              c2_dv5[c2_i72];
          }
        } else {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 85);
          if (CV_EML_IF(0, 1, 9, c2_b_hex_data[(int32_T)(real_T)
                        _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i, 1,
                c2_b_hex_sizes[1], 1, 0) - 1] == 'C')) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 86);
            c2_g_a = c2_i;
            c2_d9 = c2_g_a * 4.0;
            c2_h_a = c2_i;
            c2_d10 = c2_h_a * 4.0;
            if (c2_d9 == c2_d10) {
            } else {
              _SFD_RUNTIME_ERROR_MSGID(
                "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
            }

            for (c2_i73 = 0; c2_i73 < 4; c2_i73++) {
              c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin",
                (int32_T)(c2_d9 + (-3.0 + (real_T)c2_i73)), 1, 32, 1, 0) - 1] =
                c2_dv6[c2_i73];
            }
          } else {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
            if (CV_EML_IF(0, 1, 10, c2_b_hex_data[(int32_T)(real_T)
                          _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i, 1,
                  c2_b_hex_sizes[1], 1, 0) - 1] == 'B')) {
              _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 88);
              c2_i_a = c2_i;
              c2_d11 = c2_i_a * 4.0;
              c2_j_a = c2_i;
              c2_d12 = c2_j_a * 4.0;
              if (c2_d11 == c2_d12) {
              } else {
                _SFD_RUNTIME_ERROR_MSGID(
                  "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
              }

              for (c2_i74 = 0; c2_i74 < 4; c2_i74++) {
                c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin",
                  (int32_T)(c2_d11 + (-3.0 + (real_T)c2_i74)), 1, 32, 1, 0) - 1]
                  = c2_dv7[c2_i74];
              }
            } else {
              _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 89);
              if (CV_EML_IF(0, 1, 11, c2_b_hex_data[(int32_T)(real_T)
                            _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i, 1,
                    c2_b_hex_sizes[1], 1, 0) - 1] == 'A')) {
                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
                c2_k_a = c2_i;
                c2_d13 = c2_k_a * 4.0;
                c2_l_a = c2_i;
                c2_d14 = c2_l_a * 4.0;
                if (c2_d13 == c2_d14) {
                } else {
                  _SFD_RUNTIME_ERROR_MSGID(
                    "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                }

                for (c2_i75 = 0; c2_i75 < 4; c2_i75++) {
                  c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin",
                    (int32_T)(c2_d13 + (-3.0 + (real_T)c2_i75)), 1, 32, 1, 0) -
                    1] = c2_dv8[c2_i75];
                }
              } else {
                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 91);
                if (CV_EML_IF(0, 1, 12, c2_b_hex_data[(int32_T)(real_T)
                              _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i,
                      1, c2_b_hex_sizes[1], 1, 0) - 1] == '9')) {
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
                  c2_m_a = c2_i;
                  c2_d15 = c2_m_a * 4.0;
                  c2_n_a = c2_i;
                  c2_d16 = c2_n_a * 4.0;
                  if (c2_d15 == c2_d16) {
                  } else {
                    _SFD_RUNTIME_ERROR_MSGID(
                      "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                  }

                  for (c2_i76 = 0; c2_i76 < 4; c2_i76++) {
                    c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin",
                      (int32_T)(c2_d15 + (-3.0 + (real_T)c2_i76)), 1, 32, 1, 0)
                      - 1] = c2_dv9[c2_i76];
                  }
                } else {
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 93);
                  if (CV_EML_IF(0, 1, 13, c2_b_hex_data[(int32_T)(real_T)
                                _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)c2_i,
                        1, c2_b_hex_sizes[1], 1, 0) - 1] == '8')) {
                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 94);
                    c2_o_a = c2_i;
                    c2_d17 = c2_o_a * 4.0;
                    c2_p_a = c2_i;
                    c2_d18 = c2_p_a * 4.0;
                    if (c2_d17 == c2_d18) {
                    } else {
                      _SFD_RUNTIME_ERROR_MSGID(
                        "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                    }

                    for (c2_i77 = 0; c2_i77 < 4; c2_i77++) {
                      c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bin",
                        (int32_T)(c2_d17 + (-3.0 + (real_T)c2_i77)), 1, 32, 1, 0)
                        - 1] = c2_dv10[c2_i77];
                    }
                  } else {
                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 95);
                    if (CV_EML_IF(0, 1, 14, c2_b_hex_data[(int32_T)(real_T)
                                  _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)
                          c2_i, 1, c2_b_hex_sizes[1], 1, 0) - 1] == '7')) {
                      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 96);
                      c2_q_a = c2_i;
                      c2_d19 = c2_q_a * 4.0;
                      c2_r_a = c2_i;
                      c2_d20 = c2_r_a * 4.0;
                      if (c2_d19 == c2_d20) {
                      } else {
                        _SFD_RUNTIME_ERROR_MSGID(
                          "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                      }

                      for (c2_i78 = 0; c2_i78 < 4; c2_i78++) {
                        c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
                          "bin", (int32_T)(c2_d19 + (-3.0 + (real_T)c2_i78)), 1,
                          32, 1, 0) - 1] = c2_dv11[c2_i78];
                      }
                    } else {
                      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 97);
                      if (CV_EML_IF(0, 1, 15, c2_b_hex_data[(int32_T)(real_T)
                                    _SFD_EML_ARRAY_BOUNDS_CHECK("hex", (int32_T)
                            c2_i, 1, c2_b_hex_sizes[1], 1, 0) - 1] == '6')) {
                        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 98);
                        c2_s_a = c2_i;
                        c2_d21 = c2_s_a * 4.0;
                        c2_t_a = c2_i;
                        c2_d22 = c2_t_a * 4.0;
                        if (c2_d21 == c2_d22) {
                        } else {
                          _SFD_RUNTIME_ERROR_MSGID(
                            "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                        }

                        for (c2_i79 = 0; c2_i79 < 4; c2_i79++) {
                          c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
                            "bin", (int32_T)(c2_d21 + (-3.0 + (real_T)c2_i79)),
                            1, 32, 1, 0) - 1] = c2_dv12[c2_i79];
                        }
                      } else {
                        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 99);
                        if (CV_EML_IF(0, 1, 16, c2_b_hex_data[(int32_T)(real_T)
                                      _SFD_EML_ARRAY_BOUNDS_CHECK("hex",
                              (int32_T)c2_i, 1, c2_b_hex_sizes[1], 1, 0) - 1] ==
                                      '5')) {
                          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 100);
                          c2_u_a = c2_i;
                          c2_d23 = c2_u_a * 4.0;
                          c2_v_a = c2_i;
                          c2_d24 = c2_v_a * 4.0;
                          if (c2_d23 == c2_d24) {
                          } else {
                            _SFD_RUNTIME_ERROR_MSGID(
                              "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                          }

                          for (c2_i80 = 0; c2_i80 < 4; c2_i80++) {
                            c2_bin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
                              "bin", (int32_T)(c2_d23 + (-3.0 + (real_T)c2_i80)),
                              1, 32, 1, 0) - 1] = c2_dv13[c2_i80];
                          }
                        } else {
                          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 101);
                          if (CV_EML_IF(0, 1, 17, c2_b_hex_data[(int32_T)(real_T)
                                        _SFD_EML_ARRAY_BOUNDS_CHECK("hex",
                                (int32_T)c2_i, 1, c2_b_hex_sizes[1], 1, 0) - 1] ==
                                        '4')) {
                            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 102);
                            c2_w_a = c2_i;
                            c2_d25 = c2_w_a * 4.0;
                            c2_x_a = c2_i;
                            c2_d26 = c2_x_a * 4.0;
                            if (c2_d25 == c2_d26) {
                            } else {
                              _SFD_RUNTIME_ERROR_MSGID(
                                "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                            }

                            for (c2_i81 = 0; c2_i81 < 4; c2_i81++) {
                              c2_bin[(int32_T)(real_T)
                                _SFD_EML_ARRAY_BOUNDS_CHECK("bin", (int32_T)
                                (c2_d25 + (-3.0 + (real_T)c2_i81)), 1, 32, 1, 0)
                                - 1] = c2_dv14[c2_i81];
                            }
                          } else {
                            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 103);
                            if (CV_EML_IF(0, 1, 18, c2_b_hex_data[(int32_T)
                                          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
                                  "hex", (int32_T)c2_i, 1, c2_b_hex_sizes[1], 1,
                                  0) - 1] == '3')) {
                              _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 104);
                              c2_y_a = c2_i;
                              c2_d27 = c2_y_a * 4.0;
                              c2_ab_a = c2_i;
                              c2_d28 = c2_ab_a * 4.0;
                              if (c2_d27 == c2_d28) {
                              } else {
                                _SFD_RUNTIME_ERROR_MSGID(
                                  "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                              }

                              for (c2_i82 = 0; c2_i82 < 4; c2_i82++) {
                                c2_bin[(int32_T)(real_T)
                                  _SFD_EML_ARRAY_BOUNDS_CHECK("bin", (int32_T)
                                  (c2_d27 + (-3.0 + (real_T)c2_i82)), 1, 32, 1,
                                  0) - 1] = c2_dv15[c2_i82];
                              }
                            } else {
                              _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 105);
                              if (CV_EML_IF(0, 1, 19, c2_b_hex_data[(int32_T)
                                            (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
                                    "hex", (int32_T)c2_i, 1, c2_b_hex_sizes[1],
                                    1, 0) - 1] == '2')) {
                                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 106);
                                c2_bb_a = c2_i;
                                c2_d29 = c2_bb_a * 4.0;
                                c2_cb_a = c2_i;
                                c2_d30 = c2_cb_a * 4.0;
                                if (c2_d29 == c2_d30) {
                                } else {
                                  _SFD_RUNTIME_ERROR_MSGID(
                                    "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                                }

                                for (c2_i83 = 0; c2_i83 < 4; c2_i83++) {
                                  c2_bin[(int32_T)(real_T)
                                    _SFD_EML_ARRAY_BOUNDS_CHECK("bin", (int32_T)
                                    (c2_d29 + (-3.0 + (real_T)c2_i83)), 1, 32, 1,
                                    0) - 1] = c2_dv16[c2_i83];
                                }
                              } else {
                                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 107);
                                if (CV_EML_IF(0, 1, 20, c2_b_hex_data[(int32_T)
                                              (real_T)
                                              _SFD_EML_ARRAY_BOUNDS_CHECK("hex",
                                      (int32_T)c2_i, 1, c2_b_hex_sizes[1], 1, 0)
                                              - 1] == '1')) {
                                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent,
                                                108);
                                  c2_db_a = c2_i;
                                  c2_d31 = c2_db_a * 4.0;
                                  c2_eb_a = c2_i;
                                  c2_d32 = c2_eb_a * 4.0;
                                  if (c2_d31 == c2_d32) {
                                  } else {
                                    _SFD_RUNTIME_ERROR_MSGID(
                                      "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                                  }

                                  for (c2_i84 = 0; c2_i84 < 4; c2_i84++) {
                                    c2_bin[(int32_T)(real_T)
                                      _SFD_EML_ARRAY_BOUNDS_CHECK("bin",
                                      (int32_T)(c2_d31 + (-3.0 + (real_T)c2_i84)),
                                      1, 32, 1, 0) - 1] = c2_dv17[c2_i84];
                                  }
                                } else {
                                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent,
                                                109);
                                  if (CV_EML_IF(0, 1, 21, c2_b_hex_data[(int32_T)
                                                (real_T)
                                                _SFD_EML_ARRAY_BOUNDS_CHECK(
                                        "hex", (int32_T)c2_i, 1, c2_b_hex_sizes
                                        [1], 1, 0) - 1] == '0')) {
                                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent,
                                                  110);
                                    c2_fb_a = c2_i;
                                    c2_d33 = c2_fb_a * 4.0;
                                    c2_gb_a = c2_i;
                                    c2_d34 = c2_gb_a * 4.0;
                                    if (c2_d33 == c2_d34) {
                                    } else {
                                      _SFD_RUNTIME_ERROR_MSGID(
                                        "EMLRT:runTime:RepeatedExprWithDifferentResultsInColonIndexing");
                                    }

                                    for (c2_i85 = 0; c2_i85 < 4; c2_i85++) {
                                      c2_bin[(int32_T)(real_T)
                                        _SFD_EML_ARRAY_BOUNDS_CHECK("bin",
                                        (int32_T)(c2_d33 + (-3.0 + (real_T)
                                                            c2_i85)), 1, 32, 1,
                                        0) - 1] = 0.0;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    c2_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -110);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_dec2hex(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T c2_d
  [4], char_T c2_s_data[8], int32_T c2_s_sizes[2])
{
  int32_T c2_i86;
  char_T c2_cv0[8];
  int32_T c2_b_s_sizes[2];
  int32_T c2_s;
  int32_T c2_b_s;
  int32_T c2_i87;
  char_T c2_b_s_data[8];
  int32_T c2_c_s;
  int32_T c2_d_s;
  int32_T c2_loop_ub;
  int32_T c2_i88;
  int32_T c2_i;
  int32_T c2_b_i;
  uint8_T c2_di;
  int32_T c2_i89;
  int32_T c2_j;
  int32_T c2_b_j;
  uint8_T c2_r;
  uint8_T c2_x;
  uint16_T c2_rucls;
  int32_T c2_firstcol;
  int32_T c2_c_j;
  int32_T c2_e_s;
  int32_T c2_f_s;
  int32_T c2_b_loop_ub;
  int32_T c2_i90;
  boolean_T c2_p;
  int32_T c2_c_i;
  real_T c2_d_i;
  int32_T c2_d_j;
  int32_T c2_e_i;
  int32_T c2_f_i;
  int32_T c2_c_s_sizes[2];
  int32_T c2_i91;
  char_T c2_c_s_data[8];
  int32_T c2_c_loop_ub;
  int32_T c2_i92;
  int32_T c2_i93;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  for (c2_i86 = 0; c2_i86 < 8; c2_i86++) {
    c2_cv0[c2_i86] = '0';
  }

  c2_b_s_sizes[0] = 4;
  c2_b_s_sizes[1] = 2;
  c2_s = c2_b_s_sizes[0];
  c2_b_s = c2_b_s_sizes[1];
  for (c2_i87 = 0; c2_i87 < 8; c2_i87++) {
    c2_b_s_data[c2_i87] = c2_cv0[c2_i87];
  }

  c2_s_sizes[0] = 4;
  c2_s_sizes[1] = 2;
  c2_c_s = c2_s_sizes[0];
  c2_d_s = c2_s_sizes[1];
  c2_loop_ub = c2_b_s_sizes[0] * c2_b_s_sizes[1] - 1;
  for (c2_i88 = 0; c2_i88 <= c2_loop_ub; c2_i88++) {
    c2_s_data[c2_i88] = c2_b_s_data[c2_i88];
  }

  for (c2_i = 1; c2_i < 5; c2_i++) {
    c2_b_i = c2_i - 1;
    c2_di = c2_d[c2_b_i];
    c2_i89 = 2;
    exitg3 = FALSE;
    while ((exitg3 == FALSE) && (c2_i89 > 0)) {
      c2_j = c2_i89;
      c2_b_j = c2_j - 1;
      c2_r = c2_di;
      c2_x = (uint8_T)((uint32_T)(int32_T)c2_di >> 4);
      c2_di = c2_x;
      c2_r = (uint8_T)((uint32_T)c2_r - (uint32_T)(uint8_T)(c2_di << 4));
      if ((real_T)c2_r > 9.0) {
        c2_r = (uint8_T)((uint32_T)c2_r + 7U);
      }

      c2_rucls = c2_r;
      c2_rucls;
      c2_s_data[c2_b_i + c2_s_sizes[0] * c2_b_j] = (char_T)(int8_T)(uint16_T)
        ((uint32_T)c2_rucls + 48U);
      if ((real_T)c2_di > 0.0) {
        c2_i89--;
      } else {
        exitg3 = TRUE;
      }
    }
  }

  c2_firstcol = 2;
  c2_c_j = 1;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c2_c_j <= 1)) {
    c2_b_s_sizes[0] = 4;
    c2_b_s_sizes[1] = c2_s_sizes[1];
    c2_e_s = c2_b_s_sizes[0];
    c2_f_s = c2_b_s_sizes[1];
    c2_b_loop_ub = c2_s_sizes[0] * c2_s_sizes[1] - 1;
    for (c2_i90 = 0; c2_i90 <= c2_b_loop_ub; c2_i90++) {
      c2_b_s_data[c2_i90] = c2_s_data[c2_i90];
    }

    c2_p = FALSE;
    c2_c_i = 0;
    exitg2 = FALSE;
    while ((exitg2 == FALSE) && (c2_c_i <= 3)) {
      c2_d_i = 1.0 + (real_T)c2_c_i;
      if (c2_b_s_data[(int32_T)c2_d_i - 1] != '0') {
        c2_p = TRUE;
        exitg2 = TRUE;
      } else {
        c2_c_i++;
      }
    }

    if (c2_p) {
      c2_firstcol = 1;
      exitg1 = TRUE;
    } else {
      c2_c_j = 2;
    }
  }

  if (c2_firstcol > 1) {
    c2_d_j = 2;
    while (c2_d_j <= 2) {
      for (c2_e_i = 1; c2_e_i < 5; c2_e_i++) {
        c2_f_i = c2_e_i - 1;
        c2_s_data[c2_f_i] = c2_s_data[c2_f_i + c2_s_sizes[0]];
      }

      c2_d_j = 3;
    }

    c2_c_s_sizes[0] = 4;
    c2_c_s_sizes[1] = 1;
    for (c2_i91 = 0; c2_i91 < 4; c2_i91++) {
      c2_c_s_data[c2_i91] = c2_s_data[c2_i91];
    }

    c2_s_sizes[0] = 4;
    c2_s_sizes[1] = c2_c_s_sizes[1];
    c2_c_loop_ub = c2_c_s_sizes[1] - 1;
    for (c2_i92 = 0; c2_i92 <= c2_c_loop_ub; c2_i92++) {
      for (c2_i93 = 0; c2_i93 < 4; c2_i93++) {
        c2_s_data[c2_i93 + c2_s_sizes[0] * c2_i92] = c2_c_s_data[c2_i93 +
          c2_c_s_sizes[0] * c2_i92];
      }
    }
  }
}

static real_T c2_decode(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T
  c2_input[4])
{
  real_T c2_res;
  uint32_T c2_debug_family_var_map[6];
  int32_T c2_hex_value_sizes[2];
  char_T c2_hex_value_data[8];
  int32_T c2_b_hex_value_sizes[2];
  char_T c2_b_hex_value_data[8];
  real_T c2_mark;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i94;
  uint8_T c2_b_input[4];
  int32_T c2_tmp_sizes[2];
  char_T c2_tmp_data[8];
  int32_T c2_hex_value;
  int32_T c2_b_hex_value;
  int32_T c2_loop_ub;
  int32_T c2_i95;
  int32_T c2_i96;
  int32_T c2_i97;
  int32_T c2_i98;
  int32_T c2_i99;
  int32_T c2_b_loop_ub;
  int32_T c2_i100;
  int32_T c2_c_loop_ub;
  int32_T c2_i101;
  int32_T c2_d_loop_ub;
  int32_T c2_i102;
  int32_T c2_e_loop_ub;
  int32_T c2_i103;
  int32_T c2_c_hex_value_sizes[2];
  int32_T c2_c_hex_value;
  int32_T c2_d_hex_value;
  int32_T c2_f_loop_ub;
  int32_T c2_i104;
  char_T c2_c_hex_value_data[8];
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 7U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_hex_value_data, (const int32_T *)
    &c2_hex_value_sizes, NULL, 0, -1, (void *)c2_j_sf_marshallOut, (void *)
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_b_hex_value_data, (const int32_T *)
    &c2_b_hex_value_sizes, NULL, 0, -1, (void *)c2_i_sf_marshallOut, (void *)
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mark, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_input, 4U, c2_h_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_res, 5U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  c2_mark = 1.0;
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 64);
  for (c2_i94 = 0; c2_i94 < 4; c2_i94++) {
    c2_b_input[c2_i94] = c2_input[c2_i94];
  }

  c2_dec2hex(chartInstance, c2_b_input, c2_tmp_data, c2_tmp_sizes);
  c2_hex_value_sizes[0] = 4;
  c2_hex_value_sizes[1] = c2_tmp_sizes[1];
  c2_hex_value = c2_hex_value_sizes[0];
  c2_b_hex_value = c2_hex_value_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i95 = 0; c2_i95 <= c2_loop_ub; c2_i95++) {
    c2_hex_value_data[c2_i95] = c2_tmp_data[c2_i95];
  }

  _SFD_SYMBOL_SWITCH(0U, 0U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 65);
  c2_i96 = c2_hex_value_sizes[1];
  c2_i97 = c2_hex_value_sizes[1];
  c2_i98 = c2_hex_value_sizes[1];
  c2_i99 = c2_hex_value_sizes[1];
  c2_b_hex_value_sizes[0] = 1;
  c2_b_hex_value_sizes[1] = ((c2_i96 + c2_i97) + c2_i98) + c2_i99;
  c2_b_loop_ub = c2_i96 - 1;
  for (c2_i100 = 0; c2_i100 <= c2_b_loop_ub; c2_i100++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * c2_i100] = c2_hex_value_data[3
      + c2_hex_value_sizes[0] * c2_i100];
  }

  c2_c_loop_ub = c2_i97 - 1;
  for (c2_i101 = 0; c2_i101 <= c2_c_loop_ub; c2_i101++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * (c2_i101 + c2_i96)] =
      c2_hex_value_data[2 + c2_hex_value_sizes[0] * c2_i101];
  }

  c2_d_loop_ub = c2_i98 - 1;
  for (c2_i102 = 0; c2_i102 <= c2_d_loop_ub; c2_i102++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * ((c2_i102 + c2_i96) + c2_i97)]
      = c2_hex_value_data[1 + c2_hex_value_sizes[0] * c2_i102];
  }

  c2_e_loop_ub = c2_i99 - 1;
  for (c2_i103 = 0; c2_i103 <= c2_e_loop_ub; c2_i103++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * (((c2_i103 + c2_i96) + c2_i97)
      + c2_i98)] = c2_hex_value_data[c2_hex_value_sizes[0] * c2_i103];
  }

  _SFD_SYMBOL_SWITCH(0U, 1U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
  CV_EML_IF(0, 1, 5, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 67);
  c2_c_hex_value_sizes[0] = 1;
  c2_c_hex_value_sizes[1] = c2_b_hex_value_sizes[1];
  c2_c_hex_value = c2_c_hex_value_sizes[0];
  c2_d_hex_value = c2_c_hex_value_sizes[1];
  c2_f_loop_ub = c2_b_hex_value_sizes[0] * c2_b_hex_value_sizes[1] - 1;
  for (c2_i104 = 0; c2_i104 <= c2_f_loop_ub; c2_i104++) {
    c2_c_hex_value_data[c2_i104] = c2_b_hex_value_data[c2_i104];
  }

  c2_res = c2_hex2dec(chartInstance, c2_c_hex_value_data, c2_c_hex_value_sizes);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -69);
  _SFD_SYMBOL_SCOPE_POP();
  return c2_res;
}

static real_T c2_hex2dec(SFc2_ARBlocksInstanceStruct *chartInstance, char_T
  c2_s_data[8], int32_T c2_s_sizes[2])
{
  real_T c2_x;
  real_T c2_d35;
  int32_T c2_i105;
  int32_T c2_k;
  real_T c2_b_k;
  boolean_T c2_b0;
  boolean_T c2_p;
  int32_T c2_i106;
  static char_T c2_cv1[33] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'h', 'e', 'x',
    '2', 'd', 'e', 'c', ':', 'I', 'l', 'l', 'e', 'g', 'a', 'l', 'H', 'e', 'x',
    'a', 'd', 'e', 'c', 'i', 'm', 'a', 'l' };

  char_T c2_u[33];
  const mxArray *c2_y = NULL;
  real_T c2_p16;
  real_T c2_d36;
  int32_T c2_i107;
  int32_T c2_j;
  real_T c2_b_j;
  real_T c2_skj;
  real_T c2_a;
  real_T c2_b;
  real_T c2_b_y;
  real_T c2_b_b;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  boolean_T guard4 = FALSE;
  boolean_T guard5 = FALSE;
  int32_T exitg1;
  c2_d35 = (real_T)c2_s_sizes[1];
  c2_i105 = (int32_T)c2_d35 - 1;
  c2_k = 0;
  do {
    exitg1 = 0;
    if (c2_k <= c2_i105) {
      c2_b_k = 1.0 + (real_T)c2_k;
      guard1 = FALSE;
      guard2 = FALSE;
      guard3 = FALSE;
      guard4 = FALSE;
      guard5 = FALSE;
      if (c2_s_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
           c2_b_k, 1, c2_s_sizes[1], 1, 0) - 1] == ' ') {
        guard4 = TRUE;
      } else if ((real_T)(uint8_T)c2_s_data[(int32_T)(real_T)
                 _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)c2_b_k, 1, c2_s_sizes
                  [1], 1, 0) - 1] == 0.0) {
        guard4 = TRUE;
      } else if (c2_s_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                  (int32_T)c2_b_k, 1, c2_s_sizes[1], 1, 0) - 1] >= 'A') {
        if (c2_s_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
             c2_b_k, 1, c2_s_sizes[1], 1, 0) - 1] <= 'F') {
          guard2 = TRUE;
        } else {
          guard5 = TRUE;
        }
      } else {
        guard5 = TRUE;
      }

      if (guard5 == TRUE) {
        if (c2_s_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
             c2_b_k, 1, c2_s_sizes[1], 1, 0) - 1] >= 'a') {
          guard3 = TRUE;
        } else if (c2_s_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                    (int32_T)c2_b_k, 1, c2_s_sizes[1], 1, 0) - 1] <= 'f') {
          guard3 = TRUE;
        } else {
          c2_b0 = FALSE;
        }
      }

      if (guard4 == TRUE) {
        guard2 = TRUE;
      }

      if (guard3 == TRUE) {
        guard1 = TRUE;
      }

      if (guard2 == TRUE) {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        c2_b0 = TRUE;
      }

      if (!c2_b0) {
        c2_p = FALSE;
        exitg1 = 1;
      } else {
        c2_k++;
      }
    } else {
      c2_p = TRUE;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (c2_p) {
  } else {
    for (c2_i106 = 0; c2_i106 < 33; c2_i106++) {
      c2_u[c2_i106] = c2_cv1[c2_i106];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 33),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
      14, c2_y));
  }

  c2_x = 0.0;
  c2_p16 = 1.0;
  c2_d36 = (real_T)c2_s_sizes[1];
  c2_i107 = (int32_T)-(1.0 + (-1.0 - c2_d36));
  _SFD_FOR_LOOP_VECTOR_CHECK(c2_d36, -1.0, 1.0, mxDOUBLE_CLASS, c2_i107);
  for (c2_j = 0; c2_j < c2_i107; c2_j++) {
    c2_b_j = c2_d36 + -(real_T)c2_j;
    if (c2_s_data[c2_s_sizes[0] * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)c2_b_j, 1, c2_s_sizes[1], 2, 0) - 1)] != ' ') {
      c2_skj = (real_T)(uint8_T)c2_s_data[c2_s_sizes[0] * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)c2_b_j, 1, c2_s_sizes[1], 2, 0)
        - 1)];
      if (c2_skj != 0.0) {
        if (c2_skj != 48.0) {
          if (c2_skj <= 57.0) {
            c2_skj -= 48.0;
          } else if (c2_skj > 70.0) {
            c2_skj = (c2_skj - 97.0) + 10.0;
          } else {
            c2_skj = (c2_skj - 65.0) + 10.0;
          }

          c2_a = c2_skj;
          c2_b = c2_p16;
          c2_b_y = c2_a * c2_b;
          c2_x += c2_b_y;
        }
      }

      c2_b_b = c2_p16;
      c2_p16 = 16.0 * c2_b_b;
    }
  }

  return c2_x;
}

static real32_T c2_b_decode(SFc2_ARBlocksInstanceStruct *chartInstance, uint8_T
  c2_input[4])
{
  real32_T c2_res;
  uint32_T c2_debug_family_var_map[6];
  int32_T c2_hex_value_sizes[2];
  char_T c2_hex_value_data[8];
  int32_T c2_b_hex_value_sizes[2];
  char_T c2_b_hex_value_data[8];
  real_T c2_mark;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i108;
  uint8_T c2_b_input[4];
  int32_T c2_tmp_sizes[2];
  char_T c2_tmp_data[8];
  int32_T c2_hex_value;
  int32_T c2_b_hex_value;
  int32_T c2_loop_ub;
  int32_T c2_i109;
  int32_T c2_i110;
  int32_T c2_i111;
  int32_T c2_i112;
  int32_T c2_i113;
  int32_T c2_b_loop_ub;
  int32_T c2_i114;
  int32_T c2_c_loop_ub;
  int32_T c2_i115;
  int32_T c2_d_loop_ub;
  int32_T c2_i116;
  int32_T c2_e_loop_ub;
  int32_T c2_i117;
  int32_T c2_c_hex_value_sizes[2];
  int32_T c2_c_hex_value;
  int32_T c2_d_hex_value;
  int32_T c2_f_loop_ub;
  int32_T c2_i118;
  char_T c2_c_hex_value_data[8];
  real_T c2_d37;
  uint32_T c2_u0;
  uint32_T c2_x;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 7U, c2_d_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_hex_value_data, (const int32_T *)
    &c2_hex_value_sizes, NULL, 0, -1, (void *)c2_j_sf_marshallOut, (void *)
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_b_hex_value_data, (const int32_T *)
    &c2_b_hex_value_sizes, NULL, 0, -1, (void *)c2_i_sf_marshallOut, (void *)
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mark, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_input, 4U, c2_h_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_res, 5U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  c2_mark = 0.0;
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 64);
  for (c2_i108 = 0; c2_i108 < 4; c2_i108++) {
    c2_b_input[c2_i108] = c2_input[c2_i108];
  }

  c2_dec2hex(chartInstance, c2_b_input, c2_tmp_data, c2_tmp_sizes);
  c2_hex_value_sizes[0] = 4;
  c2_hex_value_sizes[1] = c2_tmp_sizes[1];
  c2_hex_value = c2_hex_value_sizes[0];
  c2_b_hex_value = c2_hex_value_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i109 = 0; c2_i109 <= c2_loop_ub; c2_i109++) {
    c2_hex_value_data[c2_i109] = c2_tmp_data[c2_i109];
  }

  _SFD_SYMBOL_SWITCH(0U, 0U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 65);
  c2_i110 = c2_hex_value_sizes[1];
  c2_i111 = c2_hex_value_sizes[1];
  c2_i112 = c2_hex_value_sizes[1];
  c2_i113 = c2_hex_value_sizes[1];
  c2_b_hex_value_sizes[0] = 1;
  c2_b_hex_value_sizes[1] = ((c2_i110 + c2_i111) + c2_i112) + c2_i113;
  c2_b_loop_ub = c2_i110 - 1;
  for (c2_i114 = 0; c2_i114 <= c2_b_loop_ub; c2_i114++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * c2_i114] = c2_hex_value_data[3
      + c2_hex_value_sizes[0] * c2_i114];
  }

  c2_c_loop_ub = c2_i111 - 1;
  for (c2_i115 = 0; c2_i115 <= c2_c_loop_ub; c2_i115++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * (c2_i115 + c2_i110)] =
      c2_hex_value_data[2 + c2_hex_value_sizes[0] * c2_i115];
  }

  c2_d_loop_ub = c2_i112 - 1;
  for (c2_i116 = 0; c2_i116 <= c2_d_loop_ub; c2_i116++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * ((c2_i116 + c2_i110) + c2_i111)]
      = c2_hex_value_data[1 + c2_hex_value_sizes[0] * c2_i116];
  }

  c2_e_loop_ub = c2_i113 - 1;
  for (c2_i117 = 0; c2_i117 <= c2_e_loop_ub; c2_i117++) {
    c2_b_hex_value_data[c2_b_hex_value_sizes[0] * (((c2_i117 + c2_i110) +
      c2_i111) + c2_i112)] = c2_hex_value_data[c2_hex_value_sizes[0] * c2_i117];
  }

  _SFD_SYMBOL_SWITCH(0U, 1U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
  CV_EML_IF(0, 1, 5, FALSE);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 69);
  c2_c_hex_value_sizes[0] = 1;
  c2_c_hex_value_sizes[1] = c2_b_hex_value_sizes[1];
  c2_c_hex_value = c2_c_hex_value_sizes[0];
  c2_d_hex_value = c2_c_hex_value_sizes[1];
  c2_f_loop_ub = c2_b_hex_value_sizes[0] * c2_b_hex_value_sizes[1] - 1;
  for (c2_i118 = 0; c2_i118 <= c2_f_loop_ub; c2_i118++) {
    c2_c_hex_value_data[c2_i118] = c2_b_hex_value_data[c2_i118];
  }

  c2_d37 = muDoubleScalarRound(c2_hex2dec(chartInstance, c2_c_hex_value_data,
    c2_c_hex_value_sizes));
  if (c2_d37 < 4.294967296E+9) {
    if (CV_SATURATION_EVAL(4, 0, 0, 1, c2_d37 >= 0.0)) {
      c2_u0 = (uint32_T)c2_d37;
    } else {
      c2_u0 = 0U;
    }
  } else if (CV_SATURATION_EVAL(4, 0, 0, 0, c2_d37 >= 4.294967296E+9)) {
    c2_u0 = MAX_uint32_T;
  } else {
    c2_u0 = 0U;
  }

  c2_x = c2_u0;
  memcpy(&c2_res, &c2_x, 4U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -69);
  _SFD_SYMBOL_SCOPE_POP();
  return c2_res;
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_o_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i119;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i119, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i119;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_p_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_ARBlocks, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_ARBlocks), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_ARBlocks);
  return c2_y;
}

static uint8_T c2_q_emlrt_marshallIn(SFc2_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u1;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u1, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u1;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_ARBlocksInstanceStruct *chartInstance)
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

void sf_c2_ARBlocks_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3714640849U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(926634053U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3642756966U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1555957733U);
}

mxArray *sf_c2_ARBlocks_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("hXQ3tMHDYVYgkO36bYP10B");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(496);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,10,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_ARBlocks_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c2_ARBlocks(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[7],T\"battery\",},{M[1],M[15],T\"cksumError\",},{M[1],M[10],T\"height\",},{M[1],M[4],T\"pitchAngle\",},{M[1],M[8],T\"rollAngle\",},{M[1],M[14],T\"status\",},{M[1],M[11],T\"u\",},{M[1],M[12],T\"v\",},{M[1],M[13],T\"w\",},{M[1],M[9],T\"yawAngle\",}}",
    "100 S1x3'type','srcId','name','auxInfo'{{M[4],M[0],T\"dataPrev\",S'l','i','p'{{M1x2[327 335],M[0],}}},{M[4],M[0],T\"hPrev\",S'l','i','p'{{M1x2[284 289],M[0],}}},{M[8],M[0],T\"is_active_c2_ARBlocks\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 13, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_ARBlocks_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_ARBlocksInstanceStruct *chartInstance;
    chartInstance = (SFc2_ARBlocksInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ARBlocksMachineNumber_,
           2,
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
          _SFD_SET_DATA_PROPS(0,2,0,1,"status");
          _SFD_SET_DATA_PROPS(1,2,0,1,"battery");
          _SFD_SET_DATA_PROPS(2,2,0,1,"rollAngle");
          _SFD_SET_DATA_PROPS(3,2,0,1,"pitchAngle");
          _SFD_SET_DATA_PROPS(4,1,1,0,"data");
          _SFD_SET_DATA_PROPS(5,2,0,1,"yawAngle");
          _SFD_SET_DATA_PROPS(6,2,0,1,"height");
          _SFD_SET_DATA_PROPS(7,2,0,1,"u");
          _SFD_SET_DATA_PROPS(8,2,0,1,"v");
          _SFD_SET_DATA_PROPS(9,2,0,1,"w");
          _SFD_SET_DATA_PROPS(10,2,0,1,"cksumError");
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
        _SFD_CV_INIT_EML(0,1,3,22,0,1,0,1,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1520);
        _SFD_CV_INIT_EML_FCN(0,1,"decode",1523,-1,1981);
        _SFD_CV_INIT_EML_FCN(0,2,"getDroneState",1983,-1,3147);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,1932,-1,1958);
        _SFD_CV_INIT_EML_IF(0,1,0,381,398,-1,417);
        _SFD_CV_INIT_EML_IF(0,1,1,419,439,-1,480);
        _SFD_CV_INIT_EML_IF(0,1,2,868,887,913,943);
        _SFD_CV_INIT_EML_IF(0,1,3,1405,1438,1463,1483);
        _SFD_CV_INIT_EML_IF(0,1,4,1463,1483,-1,1483);
        _SFD_CV_INIT_EML_IF(0,1,5,1854,1865,1904,1977);
        _SFD_CV_INIT_EML_IF(0,1,6,2195,2209,2250,2268);
        _SFD_CV_INIT_EML_IF(0,1,7,2250,2268,2309,3138);
        _SFD_CV_INIT_EML_IF(0,1,8,2309,2327,2368,3138);
        _SFD_CV_INIT_EML_IF(0,1,9,2368,2386,2427,3138);
        _SFD_CV_INIT_EML_IF(0,1,10,2427,2445,2486,3138);
        _SFD_CV_INIT_EML_IF(0,1,11,2486,2504,2545,3138);
        _SFD_CV_INIT_EML_IF(0,1,12,2545,2563,2604,3138);
        _SFD_CV_INIT_EML_IF(0,1,13,2604,2622,2663,3138);
        _SFD_CV_INIT_EML_IF(0,1,14,2663,2681,2722,3138);
        _SFD_CV_INIT_EML_IF(0,1,15,2722,2740,2781,3138);
        _SFD_CV_INIT_EML_IF(0,1,16,2781,2799,2840,3138);
        _SFD_CV_INIT_EML_IF(0,1,17,2840,2858,2899,3138);
        _SFD_CV_INIT_EML_IF(0,1,18,2899,2917,2958,3138);
        _SFD_CV_INIT_EML_IF(0,1,19,2958,2976,3017,3138);
        _SFD_CV_INIT_EML_IF(0,1,20,3017,3035,3076,3138);
        _SFD_CV_INIT_EML_IF(0,1,21,3076,3094,-1,3094);
        _SFD_CV_INIT_EML_FOR(0,1,0,2171,2191,3142);

        {
          static int condStart[] = { 1409, 1427 };

          static int condEnd[] = { 1423, 1438 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1409,1438,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
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
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)
            c2_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 496;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);

        {
          real_T *c2_battery;
          real32_T *c2_rollAngle;
          real32_T *c2_pitchAngle;
          real32_T *c2_yawAngle;
          real_T *c2_height;
          real32_T *c2_u;
          real32_T *c2_v;
          real32_T *c2_w;
          real_T *c2_cksumError;
          real_T (*c2_status)[32];
          uint8_T (*c2_data)[496];
          c2_cksumError = (real_T *)ssGetOutputPortSignal(chartInstance->S, 10);
          c2_w = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 9);
          c2_v = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 8);
          c2_u = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 7);
          c2_height = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
          c2_yawAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 5);
          c2_data = (uint8_T (*)[496])ssGetInputPortSignal(chartInstance->S, 0);
          c2_pitchAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c2_rollAngle = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c2_battery = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c2_status = (real_T (*)[32])ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_status);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_battery);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_rollAngle);
          _SFD_SET_DATA_VALUE_PTR(3U, c2_pitchAngle);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_data);
          _SFD_SET_DATA_VALUE_PTR(5U, c2_yawAngle);
          _SFD_SET_DATA_VALUE_PTR(6U, c2_height);
          _SFD_SET_DATA_VALUE_PTR(7U, c2_u);
          _SFD_SET_DATA_VALUE_PTR(8U, c2_v);
          _SFD_SET_DATA_VALUE_PTR(9U, c2_w);
          _SFD_SET_DATA_VALUE_PTR(10U, c2_cksumError);
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
  return "rgIVgRGm8Ynj6sqtqIDVkE";
}

static void sf_opaque_initialize_c2_ARBlocks(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_ARBlocksInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*) chartInstanceVar);
  initialize_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_ARBlocks(void *chartInstanceVar)
{
  enable_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_ARBlocks(void *chartInstanceVar)
{
  disable_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_ARBlocks(void *chartInstanceVar)
{
  sf_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_ARBlocks(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_ARBlocks();/* state var info */
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

extern void sf_internal_set_sim_state_c2_ARBlocks(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_ARBlocks();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_ARBlocks(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_ARBlocks(S);
}

static void sf_opaque_set_sim_state_c2_ARBlocks(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_ARBlocks(S, st);
}

static void sf_opaque_terminate_c2_ARBlocks(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_ARBlocksInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ARBlocks_optimization_info();
    }

    finalize_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_ARBlocks((SFc2_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_ARBlocks(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_ARBlocks((SFc2_ARBlocksInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ARBlocks_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,10);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=10; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3790776115U));
  ssSetChecksum1(S,(3034599199U));
  ssSetChecksum2(S,(58618483U));
  ssSetChecksum3(S,(80074499U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_ARBlocks(SimStruct *S)
{
  SFc2_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc2_ARBlocksInstanceStruct *)utMalloc(sizeof
    (SFc2_ARBlocksInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_ARBlocksInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_ARBlocks;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_ARBlocks;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_ARBlocks;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_ARBlocks;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_ARBlocks;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_ARBlocks;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_ARBlocks;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_ARBlocks;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_ARBlocks;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_ARBlocks;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_ARBlocks;
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

void c2_ARBlocks_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_ARBlocks(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_ARBlocks(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_ARBlocks(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_ARBlocks_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
