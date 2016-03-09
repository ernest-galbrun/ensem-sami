/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ARBlocks_sfun.h"
#include "c3_ARBlocks.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ARBlocks_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[16] = { "sizePayload", "nBytes",
  "bytesToRead", "k", "bytesLeft", "nargin", "nargout", "dataIn", "frameOut",
  "flagOut", "frame", "lastFrame", "count", "countHeader", "countBuffer",
  "buffer" };

/* Function Declarations */
static void initialize_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance);
static void initialize_params_c3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance);
static void enable_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance);
static void disable_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance);
static void set_sim_state_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_st);
static void finalize_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance);
static void sf_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance);
static void c3_chartstep_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance);
static void initSimStructsc3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance);
static void registerMessagesc3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_buffer, const char_T *c3_identifier, uint8_T c3_y[1024]);
static void c3_b_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[1024]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_c_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_countBuffer, const char_T *c3_identifier);
static real_T c3_d_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_e_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_countHeader, const char_T *c3_identifier);
static real_T c3_f_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_g_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_count, const char_T *c3_identifier);
static real_T c3_h_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_i_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_lastFrame, const char_T *c3_identifier, uint8_T c3_y[496]);
static void c3_j_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[496]);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_k_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_frame, const char_T *c3_identifier, uint8_T c3_y[496]);
static void c3_l_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[496]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_m_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_flagOut, const char_T *c3_identifier);
static real_T c3_n_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_o_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_frameOut, const char_T *c3_identifier, uint8_T c3_y[496]);
static void c3_p_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[496]);
static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_q_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_r_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_ARBlocks, const char_T *c3_identifier);
static uint8_T c3_s_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_ARBlocksInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_frame_not_empty = FALSE;
  chartInstance->c3_lastFrame_not_empty = FALSE;
  chartInstance->c3_count_not_empty = FALSE;
  chartInstance->c3_countHeader_not_empty = FALSE;
  chartInstance->c3_countBuffer_not_empty = FALSE;
  chartInstance->c3_buffer_not_empty = FALSE;
  chartInstance->c3_is_active_c3_ARBlocks = 0U;
}

static void initialize_params_c3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void enable_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_u;
  const mxArray *c3_b_y = NULL;
  int32_T c3_i0;
  uint8_T c3_b_u[496];
  const mxArray *c3_c_y = NULL;
  int32_T c3_i1;
  uint8_T c3_c_u[1024];
  const mxArray *c3_d_y = NULL;
  real_T c3_b_hoistedGlobal;
  real_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  real_T c3_c_hoistedGlobal;
  real_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  real_T c3_d_hoistedGlobal;
  real_T c3_f_u;
  const mxArray *c3_g_y = NULL;
  int32_T c3_i2;
  uint8_T c3_g_u[496];
  const mxArray *c3_h_y = NULL;
  int32_T c3_i3;
  uint8_T c3_h_u[496];
  const mxArray *c3_i_y = NULL;
  uint8_T c3_e_hoistedGlobal;
  uint8_T c3_i_u;
  const mxArray *c3_j_y = NULL;
  real_T *c3_flagOut;
  uint8_T (*c3_frameOut)[496];
  c3_flagOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_frameOut = (uint8_T (*)[496])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(9), FALSE);
  c3_hoistedGlobal = *c3_flagOut;
  c3_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i0 = 0; c3_i0 < 496; c3_i0++) {
    c3_b_u[c3_i0] = (*c3_frameOut)[c3_i0];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 3, 0U, 1U, 0U, 1, 496),
                FALSE);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  for (c3_i1 = 0; c3_i1 < 1024; c3_i1++) {
    c3_c_u[c3_i1] = chartInstance->c3_buffer[c3_i1];
  }

  c3_d_y = NULL;
  if (!chartInstance->c3_buffer_not_empty) {
    sf_mex_assign(&c3_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_c_u, 3, 0U, 1U, 0U, 1, 1024),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_b_hoistedGlobal = chartInstance->c3_count;
  c3_d_u = c3_b_hoistedGlobal;
  c3_e_y = NULL;
  if (!chartInstance->c3_count_not_empty) {
    sf_mex_assign(&c3_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c3_y, 3, c3_e_y);
  c3_c_hoistedGlobal = chartInstance->c3_countBuffer;
  c3_e_u = c3_c_hoistedGlobal;
  c3_f_y = NULL;
  if (!chartInstance->c3_countBuffer_not_empty) {
    sf_mex_assign(&c3_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c3_y, 4, c3_f_y);
  c3_d_hoistedGlobal = chartInstance->c3_countHeader;
  c3_f_u = c3_d_hoistedGlobal;
  c3_g_y = NULL;
  if (!chartInstance->c3_countHeader_not_empty) {
    sf_mex_assign(&c3_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c3_y, 5, c3_g_y);
  for (c3_i2 = 0; c3_i2 < 496; c3_i2++) {
    c3_g_u[c3_i2] = chartInstance->c3_frame[c3_i2];
  }

  c3_h_y = NULL;
  if (!chartInstance->c3_frame_not_empty) {
    sf_mex_assign(&c3_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_g_u, 3, 0U, 1U, 0U, 1, 496),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 6, c3_h_y);
  for (c3_i3 = 0; c3_i3 < 496; c3_i3++) {
    c3_h_u[c3_i3] = chartInstance->c3_lastFrame[c3_i3];
  }

  c3_i_y = NULL;
  if (!chartInstance->c3_lastFrame_not_empty) {
    sf_mex_assign(&c3_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_i_y, sf_mex_create("y", c3_h_u, 3, 0U, 1U, 0U, 1, 496),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 7, c3_i_y);
  c3_e_hoistedGlobal = chartInstance->c3_is_active_c3_ARBlocks;
  c3_i_u = c3_e_hoistedGlobal;
  c3_j_y = NULL;
  sf_mex_assign(&c3_j_y, sf_mex_create("y", &c3_i_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c3_y, 8, c3_j_y);
  sf_mex_assign(&c3_st, c3_y, FALSE);
  return c3_st;
}

static void set_sim_state_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_st)
{
  const mxArray *c3_u;
  uint8_T c3_uv0[496];
  int32_T c3_i4;
  uint8_T c3_uv1[1024];
  int32_T c3_i5;
  uint8_T c3_uv2[496];
  int32_T c3_i6;
  uint8_T c3_uv3[496];
  int32_T c3_i7;
  real_T *c3_flagOut;
  uint8_T (*c3_frameOut)[496];
  c3_flagOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_frameOut = (uint8_T (*)[496])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  *c3_flagOut = c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c3_u, 0)), "flagOut");
  c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                        "frameOut", c3_uv0);
  for (c3_i4 = 0; c3_i4 < 496; c3_i4++) {
    (*c3_frameOut)[c3_i4] = c3_uv0[c3_i4];
  }

  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 2)),
                      "buffer", c3_uv1);
  for (c3_i5 = 0; c3_i5 < 1024; c3_i5++) {
    chartInstance->c3_buffer[c3_i5] = c3_uv1[c3_i5];
  }

  chartInstance->c3_count = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 3)), "count");
  chartInstance->c3_countBuffer = c3_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 4)), "countBuffer");
  chartInstance->c3_countHeader = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 5)), "countHeader");
  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 6)),
                        "frame", c3_uv2);
  for (c3_i6 = 0; c3_i6 < 496; c3_i6++) {
    chartInstance->c3_frame[c3_i6] = c3_uv2[c3_i6];
  }

  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 7)),
                        "lastFrame", c3_uv3);
  for (c3_i7 = 0; c3_i7 < 496; c3_i7++) {
    chartInstance->c3_lastFrame[c3_i7] = c3_uv3[c3_i7];
  }

  chartInstance->c3_is_active_c3_ARBlocks = c3_r_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 8)), "is_active_c3_ARBlocks");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_ARBlocks(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance)
{
}

