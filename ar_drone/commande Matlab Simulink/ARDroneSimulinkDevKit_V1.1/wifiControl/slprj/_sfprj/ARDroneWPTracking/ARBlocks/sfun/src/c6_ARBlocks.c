/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ARBlocks_sfun.h"
#include "c6_ARBlocks.h"
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
static const char * c6_debug_family_names[6] = { "T", "nargin", "nargout",
  "Vel_b", "psi", "Vel_xy" };

/* Function Declarations */
static void initialize_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance);
static void initialize_params_c6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance);
static void enable_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance);
static void disable_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance);
static void c6_update_debugger_state_c6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance);
static void set_sim_state_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_st);
static void finalize_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance);
static void sf_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance);
static void c6_chartstep_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance);
static void initSimStructsc6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance);
static void registerMessagesc6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static void c6_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_Vel_xy, const char_T *c6_identifier, real_T c6_y[2]);
static void c6_b_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[2]);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_c_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_d_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[4]);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[13]);
static void c6_eml_scalar_eg(SFc6_ARBlocksInstanceStruct *chartInstance);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_e_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_f_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_b_is_active_c6_ARBlocks, const char_T *c6_identifier);
static uint8_T c6_g_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_ARBlocksInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c6_is_active_c6_ARBlocks = 0U;
}

static void initialize_params_c6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void enable_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c6_update_debugger_state_c6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  int32_T c6_i0;
  real_T c6_u[2];
  const mxArray *c6_b_y = NULL;
  uint8_T c6_hoistedGlobal;
  uint8_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  real_T (*c6_Vel_xy)[2];
  c6_Vel_xy = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellarray(2), FALSE);
  for (c6_i0 = 0; c6_i0 < 2; c6_i0++) {
    c6_u[c6_i0] = (*c6_Vel_xy)[c6_i0];
  }

  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_hoistedGlobal = chartInstance->c6_is_active_c6_ARBlocks;
  c6_b_u = c6_hoistedGlobal;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  sf_mex_assign(&c6_st, c6_y, FALSE);
  return c6_st;
}

static void set_sim_state_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv0[2];
  int32_T c6_i1;
  real_T (*c6_Vel_xy)[2];
  c6_Vel_xy = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = TRUE;
  c6_u = sf_mex_dup(c6_st);
  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)),
                      "Vel_xy", c6_dv0);
  for (c6_i1 = 0; c6_i1 < 2; c6_i1++) {
    (*c6_Vel_xy)[c6_i1] = c6_dv0[c6_i1];
  }

  chartInstance->c6_is_active_c6_ARBlocks = c6_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 1)), "is_active_c6_ARBlocks");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_ARBlocks(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance)
{
}

