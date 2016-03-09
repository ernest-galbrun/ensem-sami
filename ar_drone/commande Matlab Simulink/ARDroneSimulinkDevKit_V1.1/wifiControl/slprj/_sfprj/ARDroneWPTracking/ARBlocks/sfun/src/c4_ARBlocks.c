/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ARBlocks_sfun.h"
#include "c4_ARBlocks.h"
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
static const char * c4_debug_family_names[8] = { "nargin", "nargout", "isFlying",
  "enableCmds", "yaw", "yawOut", "yaw0", "mode" };

/* Function Declarations */
static void initialize_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance);
static void initialize_params_c4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance);
static void enable_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance);
static void disable_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance);
static void set_sim_state_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_st);
static void finalize_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance);
static void sf_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance);
static void initSimStructsc4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance);
static void registerMessagesc4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static real_T c4_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_b_mode, const char_T *c4_identifier);
static real_T c4_b_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_c_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_b_yaw0, const char_T *c4_identifier);
static real_T c4_d_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_e_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_yawOut, const char_T *c4_identifier);
static real_T c4_f_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_eml_scalar_eg(SFc4_ARBlocksInstanceStruct *chartInstance);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_g_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_h_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_ARBlocks, const char_T *c4_identifier);
static uint8_T c4_i_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_ARBlocksInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_yaw0_not_empty = FALSE;
  chartInstance->c4_mode_not_empty = FALSE;
  chartInstance->c4_is_active_c4_ARBlocks = 0U;
}

static void initialize_params_c4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void enable_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  real_T c4_hoistedGlobal;
  real_T c4_u;
  const mxArray *c4_b_y = NULL;
  real_T c4_b_hoistedGlobal;
  real_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  real_T c4_c_hoistedGlobal;
  real_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  uint8_T c4_d_hoistedGlobal;
  uint8_T c4_d_u;
  const mxArray *c4_e_y = NULL;
  real_T *c4_yawOut;
  c4_yawOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(4), FALSE);
  c4_hoistedGlobal = *c4_yawOut;
  c4_u = c4_hoistedGlobal;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_b_hoistedGlobal = chartInstance->c4_mode;
  c4_b_u = c4_b_hoistedGlobal;
  c4_c_y = NULL;
  if (!chartInstance->c4_mode_not_empty) {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_c_hoistedGlobal = chartInstance->c4_yaw0;
  c4_c_u = c4_c_hoistedGlobal;
  c4_d_y = NULL;
  if (!chartInstance->c4_yaw0_not_empty) {
    sf_mex_assign(&c4_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_d_hoistedGlobal = chartInstance->c4_is_active_c4_ARBlocks;
  c4_d_u = c4_d_hoistedGlobal;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 3, c4_e_y);
  sf_mex_assign(&c4_st, c4_y, FALSE);
  return c4_st;
}

static void set_sim_state_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T *c4_yawOut;
  c4_yawOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
  c4_u = sf_mex_dup(c4_st);
  *c4_yawOut = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c4_u, 0)), "yawOut");
  chartInstance->c4_mode = c4_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 1)), "mode");
  chartInstance->c4_yaw0 = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 2)), "yaw0");
  chartInstance->c4_is_active_c4_ARBlocks = c4_h_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 3)), "is_active_c4_ARBlocks");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_ARBlocks(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance)
{
}