static void sf_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance)
{
  int32_T c3_i8;
  int32_T c3_i9;
  real_T *c3_flagOut;
  uint8_T (*c3_frameOut)[496];
  uint8_T (*c3_dataIn)[500];
  c3_flagOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_frameOut = (uint8_T (*)[496])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_dataIn = (uint8_T (*)[500])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i8 = 0; c3_i8 < 500; c3_i8++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_dataIn)[c3_i8], 0U);
  }

  for (c3_i9 = 0; c3_i9 < 496; c3_i9++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_frameOut)[c3_i9], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_flagOut, 2U);
  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_ARBlocks(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ARBlocksMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_chartstep_c3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance)
{
  int32_T c3_i10;
  uint8_T c3_dataIn[500];
  uint32_T c3_debug_family_var_map[16];
  real_T c3_sizePayload;
  real_T c3_nBytes;
  real_T c3_bytesToRead;
  real_T c3_k;
  real_T c3_bytesLeft;
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 2.0;
  uint8_T c3_frameOut[496];
  real_T c3_flagOut;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  int32_T c3_i14;
  real_T c3_b_bytesToRead;
  int32_T c3_i15;
  int32_T c3_b_k;
  real_T c3_d0;
  boolean_T c3_b0;
  boolean_T c3_b1;
  boolean_T c3_b2;
  int32_T c3_i16;
  int32_T c3_i17;
  real_T c3_d1;
  int32_T c3_i18;
  int32_T c3_tmp_sizes;
  int32_T c3_loop_ub;
  int32_T c3_i19;
  int32_T c3_tmp_data[496];
  int32_T c3_b_tmp_sizes;
  int32_T c3_b_loop_ub;
  int32_T c3_i20;
  int32_T c3_b_tmp_data[1024];
  int32_T c3_c_tmp_sizes[2];
  int32_T c3_iv0[2];
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_c_loop_ub;
  int32_T c3_i23;
  uint8_T c3_c_tmp_data[1024];
  int32_T c3_d_loop_ub;
  int32_T c3_i24;
  real_T c3_d2;
  boolean_T c3_b3;
  boolean_T c3_b4;
  boolean_T c3_b5;
  int32_T c3_i25;
  int32_T c3_i26;
  boolean_T c3_b6;
  boolean_T c3_b7;
  boolean_T c3_b8;
  int32_T c3_i27;
  int32_T c3_d_tmp_sizes;
  int32_T c3_e_loop_ub;
  int32_T c3_i28;
  int32_T c3_d_tmp_data[1024];
  int32_T c3_e_tmp_sizes;
  int32_T c3_f_loop_ub;
  int32_T c3_i29;
  int32_T c3_e_tmp_data[1024];
  int32_T c3_iv1[2];
  int32_T c3_i30;
  int32_T c3_i31;
  int32_T c3_g_loop_ub;
  int32_T c3_i32;
  int32_T c3_h_loop_ub;
  int32_T c3_i33;
  int32_T c3_f_tmp_sizes;
  int32_T c3_i34;
  int32_T c3_f_tmp_data[496];
  int32_T c3_g_tmp_sizes[2];
  int32_T c3_i35;
  int32_T c3_i36;
  int32_T c3_i_loop_ub;
  int32_T c3_i37;
  int32_T c3_g_tmp_data[496];
  int32_T c3_i38;
  real_T c3_dv0[496];
  int32_T c3_j_loop_ub;
  int32_T c3_i39;
  real_T c3_d3;
  boolean_T c3_b9;
  boolean_T c3_b10;
  boolean_T c3_b11;
  int32_T c3_i40;
  int32_T c3_i41;
  boolean_T c3_b12;
  boolean_T c3_b13;
  boolean_T c3_b14;
  int32_T c3_i42;
  int32_T c3_k_loop_ub;
  int32_T c3_i43;
  int32_T c3_h_tmp_sizes;
  int32_T c3_l_loop_ub;
  int32_T c3_i44;
  int32_T c3_h_tmp_data[1024];
  int32_T c3_iv2[2];
  int32_T c3_i45;
  int32_T c3_i46;
  int32_T c3_m_loop_ub;
  int32_T c3_i47;
  int32_T c3_n_loop_ub;
  int32_T c3_i48;
  real_T c3_d4;
  boolean_T c3_b15;
  boolean_T c3_b16;
  boolean_T c3_b17;
  int32_T c3_i49;
  int32_T c3_i50;
  int32_T c3_i51;
  int32_T c3_o_loop_ub;
  int32_T c3_i52;
  int32_T c3_i_tmp_sizes;
  int32_T c3_p_loop_ub;
  int32_T c3_i53;
  int32_T c3_i_tmp_data[1024];
  int32_T c3_iv3[2];
  int32_T c3_i54;
  int32_T c3_i55;
  int32_T c3_q_loop_ub;
  int32_T c3_i56;
  int32_T c3_r_loop_ub;
  int32_T c3_i57;
  int32_T c3_i58;
  int32_T c3_i59;
  int32_T c3_i60;
  int32_T c3_i61;
  int32_T c3_i62;
  real_T *c3_b_flagOut;
  uint8_T (*c3_b_frameOut)[496];
  uint8_T (*c3_b_dataIn)[500];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  int32_T exitg1;
  boolean_T guard11 = FALSE;
  boolean_T guard21 = FALSE;
  c3_b_flagOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_frameOut = (uint8_T (*)[496])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_dataIn = (uint8_T (*)[500])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i10 = 0; c3_i10 < 500; c3_i10++) {
    c3_dataIn[c3_i10] = (*c3_b_dataIn)[c3_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 16U, 16U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_sizePayload, 0U, c3_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_nBytes, 1U, c3_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_bytesToRead, 2U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_k, 3U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_bytesLeft, 4U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 5U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 6U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_dataIn, 7U, c3_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_frameOut, 8U, c3_h_sf_marshallOut,
    c3_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_flagOut, 9U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_frame, 10U,
    c3_f_sf_marshallOut, c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_lastFrame, 11U,
    c3_e_sf_marshallOut, c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c3_count, 12U,
    c3_d_sf_marshallOut, c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c3_countHeader, 13U,
    c3_c_sf_marshallOut, c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c3_countBuffer, 14U,
    c3_b_sf_marshallOut, c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_buffer, 15U,
    c3_sf_marshallOut, c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 8);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 10);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 11);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 16);
  c3_sizePayload = 496.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 19);
  c3_nBytes = 500.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 24);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c3_buffer_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 25);
    for (c3_i11 = 0; c3_i11 < 1024; c3_i11++) {
      chartInstance->c3_buffer[c3_i11] = 0U;
    }

    chartInstance->c3_buffer_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 28);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c3_countBuffer_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
    chartInstance->c3_countBuffer = 0.0;
    chartInstance->c3_countBuffer_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 33);
  if (CV_EML_IF(0, 1, 2, !chartInstance->c3_frame_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 34);
    for (c3_i12 = 0; c3_i12 < 496; c3_i12++) {
      chartInstance->c3_frame[c3_i12] = 0U;
    }

    chartInstance->c3_frame_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 37);
  if (CV_EML_IF(0, 1, 3, !chartInstance->c3_lastFrame_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 38);
    for (c3_i13 = 0; c3_i13 < 496; c3_i13++) {
      chartInstance->c3_lastFrame[c3_i13] = 0U;
    }

    chartInstance->c3_lastFrame_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 42);
  if (CV_EML_IF(0, 1, 4, !chartInstance->c3_count_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 43);
    chartInstance->c3_count = 0.0;
    chartInstance->c3_count_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 46);
  if (CV_EML_IF(0, 1, 5, !chartInstance->c3_countHeader_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 47);
    chartInstance->c3_countHeader = 0.0;
    chartInstance->c3_countHeader_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 52);
  for (c3_i14 = 0; c3_i14 < 500; c3_i14++) {
    chartInstance->c3_buffer[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
      "buffer", (int32_T)_SFD_INTEGER_CHECK("countBuffer+1:countBuffer+nBytes",
      chartInstance->c3_countBuffer + (1.0 + (real_T)c3_i14)), 1, 1024, 1, 0) -
      1] = c3_dataIn[c3_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 54);
  c3_bytesToRead = chartInstance->c3_countBuffer + 500.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 59);
  c3_b_bytesToRead = c3_bytesToRead;
  c3_i15 = (int32_T)c3_b_bytesToRead;
  _SFD_FOR_LOOP_VECTOR_CHECK(1.0, 1.0, c3_b_bytesToRead, mxDOUBLE_CLASS, c3_i15);
  c3_k = 1.0;
  c3_b_k = 0;
  do {
    exitg1 = 0;
    if (c3_b_k <= c3_i15 - 1) {
      c3_k = 1.0 + (real_T)c3_b_k;
      CV_EML_FOR(0, 1, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 60);
      guard11 = FALSE;
      guard21 = FALSE;
      if (CV_EML_COND(0, 1, 0, chartInstance->c3_countHeader == 4.0)) {
        if (CV_EML_COND(0, 1, 1, chartInstance->c3_count < 496.0)) {
          CV_EML_MCDC(0, 1, 0, TRUE);
          CV_EML_IF(0, 1, 6, TRUE);
          _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 61);
          c3_bytesLeft = 496.0 - chartInstance->c3_count;
          _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 62);
          c3_d0 = (c3_k + c3_bytesLeft) - 1.0;
          c3_b0 = (c3_k > c3_d0);
          c3_b1 = c3_b0;
          c3_b2 = c3_b1;
          if (c3_b2) {
            c3_i16 = 1;
            c3_i17 = 0;
          } else {
            c3_i16 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
              (int32_T)c3_k, 1, 1024, 0, 0);
            c3_i17 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
              (int32_T)c3_d0, 1, 1024, 0, 0);
          }

          c3_d1 = chartInstance->c3_count + 1.0;
          c3_i18 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("frame",
            (int32_T)c3_d1, 1, 496, 0, 0);
          c3_tmp_sizes = 497 - c3_i18;
          c3_loop_ub = 496 - c3_i18;
          for (c3_i19 = 0; c3_i19 <= c3_loop_ub; c3_i19++) {
            c3_tmp_data[c3_i19] = c3_i18 + c3_i19;
          }

          c3_b_tmp_sizes = (c3_i17 - c3_i16) + 1;
          c3_b_loop_ub = c3_i17 - c3_i16;
          for (c3_i20 = 0; c3_i20 <= c3_b_loop_ub; c3_i20++) {
            c3_b_tmp_data[c3_i20] = c3_i16 + c3_i20;
          }

          c3_c_tmp_sizes[0] = 1;
          c3_iv0[0] = 1;
          c3_iv0[1] = c3_b_tmp_sizes;
          c3_c_tmp_sizes[1] = c3_iv0[1];
          c3_i21 = c3_c_tmp_sizes[0];
          c3_i22 = c3_c_tmp_sizes[1];
          c3_c_loop_ub = c3_b_tmp_sizes - 1;
          for (c3_i23 = 0; c3_i23 <= c3_c_loop_ub; c3_i23++) {
            c3_c_tmp_data[c3_i23] = chartInstance->
              c3_buffer[c3_b_tmp_data[c3_i23] - 1];
          }

          _SFD_SIZE_EQ_CHECK_1D(c3_tmp_sizes, c3_c_tmp_sizes[1]);
          c3_d_loop_ub = c3_c_tmp_sizes[0] * c3_c_tmp_sizes[1] - 1;
          for (c3_i24 = 0; c3_i24 <= c3_d_loop_ub; c3_i24++) {
            chartInstance->c3_frame[c3_tmp_data[c3_i24] - 1] =
              c3_c_tmp_data[c3_i24];
          }

          _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 63);
          chartInstance->c3_count = 496.0;
          _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 64);
          chartInstance->c3_countBuffer = c3_bytesToRead - c3_bytesLeft;
          _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 65);
          c3_d2 = c3_k + c3_bytesLeft;
          c3_b3 = (c3_d2 > c3_bytesToRead);
          c3_b4 = c3_b3;
          c3_b5 = c3_b4;
          if (c3_b5) {
            c3_i25 = 1;
            c3_i26 = 0;
          } else {
            c3_i25 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
              (int32_T)c3_d2, 1, 1024, 0, 0);
            c3_i26 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
              (int32_T)_SFD_INTEGER_CHECK("bytesToRead", c3_bytesToRead), 1,
              1024, 0, 0);
          }

          c3_b6 = (1.0 > chartInstance->c3_countBuffer);
          c3_b7 = c3_b6;
          c3_b8 = c3_b7;
          if (c3_b8) {
            c3_i27 = 0;
          } else {
            c3_i27 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
              (int32_T)_SFD_INTEGER_CHECK("countBuffer",
              chartInstance->c3_countBuffer), 1, 1024, 0, 0);
          }

          c3_d_tmp_sizes = c3_i27;
          c3_e_loop_ub = c3_i27 - 1;
          for (c3_i28 = 0; c3_i28 <= c3_e_loop_ub; c3_i28++) {
            c3_d_tmp_data[c3_i28] = 1 + c3_i28;
          }

          c3_e_tmp_sizes = (c3_i26 - c3_i25) + 1;
          c3_f_loop_ub = c3_i26 - c3_i25;
          for (c3_i29 = 0; c3_i29 <= c3_f_loop_ub; c3_i29++) {
            c3_e_tmp_data[c3_i29] = c3_i25 + c3_i29;
          }

          c3_c_tmp_sizes[0] = 1;
          c3_iv1[0] = 1;
          c3_iv1[1] = c3_e_tmp_sizes;
          c3_c_tmp_sizes[1] = c3_iv1[1];
          c3_i30 = c3_c_tmp_sizes[0];
          c3_i31 = c3_c_tmp_sizes[1];
          c3_g_loop_ub = c3_e_tmp_sizes - 1;
          for (c3_i32 = 0; c3_i32 <= c3_g_loop_ub; c3_i32++) {
            c3_c_tmp_data[c3_i32] = chartInstance->
              c3_buffer[c3_e_tmp_data[c3_i32] - 1];
          }

          _SFD_SIZE_EQ_CHECK_1D(c3_d_tmp_sizes, c3_c_tmp_sizes[1]);
          c3_h_loop_ub = c3_c_tmp_sizes[0] * c3_c_tmp_sizes[1] - 1;
          for (c3_i33 = 0; c3_i33 <= c3_h_loop_ub; c3_i33++) {
            chartInstance->c3_buffer[c3_d_tmp_data[c3_i33] - 1] =
              c3_c_tmp_data[c3_i33];
          }

          _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 66);
          exitg1 = 1;
        } else {
          guard21 = TRUE;
        }
      } else {
        guard21 = TRUE;
      }

      if (guard21 == TRUE) {
        CV_EML_MCDC(0, 1, 0, FALSE);
        CV_EML_IF(0, 1, 6, FALSE);
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 70);
        if (CV_EML_COND(0, 1, 2, chartInstance->c3_countHeader == 3.0)) {
          if (CV_EML_COND(0, 1, 3, (real_T)chartInstance->c3_buffer[(int32_T)
                          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer", (int32_T)
                c3_k, 1, 1024, 1, 0) - 1] == 85.0)) {
            CV_EML_MCDC(0, 1, 1, TRUE);
            CV_EML_IF(0, 1, 7, TRUE);
            _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 72);
            chartInstance->c3_countHeader = 4.0;
            _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 74);
            if (CV_EML_IF(0, 1, 8, c3_bytesToRead - c3_k > 496.0)) {
              _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 75);
              chartInstance->c3_count = 496.0;
              _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 76);
              c3_f_tmp_sizes = 496;
              for (c3_i34 = 0; c3_i34 < 496; c3_i34++) {
                c3_f_tmp_data[c3_i34] = 1 + c3_i34;
              }

              c3_g_tmp_sizes[0] = 1;
              c3_g_tmp_sizes[1] = 496;
              c3_i35 = c3_g_tmp_sizes[0];
              c3_i36 = c3_g_tmp_sizes[1];
              c3_i_loop_ub = c3_f_tmp_sizes - 1;
              for (c3_i37 = 0; c3_i37 <= c3_i_loop_ub; c3_i37++) {
                c3_g_tmp_data[c3_i37] = c3_f_tmp_data[c3_i37] - 1;
              }

              for (c3_i38 = 0; c3_i38 < 496; c3_i38++) {
                c3_dv0[c3_i38] = 1.0 + (real_T)c3_i38;
              }

              c3_j_loop_ub = c3_g_tmp_sizes[0] * c3_g_tmp_sizes[1] - 1;
              for (c3_i39 = 0; c3_i39 <= c3_j_loop_ub; c3_i39++) {
                chartInstance->c3_frame[c3_g_tmp_data[c3_i39]] =
                  chartInstance->c3_buffer[(int32_T)(real_T)
                  _SFD_EML_ARRAY_BOUNDS_CHECK("buffer", (int32_T)(c3_k +
                  c3_dv0[c3_i39]), 1, 1024, 1, 0) - 1];
              }

              _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 77);
              chartInstance->c3_countBuffer = (c3_bytesToRead - c3_k) - 496.0;
              _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 78);
              c3_d3 = (c3_k + 496.0) + 1.0;
              c3_b9 = (c3_d3 > c3_bytesToRead);
              c3_b10 = c3_b9;
              c3_b11 = c3_b10;
              if (c3_b11) {
                c3_i40 = 1;
                c3_i41 = 0;
              } else {
                c3_i40 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
                  (int32_T)c3_d3, 1, 1024, 0, 0);
                c3_i41 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
                  (int32_T)_SFD_INTEGER_CHECK("bytesToRead", c3_bytesToRead), 1,
                  1024, 0, 0);
              }

              c3_b12 = (1.0 > chartInstance->c3_countBuffer);
              c3_b13 = c3_b12;
              c3_b14 = c3_b13;
              if (c3_b14) {
                c3_i42 = 0;
              } else {
                c3_i42 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
                  (int32_T)_SFD_INTEGER_CHECK("countBuffer",
                  chartInstance->c3_countBuffer), 1, 1024, 0, 0);
              }

              c3_d_tmp_sizes = c3_i42;
              c3_k_loop_ub = c3_i42 - 1;
              for (c3_i43 = 0; c3_i43 <= c3_k_loop_ub; c3_i43++) {
                c3_d_tmp_data[c3_i43] = 1 + c3_i43;
              }

              c3_h_tmp_sizes = (c3_i41 - c3_i40) + 1;
              c3_l_loop_ub = c3_i41 - c3_i40;
              for (c3_i44 = 0; c3_i44 <= c3_l_loop_ub; c3_i44++) {
                c3_h_tmp_data[c3_i44] = c3_i40 + c3_i44;
              }

              c3_c_tmp_sizes[0] = 1;
              c3_iv2[0] = 1;
              c3_iv2[1] = c3_h_tmp_sizes;
              c3_c_tmp_sizes[1] = c3_iv2[1];
              c3_i45 = c3_c_tmp_sizes[0];
              c3_i46 = c3_c_tmp_sizes[1];
              c3_m_loop_ub = c3_h_tmp_sizes - 1;
              for (c3_i47 = 0; c3_i47 <= c3_m_loop_ub; c3_i47++) {
                c3_c_tmp_data[c3_i47] = chartInstance->
                  c3_buffer[c3_h_tmp_data[c3_i47] - 1];
              }

              _SFD_SIZE_EQ_CHECK_1D(c3_d_tmp_sizes, c3_c_tmp_sizes[1]);
              c3_n_loop_ub = c3_c_tmp_sizes[0] * c3_c_tmp_sizes[1] - 1;
              for (c3_i48 = 0; c3_i48 <= c3_n_loop_ub; c3_i48++) {
                chartInstance->c3_buffer[c3_d_tmp_data[c3_i48] - 1] =
                  c3_c_tmp_data[c3_i48];
              }
            } else {
              _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 81);
              chartInstance->c3_count = c3_bytesToRead - c3_k;
              _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 82);
              if (CV_EML_IF(0, 1, 9, chartInstance->c3_count > 0.0)) {
                _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 83);
                c3_d4 = c3_k + 1.0;
                c3_b15 = (c3_d4 > c3_bytesToRead);
                c3_b16 = c3_b15;
                c3_b17 = c3_b16;
                if (c3_b17) {
                  c3_i49 = 1;
                  c3_i50 = 0;
                } else {
                  c3_i49 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
                    (int32_T)c3_d4, 1, 1024, 0, 0);
                  c3_i50 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer",
                    (int32_T)_SFD_INTEGER_CHECK("bytesToRead", c3_bytesToRead),
                    1, 1024, 0, 0);
                }

                c3_i51 = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("frame",
                  (int32_T)chartInstance->c3_count, 1, 496, 0, 0);
                c3_tmp_sizes = c3_i51;
                c3_o_loop_ub = c3_i51 - 1;
                for (c3_i52 = 0; c3_i52 <= c3_o_loop_ub; c3_i52++) {
                  c3_tmp_data[c3_i52] = 1 + c3_i52;
                }

                c3_i_tmp_sizes = (c3_i50 - c3_i49) + 1;
                c3_p_loop_ub = c3_i50 - c3_i49;
                for (c3_i53 = 0; c3_i53 <= c3_p_loop_ub; c3_i53++) {
                  c3_i_tmp_data[c3_i53] = c3_i49 + c3_i53;
                }

                c3_c_tmp_sizes[0] = 1;
                c3_iv3[0] = 1;
                c3_iv3[1] = c3_i_tmp_sizes;
                c3_c_tmp_sizes[1] = c3_iv3[1];
                c3_i54 = c3_c_tmp_sizes[0];
                c3_i55 = c3_c_tmp_sizes[1];
                c3_q_loop_ub = c3_i_tmp_sizes - 1;
                for (c3_i56 = 0; c3_i56 <= c3_q_loop_ub; c3_i56++) {
                  c3_c_tmp_data[c3_i56] = chartInstance->
                    c3_buffer[c3_i_tmp_data[c3_i56] - 1];
                }

                _SFD_SIZE_EQ_CHECK_1D(c3_tmp_sizes, c3_c_tmp_sizes[1]);
                c3_r_loop_ub = c3_c_tmp_sizes[0] * c3_c_tmp_sizes[1] - 1;
                for (c3_i57 = 0; c3_i57 <= c3_r_loop_ub; c3_i57++) {
                  chartInstance->c3_frame[c3_tmp_data[c3_i57] - 1] =
                    c3_c_tmp_data[c3_i57];
                }
              }

              _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 85);
              chartInstance->c3_countBuffer = 0.0;
            }

            _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 89);
            exitg1 = 1;
          } else {
            guard11 = TRUE;
          }
        } else {
          guard11 = TRUE;
        }
      }

      if (guard11 == TRUE) {
        CV_EML_MCDC(0, 1, 1, FALSE);
        CV_EML_IF(0, 1, 7, FALSE);
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 92);
        guard3 = FALSE;
        if (CV_EML_COND(0, 1, 4, chartInstance->c3_countHeader == 2.0)) {
          if (CV_EML_COND(0, 1, 5, (real_T)chartInstance->c3_buffer[(int32_T)
                          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer", (int32_T)
                c3_k, 1, 1024, 1, 0) - 1] == 102.0)) {
            CV_EML_MCDC(0, 1, 2, TRUE);
            CV_EML_IF(0, 1, 10, TRUE);
            _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 93);
            chartInstance->c3_countHeader = 3.0;
          } else {
            guard3 = TRUE;
          }
        } else {
          guard3 = TRUE;
        }

        if (guard3 == TRUE) {
          CV_EML_MCDC(0, 1, 2, FALSE);
          CV_EML_IF(0, 1, 10, FALSE);
        }

        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 96);
        guard2 = FALSE;
        if (CV_EML_COND(0, 1, 6, chartInstance->c3_countHeader == 1.0)) {
          if (CV_EML_COND(0, 1, 7, (real_T)chartInstance->c3_buffer[(int32_T)
                          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer", (int32_T)
                c3_k, 1, 1024, 1, 0) - 1] == 119.0)) {
            CV_EML_MCDC(0, 1, 3, TRUE);
            CV_EML_IF(0, 1, 11, TRUE);
            _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 97);
            chartInstance->c3_countHeader = 2.0;
          } else {
            guard2 = TRUE;
          }
        } else {
          guard2 = TRUE;
        }

        if (guard2 == TRUE) {
          CV_EML_MCDC(0, 1, 3, FALSE);
          CV_EML_IF(0, 1, 11, FALSE);
        }

        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 100);
        guard1 = FALSE;
        if (CV_EML_COND(0, 1, 8, chartInstance->c3_countHeader == 0.0)) {
          if (CV_EML_COND(0, 1, 9, (real_T)chartInstance->c3_buffer[(int32_T)
                          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("buffer", (int32_T)
                c3_k, 1, 1024, 1, 0) - 1] == 136.0)) {
            CV_EML_MCDC(0, 1, 4, TRUE);
            CV_EML_IF(0, 1, 12, TRUE);
            _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 101);
            chartInstance->c3_countHeader = 1.0;
          } else {
            guard1 = TRUE;
          }
        } else {
          guard1 = TRUE;
        }

        if (guard1 == TRUE) {
          CV_EML_MCDC(0, 1, 4, FALSE);
          CV_EML_IF(0, 1, 12, FALSE);
        }

        c3_b_k++;
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      }
    } else {
      CV_EML_FOR(0, 1, 0, 0);
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 106);
  if (CV_EML_IF(0, 1, 13, chartInstance->c3_count == 496.0)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 107);
    for (c3_i58 = 0; c3_i58 < 496; c3_i58++) {
      c3_frameOut[c3_i58] = chartInstance->c3_frame[c3_i58];
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 108);
    c3_flagOut = 1.0;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 109);
    for (c3_i59 = 0; c3_i59 < 496; c3_i59++) {
      chartInstance->c3_lastFrame[c3_i59] = chartInstance->c3_frame[c3_i59];
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 110);
    for (c3_i60 = 0; c3_i60 < 496; c3_i60++) {
      chartInstance->c3_frame[c3_i60] = 0U;
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 111);
    chartInstance->c3_count = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 112);
    chartInstance->c3_countHeader = 0.0;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 115);
    for (c3_i61 = 0; c3_i61 < 496; c3_i61++) {
      c3_frameOut[c3_i61] = chartInstance->c3_lastFrame[c3_i61];
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 116);
    c3_flagOut = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -116);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i62 = 0; c3_i62 < 496; c3_i62++) {
    (*c3_b_frameOut)[c3_i62] = c3_frameOut[c3_i62];
  }

  *c3_b_flagOut = c3_flagOut;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_ARBlocks(SFc3_ARBlocksInstanceStruct *chartInstance)
{
}