static void sf_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance)
{
  int32_T c6_i2;
  int32_T c6_i3;
  real_T *c6_psi;
  real_T (*c6_Vel_xy)[2];
  real_T (*c6_Vel_b)[2];
  c6_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_Vel_xy = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_Vel_b = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
  for (c6_i2 = 0; c6_i2 < 2; c6_i2++) {
    _SFD_DATA_RANGE_CHECK((*c6_Vel_b)[c6_i2], 0U);
  }

  for (c6_i3 = 0; c6_i3 < 2; c6_i3++) {
    _SFD_DATA_RANGE_CHECK((*c6_Vel_xy)[c6_i3], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c6_psi, 2U);
  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_ARBlocks(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ARBlocksMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c6_chartstep_c6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance)
{
  real_T c6_hoistedGlobal;
  int32_T c6_i4;
  real_T c6_Vel_b[2];
  real_T c6_psi;
  uint32_T c6_debug_family_var_map[6];
  real_T c6_T[4];
  real_T c6_nargin = 2.0;
  real_T c6_nargout = 1.0;
  real_T c6_Vel_xy[2];
  real_T c6_x;
  real_T c6_b_x;
  real_T c6_c_x;
  real_T c6_d_x;
  real_T c6_e_x;
  real_T c6_f_x;
  real_T c6_g_x;
  real_T c6_h_x;
  int32_T c6_i5;
  real_T c6_a[4];
  int32_T c6_i6;
  real_T c6_b[2];
  int32_T c6_i7;
  int32_T c6_i8;
  int32_T c6_i9;
  real_T c6_C[2];
  int32_T c6_i10;
  int32_T c6_i11;
  int32_T c6_i12;
  int32_T c6_i13;
  int32_T c6_i14;
  int32_T c6_i15;
  int32_T c6_i16;
  real_T *c6_b_psi;
  real_T (*c6_b_Vel_xy)[2];
  real_T (*c6_b_Vel_b)[2];
  c6_b_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_b_Vel_xy = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_Vel_b = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
  c6_hoistedGlobal = *c6_b_psi;
  for (c6_i4 = 0; c6_i4 < 2; c6_i4++) {
    c6_Vel_b[c6_i4] = (*c6_b_Vel_b)[c6_i4];
  }

  c6_psi = c6_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_T, 0U, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 1U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 2U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_Vel_b, 3U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_psi, 4U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_Vel_xy, 5U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 3);
  c6_x = c6_psi;
  c6_b_x = c6_x;
  c6_b_x = muDoubleScalarCos(c6_b_x);
  c6_c_x = c6_psi;
  c6_d_x = c6_c_x;
  c6_d_x = muDoubleScalarSin(c6_d_x);
  c6_e_x = c6_psi;
  c6_f_x = c6_e_x;
  c6_f_x = muDoubleScalarSin(c6_f_x);
  c6_g_x = c6_psi;
  c6_h_x = c6_g_x;
  c6_h_x = muDoubleScalarCos(c6_h_x);
  c6_T[0] = c6_b_x;
  c6_T[2] = -c6_d_x;
  c6_T[1] = c6_f_x;
  c6_T[3] = c6_h_x;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 4);
  for (c6_i5 = 0; c6_i5 < 4; c6_i5++) {
    c6_a[c6_i5] = c6_T[c6_i5];
  }

  for (c6_i6 = 0; c6_i6 < 2; c6_i6++) {
    c6_b[c6_i6] = c6_Vel_b[c6_i6];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i7 = 0; c6_i7 < 2; c6_i7++) {
    c6_Vel_xy[c6_i7] = 0.0;
  }

  for (c6_i8 = 0; c6_i8 < 2; c6_i8++) {
    c6_Vel_xy[c6_i8] = 0.0;
  }

  for (c6_i9 = 0; c6_i9 < 2; c6_i9++) {
    c6_C[c6_i9] = c6_Vel_xy[c6_i9];
  }

  for (c6_i10 = 0; c6_i10 < 2; c6_i10++) {
    c6_Vel_xy[c6_i10] = c6_C[c6_i10];
  }

  for (c6_i11 = 0; c6_i11 < 2; c6_i11++) {
    c6_C[c6_i11] = c6_Vel_xy[c6_i11];
  }

  for (c6_i12 = 0; c6_i12 < 2; c6_i12++) {
    c6_Vel_xy[c6_i12] = c6_C[c6_i12];
  }

  for (c6_i13 = 0; c6_i13 < 2; c6_i13++) {
    c6_Vel_xy[c6_i13] = 0.0;
    c6_i14 = 0;
    for (c6_i15 = 0; c6_i15 < 2; c6_i15++) {
      c6_Vel_xy[c6_i13] += c6_a[c6_i14 + c6_i13] * c6_b[c6_i15];
      c6_i14 += 2;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c6_i16 = 0; c6_i16 < 2; c6_i16++) {
    (*c6_b_Vel_xy)[c6_i16] = c6_Vel_xy[c6_i16];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_ARBlocks(SFc6_ARBlocksInstanceStruct *chartInstance)
{
}

static void registerMessagesc6_ARBlocks(SFc6_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber)
{
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i17;
  real_T c6_b_inData[2];
  int32_T c6_i18;
  real_T c6_u[2];
  const mxArray *c6_y = NULL;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i17 = 0; c6_i17 < 2; c6_i17++) {
    c6_b_inData[c6_i17] = (*(real_T (*)[2])c6_inData)[c6_i17];
  }

  for (c6_i18 = 0; c6_i18 < 2; c6_i18++) {
    c6_u[c6_i18] = c6_b_inData[c6_i18];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static void c6_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_Vel_xy, const char_T *c6_identifier, real_T c6_y[2])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_Vel_xy), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_Vel_xy);
}