static void sf_c4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance)
{
  real_T c4_hoistedGlobal;
  real_T c4_b_hoistedGlobal;
  real_T c4_c_hoistedGlobal;
  real_T c4_isFlying;
  real_T c4_enableCmds;
  real_T c4_yaw;
  uint32_T c4_debug_family_var_map[8];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  real_T c4_yawOut;
  real_T c4_x;
  real_T c4_xk;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_d_x;
  real_T *c4_b_yaw;
  real_T *c4_b_enableCmds;
  real_T *c4_b_isFlying;
  real_T *c4_b_yawOut;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  c4_b_yaw = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c4_b_yawOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_enableCmds = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_isFlying = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c4_b_isFlying, 0U);
  _SFD_DATA_RANGE_CHECK(*c4_b_enableCmds, 1U);
  _SFD_DATA_RANGE_CHECK(*c4_b_yawOut, 2U);
  _SFD_DATA_RANGE_CHECK(*c4_b_yaw, 3U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *c4_b_isFlying;
  c4_b_hoistedGlobal = *c4_b_enableCmds;
  c4_c_hoistedGlobal = *c4_b_yaw;
  c4_isFlying = c4_hoistedGlobal;
  c4_enableCmds = c4_b_hoistedGlobal;
  c4_yaw = c4_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_isFlying, 2U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_enableCmds, 3U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_yaw, 4U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_yawOut, 5U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_yaw0, 6U,
    c4_b_sf_marshallOut, c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_mode, 7U,
    c4_sf_marshallOut, c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 6);
  c4_yawOut = c4_yaw;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 7);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 10);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c4_yaw0_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 11);
    chartInstance->c4_yaw0 = 0.0;
    chartInstance->c4_yaw0_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 15);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c4_mode_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
    chartInstance->c4_mode = 0.0;
    chartInstance->c4_mode_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
  guard1 = FALSE;
  if (CV_EML_COND(0, 1, 0, c4_isFlying == 1.0)) {
    if (CV_EML_COND(0, 1, 1, c4_enableCmds == 1.0)) {
      CV_EML_MCDC(0, 1, 0, TRUE);
      CV_EML_IF(0, 1, 2, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 20);
      c4_yawOut = c4_yaw - chartInstance->c4_yaw0;
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 21);
      chartInstance->c4_mode = 1.0;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 2, FALSE);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 22);
    guard2 = FALSE;
    if (CV_EML_COND(0, 1, 2, c4_isFlying == 1.0)) {
      if (CV_EML_COND(0, 1, 3, chartInstance->c4_mode == 0.0)) {
        CV_EML_MCDC(0, 1, 1, TRUE);
        CV_EML_IF(0, 1, 3, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 23);
        chartInstance->c4_yaw0 = c4_yaw;
      } else {
        guard2 = TRUE;
      }
    } else {
      guard2 = TRUE;
    }

    if (guard2 == TRUE) {
      CV_EML_MCDC(0, 1, 1, FALSE);
      CV_EML_IF(0, 1, 3, FALSE);
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 27);
  c4_x = c4_yawOut;
  c4_eml_scalar_eg(chartInstance);
  c4_xk = c4_x;
  c4_b_x = c4_xk;
  c4_eml_scalar_eg(chartInstance);
  c4_c_x = c4_b_x / 360.0;
  c4_d_x = c4_c_x;
  c4_d_x = muDoubleScalarFloor(c4_d_x);
  c4_yawOut = c4_b_x - c4_d_x * 360.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 28);
  if (CV_EML_IF(0, 1, 4, c4_yawOut > 180.0)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 29);
    c4_yawOut += -360.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -29);
  _SFD_SYMBOL_SCOPE_POP();
  *c4_b_yawOut = c4_yawOut;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ARBlocksMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc4_ARBlocks(SFc4_ARBlocksInstanceStruct *chartInstance)
{
}

static void registerMessagesc4_ARBlocks(SFc4_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_mode_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_b_mode, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_mode), &c4_thisId);
  sf_mex_destroy(&c4_b_mode);
  return c4_y;
}

static real_T c4_b_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_mode_not_empty = FALSE;
  } else {
    chartInstance->c4_mode_not_empty = TRUE;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d0;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_mode;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_b_mode = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_mode), &c4_thisId);
  sf_mex_destroy(&c4_b_mode);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_yaw0_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_c_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_b_yaw0, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_yaw0), &c4_thisId);
  sf_mex_destroy(&c4_b_yaw0);
  return c4_y;
}

static real_T c4_d_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d1;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_yaw0_not_empty = FALSE;
  } else {
    chartInstance->c4_yaw0_not_empty = TRUE;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d1, 1, 0, 0U, 0, 0U, 0);
    c4_y = c4_d1;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_yaw0;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_b_yaw0 = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_yaw0), &c4_thisId);
  sf_mex_destroy(&c4_b_yaw0);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_e_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_yawOut, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_yawOut), &c4_thisId);
  sf_mex_destroy(&c4_yawOut);
  return c4_y;
}