static void registerMessagesc3_ARBlocks(SFc3_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i63;
  uint8_T c3_b_inData[1024];
  int32_T c3_i64;
  uint8_T c3_u[1024];
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i63 = 0; c3_i63 < 1024; c3_i63++) {
    c3_b_inData[c3_i63] = (*(uint8_T (*)[1024])c3_inData)[c3_i63];
  }

  for (c3_i64 = 0; c3_i64 < 1024; c3_i64++) {
    c3_u[c3_i64] = c3_b_inData[c3_i64];
  }

  c3_y = NULL;
  if (!chartInstance->c3_buffer_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 1024), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_buffer, const char_T *c3_identifier, uint8_T c3_y[1024])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_buffer), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_buffer);
}

static void c3_b_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[1024])
{
  uint8_T c3_uv4[1024];
  int32_T c3_i65;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_buffer_not_empty = FALSE;
  } else {
    chartInstance->c3_buffer_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv4, 1, 3, 0U, 1, 0U, 1,
                  1024);
    for (c3_i65 = 0; c3_i65 < 1024; c3_i65++) {
      c3_y[c3_i65] = c3_uv4[c3_i65];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_buffer;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y[1024];
  int32_T c3_i66;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_b_buffer = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_buffer), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_buffer);
  for (c3_i66 = 0; c3_i66 < 1024; c3_i66++) {
    (*(uint8_T (*)[1024])c3_outData)[c3_i66] = c3_y[c3_i66];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_countBuffer_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_c_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_countBuffer, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_countBuffer),
    &c3_thisId);
  sf_mex_destroy(&c3_b_countBuffer);
  return c3_y;
}