static void c6_b_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[2])
{
  real_T c6_dv1[2];
  int32_T c6_i19;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv1, 1, 0, 0U, 1, 0U, 1, 2);
  for (c6_i19 = 0; c6_i19 < 2; c6_i19++) {
    c6_y[c6_i19] = c6_dv1[c6_i19];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_Vel_xy;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[2];
  int32_T c6_i20;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_Vel_xy = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_Vel_xy), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_Vel_xy);
  for (c6_i20 = 0; c6_i20 < 2; c6_i20++) {
    (*(real_T (*)[2])c6_outData)[c6_i20] = c6_y[c6_i20];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static real_T c6_c_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_nargout;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_nargout = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nargout), &c6_thisId);
  sf_mex_destroy(&c6_nargout);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i21;
  int32_T c6_i22;
  int32_T c6_i23;
  real_T c6_b_inData[4];
  int32_T c6_i24;
  int32_T c6_i25;
  int32_T c6_i26;
  real_T c6_u[4];
  const mxArray *c6_y = NULL;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_i21 = 0;
  for (c6_i22 = 0; c6_i22 < 2; c6_i22++) {
    for (c6_i23 = 0; c6_i23 < 2; c6_i23++) {
      c6_b_inData[c6_i23 + c6_i21] = (*(real_T (*)[4])c6_inData)[c6_i23 + c6_i21];
    }

    c6_i21 += 2;
  }

  c6_i24 = 0;
  for (c6_i25 = 0; c6_i25 < 2; c6_i25++) {
    for (c6_i26 = 0; c6_i26 < 2; c6_i26++) {
      c6_u[c6_i26 + c6_i24] = c6_b_inData[c6_i26 + c6_i24];
    }

    c6_i24 += 2;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static void c6_d_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[4])
{
  real_T c6_dv2[4];
  int32_T c6_i27;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv2, 1, 0, 0U, 1, 0U, 2, 2, 2);
  for (c6_i27 = 0; c6_i27 < 4; c6_i27++) {
    c6_y[c6_i27] = c6_dv2[c6_i27];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_T;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[4];
  int32_T c6_i28;
  int32_T c6_i29;
  int32_T c6_i30;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_T = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_T), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_T);
  c6_i28 = 0;
  for (c6_i29 = 0; c6_i29 < 2; c6_i29++) {
    for (c6_i30 = 0; c6_i30 < 2; c6_i30++) {
      (*(real_T (*)[4])c6_outData)[c6_i30 + c6_i28] = c6_y[c6_i30 + c6_i28];
    }

    c6_i28 += 2;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray *sf_c6_ARBlocks_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo;
  c6_ResolvedFunctionInfo c6_info[13];
  const mxArray *c6_m0 = NULL;
  int32_T c6_i31;
  c6_ResolvedFunctionInfo *c6_r0;
  c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  c6_info_helper(c6_info);
  sf_mex_assign(&c6_m0, sf_mex_createstruct("nameCaptureInfo", 1, 13), FALSE);
  for (c6_i31 = 0; c6_i31 < 13; c6_i31++) {
    c6_r0 = &c6_info[c6_i31];
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->context)), "context", "nameCaptureInfo",
                    c6_i31);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c6_r0->name)), "name", "nameCaptureInfo", c6_i31);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c6_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c6_i31);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->resolved)), "resolved", "nameCaptureInfo",
                    c6_i31);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c6_i31);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c6_i31);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c6_i31);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c6_i31);
  }

  sf_mex_assign(&c6_nameCaptureInfo, c6_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c6_nameCaptureInfo);
  return c6_nameCaptureInfo;
}