static real_T c4_f_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d2;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d2, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d2;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_yawOut;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_yawOut = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_yawOut), &c4_thisId);
  sf_mex_destroy(&c4_yawOut);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_ARBlocks_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[12];
  c4_ResolvedFunctionInfo (*c4_b_info)[12];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i0;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  c4_b_info = (c4_ResolvedFunctionInfo (*)[12])c4_info;
  (*c4_b_info)[0].context = "";
  (*c4_b_info)[0].name = "mod";
  (*c4_b_info)[0].dominantType = "double";
  (*c4_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  (*c4_b_info)[0].fileTimeLo = 1343830382U;
  (*c4_b_info)[0].fileTimeHi = 0U;
  (*c4_b_info)[0].mFileTimeLo = 0U;
  (*c4_b_info)[0].mFileTimeHi = 0U;
  (*c4_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  (*c4_b_info)[1].name = "eml_scalar_eg";
  (*c4_b_info)[1].dominantType = "double";
  (*c4_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c4_b_info)[1].fileTimeLo = 1286818796U;
  (*c4_b_info)[1].fileTimeHi = 0U;
  (*c4_b_info)[1].mFileTimeLo = 0U;
  (*c4_b_info)[1].mFileTimeHi = 0U;
  (*c4_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  (*c4_b_info)[2].name = "eml_scalexp_alloc";
  (*c4_b_info)[2].dominantType = "double";
  (*c4_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  (*c4_b_info)[2].fileTimeLo = 1352424860U;
  (*c4_b_info)[2].fileTimeHi = 0U;
  (*c4_b_info)[2].mFileTimeLo = 0U;
  (*c4_b_info)[2].mFileTimeHi = 0U;
  (*c4_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  (*c4_b_info)[3].name = "eml_scalar_eg";
  (*c4_b_info)[3].dominantType = "double";
  (*c4_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c4_b_info)[3].fileTimeLo = 1286818796U;
  (*c4_b_info)[3].fileTimeHi = 0U;
  (*c4_b_info)[3].mFileTimeLo = 0U;
  (*c4_b_info)[3].mFileTimeHi = 0U;
  (*c4_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  (*c4_b_info)[4].name = "eml_scalar_floor";
  (*c4_b_info)[4].dominantType = "double";
  (*c4_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  (*c4_b_info)[4].fileTimeLo = 1286818726U;
  (*c4_b_info)[4].fileTimeHi = 0U;
  (*c4_b_info)[4].mFileTimeLo = 0U;
  (*c4_b_info)[4].mFileTimeHi = 0U;
  (*c4_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  (*c4_b_info)[5].name = "eml_scalar_round";
  (*c4_b_info)[5].dominantType = "double";
  (*c4_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  (*c4_b_info)[5].fileTimeLo = 1307651238U;
  (*c4_b_info)[5].fileTimeHi = 0U;
  (*c4_b_info)[5].mFileTimeLo = 0U;
  (*c4_b_info)[5].mFileTimeHi = 0U;
  (*c4_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  (*c4_b_info)[6].name = "eml_scalar_abs";
  (*c4_b_info)[6].dominantType = "double";
  (*c4_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  (*c4_b_info)[6].fileTimeLo = 1286818712U;
  (*c4_b_info)[6].fileTimeHi = 0U;
  (*c4_b_info)[6].mFileTimeLo = 0U;
  (*c4_b_info)[6].mFileTimeHi = 0U;
  (*c4_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  (*c4_b_info)[7].name = "eps";
  (*c4_b_info)[7].dominantType = "char";
  (*c4_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  (*c4_b_info)[7].fileTimeLo = 1326727996U;
  (*c4_b_info)[7].fileTimeHi = 0U;
  (*c4_b_info)[7].mFileTimeLo = 0U;
  (*c4_b_info)[7].mFileTimeHi = 0U;
  (*c4_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  (*c4_b_info)[8].name = "eml_is_float_class";
  (*c4_b_info)[8].dominantType = "char";
  (*c4_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  (*c4_b_info)[8].fileTimeLo = 1286818782U;
  (*c4_b_info)[8].fileTimeHi = 0U;
  (*c4_b_info)[8].mFileTimeLo = 0U;
  (*c4_b_info)[8].mFileTimeHi = 0U;
  (*c4_b_info)[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  (*c4_b_info)[9].name = "eml_eps";
  (*c4_b_info)[9].dominantType = "char";
  (*c4_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  (*c4_b_info)[9].fileTimeLo = 1326727996U;
  (*c4_b_info)[9].fileTimeHi = 0U;
  (*c4_b_info)[9].mFileTimeLo = 0U;
  (*c4_b_info)[9].mFileTimeHi = 0U;
  (*c4_b_info)[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  (*c4_b_info)[10].name = "eml_float_model";
  (*c4_b_info)[10].dominantType = "char";
  (*c4_b_info)[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  (*c4_b_info)[10].fileTimeLo = 1326727996U;
  (*c4_b_info)[10].fileTimeHi = 0U;
  (*c4_b_info)[10].mFileTimeLo = 0U;
  (*c4_b_info)[10].mFileTimeHi = 0U;
  (*c4_b_info)[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod";
  (*c4_b_info)[11].name = "mtimes";
  (*c4_b_info)[11].dominantType = "double";
  (*c4_b_info)[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c4_b_info)[11].fileTimeLo = 1289519692U;
  (*c4_b_info)[11].fileTimeHi = 0U;
  (*c4_b_info)[11].mFileTimeLo = 0U;
  (*c4_b_info)[11].mFileTimeHi = 0U;
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 12), FALSE);
  for (c4_i0 = 0; c4_i0 < 12; c4_i0++) {
    c4_r0 = &c4_info[c4_i0];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i0);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i0);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i0);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i0);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i0);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i0);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i0);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i0);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_eml_scalar_eg(SFc4_ARBlocksInstanceStruct *chartInstance)
{
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static int32_T c4_g_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i1;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i1, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i1;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_h_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_ARBlocks, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_ARBlocks), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_ARBlocks);
  return c4_y;
}

static uint8_T c4_i_emlrt_marshallIn(SFc4_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_ARBlocksInstanceStruct *chartInstance)
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

void sf_c4_ARBlocks_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2210100224U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2940346214U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2498497699U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(223588102U);
}

mxArray *sf_c4_ARBlocks_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ZJyrVj5Pg2Ig5hWLC19MJB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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

mxArray *sf_c4_ARBlocks_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c4_ARBlocks(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[5],T\"yawOut\",},{M[4],M[0],T\"mode\",S'l','i','p'{{M1x2[195 199],M[0],}}},{M[4],M[0],T\"yaw0\",S'l','i','p'{{M1x2[176 180],M[0],}}},{M[8],M[0],T\"is_active_c4_ARBlocks\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_ARBlocks_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_ARBlocksInstanceStruct *chartInstance;
    chartInstance = (SFc4_ARBlocksInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ARBlocksMachineNumber_,
           4,
           1,
           1,
           4,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"isFlying");
          _SFD_SET_DATA_PROPS(1,1,1,0,"enableCmds");
          _SFD_SET_DATA_PROPS(2,2,0,1,"yawOut");
          _SFD_SET_DATA_PROPS(3,1,1,0,"yaw");
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
        _SFD_CV_INIT_EML(0,1,1,5,0,0,0,0,0,4,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",92,-1,482);
        _SFD_CV_INIT_EML_IF(0,1,0,204,221,-1,236);
        _SFD_CV_INIT_EML_IF(0,1,1,239,256,-1,269);
        _SFD_CV_INIT_EML_IF(0,1,2,271,303,348,379);
        _SFD_CV_INIT_EML_IF(0,1,3,348,379,-1,379);
        _SFD_CV_INIT_EML_IF(0,1,4,431,446,-1,480);

        {
          static int condStart[] = { 274, 290 };

          static int condEnd[] = { 286, 303 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,274,303,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 355, 371 };

          static int condEnd[] = { 367, 379 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,355,379,2,2,&(condStart[0]),&(condEnd[0]),
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

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)c4_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c4_isFlying;
          real_T *c4_enableCmds;
          real_T *c4_yawOut;
          real_T *c4_yaw;
          c4_yaw = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c4_yawOut = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c4_enableCmds = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c4_isFlying = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c4_isFlying);
          _SFD_SET_DATA_VALUE_PTR(1U, c4_enableCmds);
          _SFD_SET_DATA_VALUE_PTR(2U, c4_yawOut);
          _SFD_SET_DATA_VALUE_PTR(3U, c4_yaw);
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
  return "6CKhXn4ud8A3MOS9pXY3mD";
}

static void sf_opaque_initialize_c4_ARBlocks(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_ARBlocksInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*) chartInstanceVar);
  initialize_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_ARBlocks(void *chartInstanceVar)
{
  enable_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_ARBlocks(void *chartInstanceVar)
{
  disable_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_ARBlocks(void *chartInstanceVar)
{
  sf_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_ARBlocks(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_ARBlocks();/* state var info */
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

extern void sf_internal_set_sim_state_c4_ARBlocks(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_ARBlocks();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_ARBlocks(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_ARBlocks(S);
}

static void sf_opaque_set_sim_state_c4_ARBlocks(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c4_ARBlocks(S, st);
}

static void sf_opaque_terminate_c4_ARBlocks(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_ARBlocksInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ARBlocks_optimization_info();
    }

    finalize_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_ARBlocks((SFc4_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_ARBlocks(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_ARBlocks((SFc4_ARBlocksInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ARBlocks_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,4,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1152680533U));
  ssSetChecksum1(S,(2707289719U));
  ssSetChecksum2(S,(4006609498U));
  ssSetChecksum3(S,(415406633U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_ARBlocks(SimStruct *S)
{
  SFc4_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc4_ARBlocksInstanceStruct *)utMalloc(sizeof
    (SFc4_ARBlocksInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_ARBlocksInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_ARBlocks;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_ARBlocks;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_ARBlocks;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_ARBlocks;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_ARBlocks;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_ARBlocks;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_ARBlocks;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_ARBlocks;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_ARBlocks;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_ARBlocks;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_ARBlocks;
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

void c4_ARBlocks_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_ARBlocks(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_ARBlocks(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_ARBlocks(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_ARBlocks_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