static real_T c3_d_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d5;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_countBuffer_not_empty = FALSE;
  } else {
    chartInstance->c3_countBuffer_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d5, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d5;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_countBuffer;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_b_countBuffer = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_countBuffer),
    &c3_thisId);
  sf_mex_destroy(&c3_b_countBuffer);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_countHeader_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_e_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_countHeader, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_countHeader),
    &c3_thisId);
  sf_mex_destroy(&c3_b_countHeader);
  return c3_y;
}

static real_T c3_f_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d6;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_countHeader_not_empty = FALSE;
  } else {
    chartInstance->c3_countHeader_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d6, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d6;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_countHeader;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_b_countHeader = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_countHeader),
    &c3_thisId);
  sf_mex_destroy(&c3_b_countHeader);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_count_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_g_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_count, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_count), &c3_thisId);
  sf_mex_destroy(&c3_b_count);
  return c3_y;
}

static real_T c3_h_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d7;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_count_not_empty = FALSE;
  } else {
    chartInstance->c3_count_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d7, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d7;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_count;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_b_count = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_count), &c3_thisId);
  sf_mex_destroy(&c3_b_count);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i67;
  uint8_T c3_b_inData[496];
  int32_T c3_i68;
  uint8_T c3_u[496];
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i67 = 0; c3_i67 < 496; c3_i67++) {
    c3_b_inData[c3_i67] = (*(uint8_T (*)[496])c3_inData)[c3_i67];
  }

  for (c3_i68 = 0; c3_i68 < 496; c3_i68++) {
    c3_u[c3_i68] = c3_b_inData[c3_i68];
  }

  c3_y = NULL;
  if (!chartInstance->c3_lastFrame_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 496), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_i_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_lastFrame, const char_T *c3_identifier, uint8_T c3_y[496])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_lastFrame), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_lastFrame);
}