static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[13])
{
  c6_info[0].context = "";
  c6_info[0].name = "cos";
  c6_info[0].dominantType = "double";
  c6_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c6_info[0].fileTimeLo = 1343830372U;
  c6_info[0].fileTimeHi = 0U;
  c6_info[0].mFileTimeLo = 0U;
  c6_info[0].mFileTimeHi = 0U;
  c6_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c6_info[1].name = "eml_scalar_cos";
  c6_info[1].dominantType = "double";
  c6_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c6_info[1].fileTimeLo = 1286818722U;
  c6_info[1].fileTimeHi = 0U;
  c6_info[1].mFileTimeLo = 0U;
  c6_info[1].mFileTimeHi = 0U;
  c6_info[2].context = "";
  c6_info[2].name = "sin";
  c6_info[2].dominantType = "double";
  c6_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c6_info[2].fileTimeLo = 1343830386U;
  c6_info[2].fileTimeHi = 0U;
  c6_info[2].mFileTimeLo = 0U;
  c6_info[2].mFileTimeHi = 0U;
  c6_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c6_info[3].name = "eml_scalar_sin";
  c6_info[3].dominantType = "double";
  c6_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c6_info[3].fileTimeLo = 1286818736U;
  c6_info[3].fileTimeHi = 0U;
  c6_info[3].mFileTimeLo = 0U;
  c6_info[3].mFileTimeHi = 0U;
  c6_info[4].context = "";
  c6_info[4].name = "mtimes";
  c6_info[4].dominantType = "double";
  c6_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[4].fileTimeLo = 1289519692U;
  c6_info[4].fileTimeHi = 0U;
  c6_info[4].mFileTimeLo = 0U;
  c6_info[4].mFileTimeHi = 0U;
  c6_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[5].name = "eml_index_class";
  c6_info[5].dominantType = "";
  c6_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[5].fileTimeLo = 1323170578U;
  c6_info[5].fileTimeHi = 0U;
  c6_info[5].mFileTimeLo = 0U;
  c6_info[5].mFileTimeHi = 0U;
  c6_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[6].name = "eml_scalar_eg";
  c6_info[6].dominantType = "double";
  c6_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[6].fileTimeLo = 1286818796U;
  c6_info[6].fileTimeHi = 0U;
  c6_info[6].mFileTimeLo = 0U;
  c6_info[6].mFileTimeHi = 0U;
  c6_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[7].name = "eml_xgemm";
  c6_info[7].dominantType = "char";
  c6_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[7].fileTimeLo = 1299076772U;
  c6_info[7].fileTimeHi = 0U;
  c6_info[7].mFileTimeLo = 0U;
  c6_info[7].mFileTimeHi = 0U;
  c6_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[8].name = "eml_blas_inline";
  c6_info[8].dominantType = "";
  c6_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[8].fileTimeLo = 1299076768U;
  c6_info[8].fileTimeHi = 0U;
  c6_info[8].mFileTimeLo = 0U;
  c6_info[8].mFileTimeHi = 0U;
  c6_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c6_info[9].name = "mtimes";
  c6_info[9].dominantType = "double";
  c6_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[9].fileTimeLo = 1289519692U;
  c6_info[9].fileTimeHi = 0U;
  c6_info[9].mFileTimeLo = 0U;
  c6_info[9].mFileTimeHi = 0U;
  c6_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[10].name = "eml_index_class";
  c6_info[10].dominantType = "";
  c6_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[10].fileTimeLo = 1323170578U;
  c6_info[10].fileTimeHi = 0U;
  c6_info[10].mFileTimeLo = 0U;
  c6_info[10].mFileTimeHi = 0U;
  c6_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[11].name = "eml_scalar_eg";
  c6_info[11].dominantType = "double";
  c6_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[11].fileTimeLo = 1286818796U;
  c6_info[11].fileTimeHi = 0U;
  c6_info[11].mFileTimeLo = 0U;
  c6_info[11].mFileTimeHi = 0U;
  c6_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[12].name = "eml_refblas_xgemm";
  c6_info[12].dominantType = "char";
  c6_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c6_info[12].fileTimeLo = 1299076774U;
  c6_info[12].fileTimeHi = 0U;
  c6_info[12].mFileTimeLo = 0U;
  c6_info[12].mFileTimeHi = 0U;
}