static void c3_j_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[496])
{
  uint8_T c3_uv5[496];
  int32_T c3_i69;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_lastFrame_not_empty = FALSE;
  } else {
    chartInstance->c3_lastFrame_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv5, 1, 3, 0U, 1, 0U, 1, 496);
    for (c3_i69 = 0; c3_i69 < 496; c3_i69++) {
      c3_y[c3_i69] = c3_uv5[c3_i69];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_lastFrame;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y[496];
  int32_T c3_i70;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_b_lastFrame = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_lastFrame), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_lastFrame);
  for (c3_i70 = 0; c3_i70 < 496; c3_i70++) {
    (*(uint8_T (*)[496])c3_outData)[c3_i70] = c3_y[c3_i70];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i71;
  uint8_T c3_b_inData[496];
  int32_T c3_i72;
  uint8_T c3_u[496];
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i71 = 0; c3_i71 < 496; c3_i71++) {
    c3_b_inData[c3_i71] = (*(uint8_T (*)[496])c3_inData)[c3_i71];
  }

  for (c3_i72 = 0; c3_i72 < 496; c3_i72++) {
    c3_u[c3_i72] = c3_b_inData[c3_i72];
  }

  c3_y = NULL;
  if (!chartInstance->c3_frame_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 496), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_k_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_frame, const char_T *c3_identifier, uint8_T c3_y[496])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_frame), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_frame);
}

static void c3_l_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[496])
{
  uint8_T c3_uv6[496];
  int32_T c3_i73;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_frame_not_empty = FALSE;
  } else {
    chartInstance->c3_frame_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv6, 1, 3, 0U, 1, 0U, 1, 496);
    for (c3_i73 = 0; c3_i73 < 496; c3_i73++) {
      c3_y[c3_i73] = c3_uv6[c3_i73];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_frame;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y[496];
  int32_T c3_i74;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_b_frame = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_frame), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_frame);
  for (c3_i74 = 0; c3_i74 < 496; c3_i74++) {
    (*(uint8_T (*)[496])c3_outData)[c3_i74] = c3_y[c3_i74];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_m_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_flagOut, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_flagOut), &c3_thisId);
  sf_mex_destroy(&c3_flagOut);
  return c3_y;
}

static real_T c3_n_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d8;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d8, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d8;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_flagOut;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_flagOut = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_flagOut), &c3_thisId);
  sf_mex_destroy(&c3_flagOut);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i75;
  uint8_T c3_b_inData[496];
  int32_T c3_i76;
  uint8_T c3_u[496];
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i75 = 0; c3_i75 < 496; c3_i75++) {
    c3_b_inData[c3_i75] = (*(uint8_T (*)[496])c3_inData)[c3_i75];
  }

  for (c3_i76 = 0; c3_i76 < 496; c3_i76++) {
    c3_u[c3_i76] = c3_b_inData[c3_i76];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 496), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_o_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_frameOut, const char_T *c3_identifier, uint8_T c3_y[496])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_frameOut), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_frameOut);
}