static void c6_eml_scalar_eg(SFc6_ARBlocksInstanceStruct *chartInstance)
{
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static int32_T c6_e_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i32;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i32, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i32;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_f_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_b_is_active_c6_ARBlocks, const char_T *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_ARBlocks), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_ARBlocks);
  return c6_y;
}

static uint8_T c6_g_emlrt_marshallIn(SFc6_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_ARBlocksInstanceStruct *chartInstance)
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

void sf_c6_ARBlocks_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(78624191U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1433190467U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(711772385U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1562882279U);
}

mxArray *sf_c6_ARBlocks_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("5E0ZMt4gT0b9vhD6qTo22D");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_ARBlocks_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c6_ARBlocks(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"Vel_xy\",},{M[8],M[0],T\"is_active_c6_ARBlocks\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_ARBlocks_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_ARBlocksInstanceStruct *chartInstance;
    chartInstance = (SFc6_ARBlocksInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ARBlocksMachineNumber_,
           6,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"Vel_b");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Vel_xy");
          _SFD_SET_DATA_PROPS(2,1,1,0,"psi");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,110);
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
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)
            c6_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c6_psi;
          real_T (*c6_Vel_b)[2];
          real_T (*c6_Vel_xy)[2];
          c6_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c6_Vel_xy = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          c6_Vel_b = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c6_Vel_b);
          _SFD_SET_DATA_VALUE_PTR(1U, *c6_Vel_xy);
          _SFD_SET_DATA_VALUE_PTR(2U, c6_psi);
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
  return "mMZCgJvKgNjN0xJS5cBmMB";
}

static void sf_opaque_initialize_c6_ARBlocks(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_ARBlocksInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*) chartInstanceVar);
  initialize_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_ARBlocks(void *chartInstanceVar)
{
  enable_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_ARBlocks(void *chartInstanceVar)
{
  disable_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_ARBlocks(void *chartInstanceVar)
{
  sf_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c6_ARBlocks(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_ARBlocks();/* state var info */
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

extern void sf_internal_set_sim_state_c6_ARBlocks(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_ARBlocks();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_ARBlocks(SimStruct* S)
{
  return sf_internal_get_sim_state_c6_ARBlocks(S);
}

static void sf_opaque_set_sim_state_c6_ARBlocks(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c6_ARBlocks(S, st);
}

static void sf_opaque_terminate_c6_ARBlocks(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_ARBlocksInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ARBlocks_optimization_info();
    }

    finalize_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_ARBlocks((SFc6_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_ARBlocks(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_ARBlocks((SFc6_ARBlocksInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ARBlocks_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,6,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3849061815U));
  ssSetChecksum1(S,(2945241492U));
  ssSetChecksum2(S,(1230969334U));
  ssSetChecksum3(S,(2080595350U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_ARBlocks(SimStruct *S)
{
  SFc6_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc6_ARBlocksInstanceStruct *)utMalloc(sizeof
    (SFc6_ARBlocksInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_ARBlocksInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_ARBlocks;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c6_ARBlocks;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c6_ARBlocks;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_ARBlocks;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_ARBlocks;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_ARBlocks;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_ARBlocks;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c6_ARBlocks;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_ARBlocks;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_ARBlocks;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_ARBlocks;
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

void c6_ARBlocks_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_ARBlocks(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_ARBlocks(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_ARBlocks(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_ARBlocks_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