static void c3_p_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[496])
{
  uint8_T c3_uv7[496];
  int32_T c3_i77;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv7, 1, 3, 0U, 1, 0U, 1, 496);
  for (c3_i77 = 0; c3_i77 < 496; c3_i77++) {
    c3_y[c3_i77] = c3_uv7[c3_i77];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_frameOut;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y[496];
  int32_T c3_i78;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_frameOut = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_frameOut), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_frameOut);
  for (c3_i78 = 0; c3_i78 < 496; c3_i78++) {
    (*(uint8_T (*)[496])c3_outData)[c3_i78] = c3_y[c3_i78];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i79;
  uint8_T c3_b_inData[500];
  int32_T c3_i80;
  uint8_T c3_u[500];
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i79 = 0; c3_i79 < 500; c3_i79++) {
    c3_b_inData[c3_i79] = (*(uint8_T (*)[500])c3_inData)[c3_i79];
  }

  for (c3_i80 = 0; c3_i80 < 500; c3_i80++) {
    c3_u[c3_i80] = c3_b_inData[c3_i80];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 500), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

const mxArray *sf_c3_ARBlocks_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c3_nameCaptureInfo;
}

static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static int32_T c3_q_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i81;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i81, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i81;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_r_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_ARBlocks, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_ARBlocks), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_ARBlocks);
  return c3_y;
}

static uint8_T c3_s_emlrt_marshallIn(SFc3_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_ARBlocksInstanceStruct *chartInstance)
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

void sf_c3_ARBlocks_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(451742631U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2838692043U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4221762934U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1319875930U);
}

mxArray *sf_c3_ARBlocks_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("MEuQ528xsfhgc96kOJA9RG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(500);
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

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_ARBlocks_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c3_ARBlocks(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x9'type','srcId','name','auxInfo'{{M[1],M[8],T\"flagOut\",},{M[1],M[5],T\"frameOut\",},{M[4],M[0],T\"buffer\",S'l','i','p'{{M1x2[368 374],M[0],}}},{M[4],M[0],T\"count\",S'l','i','p'{{M1x2[299 304],M[0],}}},{M[4],M[0],T\"countBuffer\",S'l','i','p'{{M1x2[343 354],M[0],}}},{M[4],M[0],T\"countHeader\",S'l','i','p'{{M1x2[318 329],M[0],}}},{M[4],M[0],T\"frame\",S'l','i','p'{{M1x2[257 262],M[0],}}},{M[4],M[0],T\"lastFrame\",S'l','i','p'{{M1x2[276 285],M[0],}}},{M[8],M[0],T\"is_active_c3_ARBlocks\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 9, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_ARBlocks_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_ARBlocksInstanceStruct *chartInstance;
    chartInstance = (SFc3_ARBlocksInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ARBlocksMachineNumber_,
           3,
           1,
           1,
           3,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"dataIn");
          _SFD_SET_DATA_PROPS(1,2,0,1,"frameOut");
          _SFD_SET_DATA_PROPS(2,2,0,1,"flagOut");
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
        _SFD_CV_INIT_EML(0,1,1,14,0,0,0,1,0,10,5);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2630);
        _SFD_CV_INIT_EML_IF(0,1,0,612,630,-1,667);
        _SFD_CV_INIT_EML_IF(0,1,1,669,692,-1,715);
        _SFD_CV_INIT_EML_IF(0,1,2,718,735,-1,778);
        _SFD_CV_INIT_EML_IF(0,1,3,780,801,-1,848);
        _SFD_CV_INIT_EML_IF(0,1,4,851,868,-1,885);
        _SFD_CV_INIT_EML_IF(0,1,5,887,910,-1,933);
        _SFD_CV_INIT_EML_IF(0,1,6,1204,1243,1526,2112);
        _SFD_CV_INIT_EML_IF(0,1,7,1526,1561,2122,2189);
        _SFD_CV_INIT_EML_IF(0,1,8,1604,1635,1863,2080);
        _SFD_CV_INIT_EML_IF(0,1,9,1927,1939,-1,2025);
        _SFD_CV_INIT_EML_IF(0,1,10,2122,2158,-1,2189);
        _SFD_CV_INIT_EML_IF(0,1,11,2199,2235,-1,2266);
        _SFD_CV_INIT_EML_IF(0,1,12,2279,2315,-1,2346);
        _SFD_CV_INIT_EML_IF(0,1,13,2353,2374,2522,2627);
        _SFD_CV_INIT_EML_FOR(0,1,0,1176,1196,2351);

        {
          static int condStart[] = { 1207, 1225 };

          static int condEnd[] = { 1221, 1242 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1207,1242,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1529, 1547 };

          static int condEnd[] = { 1543, 1560 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,1529,1560,2,2,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2125, 2143 };

          static int condEnd[] = { 2139, 2157 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,2,2125,2157,2,4,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2202, 2220 };

          static int condEnd[] = { 2216, 2234 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,3,2202,2234,2,6,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2282, 2300 };

          static int condEnd[] = { 2296, 2314 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,4,2282,2314,2,8,&(condStart[0]),&(condEnd[0]),
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
          dimVector[0]= 500;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 496;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_h_sf_marshallOut,(MexInFcnForType)
            c3_h_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_g_sf_marshallOut,(MexInFcnForType)c3_g_sf_marshallIn);

        {
          real_T *c3_flagOut;
          uint8_T (*c3_dataIn)[500];
          uint8_T (*c3_frameOut)[496];
          c3_flagOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c3_frameOut = (uint8_T (*)[496])ssGetOutputPortSignal(chartInstance->S,
            1);
          c3_dataIn = (uint8_T (*)[500])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_dataIn);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_frameOut);
          _SFD_SET_DATA_VALUE_PTR(2U, c3_flagOut);
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
  return "EBwi7wwKh6dNpnh8BJBG9G";
}

static void sf_opaque_initialize_c3_ARBlocks(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_ARBlocksInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*) chartInstanceVar);
  initialize_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_ARBlocks(void *chartInstanceVar)
{
  enable_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_ARBlocks(void *chartInstanceVar)
{
  disable_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_ARBlocks(void *chartInstanceVar)
{
  sf_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_ARBlocks(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_ARBlocks();/* state var info */
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

extern void sf_internal_set_sim_state_c3_ARBlocks(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_ARBlocks();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_ARBlocks(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_ARBlocks(S);
}

static void sf_opaque_set_sim_state_c3_ARBlocks(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_ARBlocks(S, st);
}

static void sf_opaque_terminate_c3_ARBlocks(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_ARBlocksInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ARBlocks_optimization_info();
    }

    finalize_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_ARBlocks((SFc3_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_ARBlocks(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_ARBlocks((SFc3_ARBlocksInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ARBlocks_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,3,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4124947436U));
  ssSetChecksum1(S,(3464682207U));
  ssSetChecksum2(S,(274660146U));
  ssSetChecksum3(S,(2976473431U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_ARBlocks(SimStruct *S)
{
  SFc3_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc3_ARBlocksInstanceStruct *)utMalloc(sizeof
    (SFc3_ARBlocksInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_ARBlocksInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_ARBlocks;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_ARBlocks;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_ARBlocks;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_ARBlocks;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_ARBlocks;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_ARBlocks;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_ARBlocks;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_ARBlocks;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_ARBlocks;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_ARBlocks;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_ARBlocks;
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

void c3_ARBlocks_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_ARBlocks(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_ARBlocks(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_ARBlocks(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_ARBlocks_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
