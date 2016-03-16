/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ARBlocks_sfun.h"
#include "c9_ARBlocks.h"
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
static const char * c9_debug_family_names[15] = { "nPoints", "nargin", "nargout",
  "waypoint", "psi", "Pned", "h", "time", "psiRef", "hRef", "XeRef", "YeRef",
  "waypointNumber", "wpointer", "t0" };

/* Function Declarations */
static void initialize_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance);
static void initialize_params_c9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance);
static void enable_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance);
static void disable_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance);
static void c9_update_debugger_state_c9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance);
static void set_sim_state_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_st);
static void finalize_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance);
static void sf_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance);
static void c9_chartstep_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance);
static void initSimStructsc9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance);
static void registerMessagesc9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static real_T c9_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_b_t0, const char_T *c9_identifier);
static real_T c9_b_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_c_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_b_wpointer, const char_T *c9_identifier);
static real_T c9_d_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_e_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_waypointNumber, const char_T *c9_identifier);
static real_T c9_f_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_e_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[26]);
static const mxArray *c9_f_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_g_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static uint8_T c9_h_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_b_is_active_c9_ARBlocks, const char_T *c9_identifier);
static uint8_T c9_i_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void init_dsm_address_info(SFc9_ARBlocksInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance)
{
  chartInstance->c9_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c9_wpointer_not_empty = FALSE;
  chartInstance->c9_t0_not_empty = FALSE;
  chartInstance->c9_is_active_c9_ARBlocks = 0U;
}

static void initialize_params_c9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void enable_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c9_update_debugger_state_c9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  real_T c9_hoistedGlobal;
  real_T c9_u;
  const mxArray *c9_b_y = NULL;
  real_T c9_b_hoistedGlobal;
  real_T c9_b_u;
  const mxArray *c9_c_y = NULL;
  real_T c9_c_hoistedGlobal;
  real_T c9_c_u;
  const mxArray *c9_d_y = NULL;
  real_T c9_d_hoistedGlobal;
  real_T c9_d_u;
  const mxArray *c9_e_y = NULL;
  real_T c9_e_hoistedGlobal;
  real_T c9_e_u;
  const mxArray *c9_f_y = NULL;
  real_T c9_f_hoistedGlobal;
  real_T c9_f_u;
  const mxArray *c9_g_y = NULL;
  real_T c9_g_hoistedGlobal;
  real_T c9_g_u;
  const mxArray *c9_h_y = NULL;
  uint8_T c9_h_hoistedGlobal;
  uint8_T c9_h_u;
  const mxArray *c9_i_y = NULL;
  real_T *c9_XeRef;
  real_T *c9_YeRef;
  real_T *c9_hRef;
  real_T *c9_psiRef;
  real_T *c9_waypointNumber;
  c9_waypointNumber = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c9_YeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c9_XeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_hRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c9_psiRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellarray(8), FALSE);
  c9_hoistedGlobal = *c9_XeRef;
  c9_u = c9_hoistedGlobal;
  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 0, c9_b_y);
  c9_b_hoistedGlobal = *c9_YeRef;
  c9_b_u = c9_b_hoistedGlobal;
  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", &c9_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 1, c9_c_y);
  c9_c_hoistedGlobal = *c9_hRef;
  c9_c_u = c9_c_hoistedGlobal;
  c9_d_y = NULL;
  sf_mex_assign(&c9_d_y, sf_mex_create("y", &c9_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 2, c9_d_y);
  c9_d_hoistedGlobal = *c9_psiRef;
  c9_d_u = c9_d_hoistedGlobal;
  c9_e_y = NULL;
  sf_mex_assign(&c9_e_y, sf_mex_create("y", &c9_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 3, c9_e_y);
  c9_e_hoistedGlobal = *c9_waypointNumber;
  c9_e_u = c9_e_hoistedGlobal;
  c9_f_y = NULL;
  sf_mex_assign(&c9_f_y, sf_mex_create("y", &c9_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 4, c9_f_y);
  c9_f_hoistedGlobal = chartInstance->c9_t0;
  c9_f_u = c9_f_hoistedGlobal;
  c9_g_y = NULL;
  if (!chartInstance->c9_t0_not_empty) {
    sf_mex_assign(&c9_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c9_g_y, sf_mex_create("y", &c9_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c9_y, 5, c9_g_y);
  c9_g_hoistedGlobal = chartInstance->c9_wpointer;
  c9_g_u = c9_g_hoistedGlobal;
  c9_h_y = NULL;
  if (!chartInstance->c9_wpointer_not_empty) {
    sf_mex_assign(&c9_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c9_h_y, sf_mex_create("y", &c9_g_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c9_y, 6, c9_h_y);
  c9_h_hoistedGlobal = chartInstance->c9_is_active_c9_ARBlocks;
  c9_h_u = c9_h_hoistedGlobal;
  c9_i_y = NULL;
  sf_mex_assign(&c9_i_y, sf_mex_create("y", &c9_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 7, c9_i_y);
  sf_mex_assign(&c9_st, c9_y, FALSE);
  return c9_st;
}

static void set_sim_state_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_st)
{
  const mxArray *c9_u;
  real_T *c9_XeRef;
  real_T *c9_YeRef;
  real_T *c9_hRef;
  real_T *c9_psiRef;
  real_T *c9_waypointNumber;
  c9_waypointNumber = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c9_YeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c9_XeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_hRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c9_psiRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c9_doneDoubleBufferReInit = TRUE;
  c9_u = sf_mex_dup(c9_st);
  *c9_XeRef = c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c9_u, 0)), "XeRef");
  *c9_YeRef = c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c9_u, 1)), "YeRef");
  *c9_hRef = c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u,
    2)), "hRef");
  *c9_psiRef = c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c9_u, 3)), "psiRef");
  *c9_waypointNumber = c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c9_u, 4)), "waypointNumber");
  chartInstance->c9_t0 = c9_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c9_u, 5)), "t0");
  chartInstance->c9_wpointer = c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c9_u, 6)), "wpointer");
  chartInstance->c9_is_active_c9_ARBlocks = c9_h_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c9_u, 7)), "is_active_c9_ARBlocks");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_ARBlocks(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance)
{
}

static void sf_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance)
{
  int32_T c9_i0;
  int32_T c9_i1;
  real_T *c9_psiRef;
  real_T *c9_hRef;
  real_T *c9_psi;
  real_T *c9_h;
  real_T *c9_XeRef;
  real_T *c9_YeRef;
  real_T *c9_time;
  real_T *c9_waypointNumber;
  real_T (*c9_Pned)[2];
  real_T (*c9_waypoint)[250];
  c9_waypointNumber = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c9_time = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c9_YeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c9_XeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c9_Pned = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c9_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c9_waypoint = (real_T (*)[250])ssGetInputPortSignal(chartInstance->S, 0);
  c9_hRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c9_psiRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, chartInstance->c9_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c9_psiRef, 0U);
  _SFD_DATA_RANGE_CHECK(*c9_hRef, 1U);
  for (c9_i0 = 0; c9_i0 < 250; c9_i0++) {
    _SFD_DATA_RANGE_CHECK((*c9_waypoint)[c9_i0], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c9_psi, 3U);
  for (c9_i1 = 0; c9_i1 < 2; c9_i1++) {
    _SFD_DATA_RANGE_CHECK((*c9_Pned)[c9_i1], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c9_h, 5U);
  _SFD_DATA_RANGE_CHECK(*c9_XeRef, 6U);
  _SFD_DATA_RANGE_CHECK(*c9_YeRef, 7U);
  _SFD_DATA_RANGE_CHECK(*c9_time, 8U);
  _SFD_DATA_RANGE_CHECK(*c9_waypointNumber, 9U);
  chartInstance->c9_sfEvent = CALL_EVENT;
  c9_chartstep_c9_ARBlocks(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ARBlocksMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c9_chartstep_c9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance)
{
  real_T c9_hoistedGlobal;
  real_T c9_b_hoistedGlobal;
  real_T c9_c_hoistedGlobal;
  int32_T c9_i2;
  real_T c9_waypoint[250];
  real_T c9_psi;
  int32_T c9_i3;
  real_T c9_Pned[2];
  real_T c9_h;
  real_T c9_time;
  uint32_T c9_debug_family_var_map[15];
  real_T c9_nPoints;
  real_T c9_nargin = 5.0;
  real_T c9_nargout = 5.0;
  real_T c9_psiRef;
  real_T c9_hRef;
  real_T c9_XeRef;
  real_T c9_YeRef;
  real_T c9_waypointNumber;
  real_T c9_d_hoistedGlobal;
  int32_T c9_e_hoistedGlobal;
  int32_T c9_i4;
  real_T c9_x[2];
  real_T c9_y;
  real_T c9_scale;
  int32_T c9_k;
  int32_T c9_b_k;
  real_T c9_b_x;
  real_T c9_c_x;
  real_T c9_absxk;
  real_T c9_t;
  real_T c9_f_hoistedGlobal;
  real_T c9_d_x;
  real_T c9_e_x;
  real_T c9_f_x;
  real_T c9_b_y;
  real_T c9_g_hoistedGlobal;
  real_T c9_g_x;
  real_T c9_h_x;
  real_T c9_i_x;
  real_T c9_c_y;
  real_T *c9_b_psi;
  real_T *c9_b_h;
  real_T *c9_b_time;
  real_T *c9_b_psiRef;
  real_T *c9_b_hRef;
  real_T *c9_b_XeRef;
  real_T *c9_b_YeRef;
  real_T *c9_b_waypointNumber;
  real_T (*c9_b_Pned)[2];
  real_T (*c9_b_waypoint)[250];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  c9_b_waypointNumber = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c9_b_time = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c9_b_YeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c9_b_XeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_b_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c9_b_Pned = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c9_b_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c9_b_waypoint = (real_T (*)[250])ssGetInputPortSignal(chartInstance->S, 0);
  c9_b_hRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c9_b_psiRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c9_sfEvent);
  c9_hoistedGlobal = *c9_b_psi;
  c9_b_hoistedGlobal = *c9_b_h;
  c9_c_hoistedGlobal = *c9_b_time;
  for (c9_i2 = 0; c9_i2 < 250; c9_i2++) {
    c9_waypoint[c9_i2] = (*c9_b_waypoint)[c9_i2];
  }

  c9_psi = c9_hoistedGlobal;
  for (c9_i3 = 0; c9_i3 < 2; c9_i3++) {
    c9_Pned[c9_i3] = (*c9_b_Pned)[c9_i3];
  }

  c9_h = c9_b_hoistedGlobal;
  c9_time = c9_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 15U, 15U, c9_debug_family_names,
    c9_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nPoints, 0U, c9_c_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargin, 1U, c9_c_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargout, 2U, c9_c_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_waypoint, 3U, c9_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_psi, 4U, c9_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_Pned, 5U, c9_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_h, 6U, c9_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_time, 7U, c9_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_psiRef, 8U, c9_c_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_hRef, 9U, c9_c_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_XeRef, 10U, c9_c_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_YeRef, 11U, c9_c_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_waypointNumber, 12U,
    c9_c_sf_marshallOut, c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c9_wpointer, 13U,
    c9_b_sf_marshallOut, c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c9_t0, 14U,
    c9_sf_marshallOut, c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 7);
  c9_nPoints = 50.0;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 10);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 16);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c9_wpointer_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 17);
    chartInstance->c9_wpointer = 1.0;
    chartInstance->c9_wpointer_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 20);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c9_t0_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 21);
    chartInstance->c9_t0 = 0.0;
    chartInstance->c9_t0_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 28);
  c9_d_hoistedGlobal = chartInstance->c9_wpointer;
  c9_e_hoistedGlobal = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("waypoint",
    (int32_T)_SFD_INTEGER_CHECK("wpointer", c9_d_hoistedGlobal), 1, 50, 2, 0) -
    1;
  for (c9_i4 = 0; c9_i4 < 2; c9_i4++) {
    c9_x[c9_i4] = c9_Pned[c9_i4] - c9_waypoint[c9_i4 + 5 * c9_e_hoistedGlobal];
  }

  c9_y = 0.0;
  c9_scale = 2.2250738585072014E-308;
  for (c9_k = 1; c9_k < 3; c9_k++) {
    c9_b_k = c9_k;
    c9_b_x = c9_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c9_b_k), 1, 2, 1, 0) - 1];
    c9_c_x = c9_b_x;
    c9_absxk = muDoubleScalarAbs(c9_c_x);
    if (c9_absxk > c9_scale) {
      c9_t = c9_scale / c9_absxk;
      c9_y = 1.0 + c9_y * c9_t * c9_t;
      c9_scale = c9_absxk;
    } else {
      c9_t = c9_absxk / c9_scale;
      c9_y += c9_t * c9_t;
    }
  }

  c9_y = c9_scale * muDoubleScalarSqrt(c9_y);
  guard1 = FALSE;
  guard2 = FALSE;
  if (CV_EML_COND(0, 1, 0, c9_y < 0.3)) {
    c9_f_hoistedGlobal = chartInstance->c9_wpointer;
    c9_d_x = c9_h - c9_waypoint[2 + 5 * ((int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("waypoint", (int32_T)_SFD_INTEGER_CHECK(
      "wpointer", c9_f_hoistedGlobal), 1, 50, 2, 0) - 1)];
    c9_e_x = c9_d_x;
    c9_f_x = c9_e_x;
    c9_b_y = muDoubleScalarAbs(c9_f_x);
    if (CV_EML_COND(0, 1, 1, c9_b_y < 0.3)) {
      c9_g_hoistedGlobal = chartInstance->c9_wpointer;
      c9_g_x = c9_psi - c9_waypoint[3 + 5 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("waypoint", (int32_T)_SFD_INTEGER_CHECK(
        "wpointer", c9_g_hoistedGlobal), 1, 50, 2, 0) - 1)];
      c9_h_x = c9_g_x;
      c9_i_x = c9_h_x;
      c9_c_y = muDoubleScalarAbs(c9_i_x);
      if (CV_EML_COND(0, 1, 2, c9_c_y < 0.087266462599716474)) {
        CV_EML_MCDC(0, 1, 0, TRUE);
        CV_EML_IF(0, 1, 2, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 31);
        if (CV_EML_IF(0, 1, 3, chartInstance->c9_wpointer != c9_nPoints)) {
          _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 33);
          if (CV_EML_IF(0, 1, 4, chartInstance->c9_t0 == 0.0)) {
            _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 34);
            chartInstance->c9_t0 = c9_time;
          } else {
            _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 36);
            if (CV_EML_IF(0, 1, 5, c9_time - chartInstance->c9_t0 > c9_waypoint
                          [4 + 5 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK
                                    ("waypoint", (int32_T)_SFD_INTEGER_CHECK(
                    "wpointer", chartInstance->c9_wpointer), 1, 50, 2, 0) - 1)]))
            {
              _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 38);
              if (CV_EML_IF(0, 1, 6, chartInstance->c9_wpointer < c9_nPoints)) {
                _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 39);
                chartInstance->c9_wpointer++;
                _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 40);
                chartInstance->c9_t0 = 0.0;
              }
            }
          }
        }
      } else {
        guard1 = TRUE;
      }
    } else {
      guard2 = TRUE;
    }
  } else {
    guard2 = TRUE;
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 2, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 55);
  c9_hRef = c9_waypoint[2 + 5 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
    "waypoint", (int32_T)_SFD_INTEGER_CHECK("wpointer",
    chartInstance->c9_wpointer), 1, 50, 2, 0) - 1)];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 56);
  c9_psiRef = c9_waypoint[3 + 5 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
    "waypoint", (int32_T)_SFD_INTEGER_CHECK("wpointer",
    chartInstance->c9_wpointer), 1, 50, 2, 0) - 1)];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 57);
  c9_XeRef = c9_waypoint[5 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
    "waypoint", (int32_T)_SFD_INTEGER_CHECK("wpointer",
    chartInstance->c9_wpointer), 1, 50, 2, 0) - 1)];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 58);
  c9_YeRef = c9_waypoint[1 + 5 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
    "waypoint", (int32_T)_SFD_INTEGER_CHECK("wpointer",
    chartInstance->c9_wpointer), 1, 50, 2, 0) - 1)];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 59);
  c9_waypointNumber = chartInstance->c9_wpointer;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, -59);
  _SFD_SYMBOL_SCOPE_POP();
  *c9_b_psiRef = c9_psiRef;
  *c9_b_hRef = c9_hRef;
  *c9_b_XeRef = c9_XeRef;
  *c9_b_YeRef = c9_YeRef;
  *c9_b_waypointNumber = c9_waypointNumber;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c9_sfEvent);
}

static void initSimStructsc9_ARBlocks(SFc9_ARBlocksInstanceStruct *chartInstance)
{
}

static void registerMessagesc9_ARBlocks(SFc9_ARBlocksInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber)
{
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  if (!chartInstance->c9_t0_not_empty) {
    sf_mex_assign(&c9_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_b_t0, const char_T *c9_identifier)
{
  real_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_t0), &c9_thisId);
  sf_mex_destroy(&c9_b_t0);
  return c9_y;
}

static real_T c9_b_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  if (mxIsEmpty(c9_u)) {
    chartInstance->c9_t0_not_empty = FALSE;
  } else {
    chartInstance->c9_t0_not_empty = TRUE;
    sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
    c9_y = c9_d0;
  }

  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_t0;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_b_t0 = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_t0), &c9_thisId);
  sf_mex_destroy(&c9_b_t0);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  if (!chartInstance->c9_wpointer_not_empty) {
    sf_mex_assign(&c9_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_c_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_b_wpointer, const char_T *c9_identifier)
{
  real_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_wpointer),
    &c9_thisId);
  sf_mex_destroy(&c9_b_wpointer);
  return c9_y;
}

static real_T c9_d_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d1;
  if (mxIsEmpty(c9_u)) {
    chartInstance->c9_wpointer_not_empty = FALSE;
  } else {
    chartInstance->c9_wpointer_not_empty = TRUE;
    sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d1, 1, 0, 0U, 0, 0U, 0);
    c9_y = c9_d1;
  }

  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_wpointer;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_b_wpointer = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_wpointer),
    &c9_thisId);
  sf_mex_destroy(&c9_b_wpointer);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_e_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_waypointNumber, const char_T *c9_identifier)
{
  real_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_waypointNumber),
    &c9_thisId);
  sf_mex_destroy(&c9_waypointNumber);
  return c9_y;
}

static real_T c9_f_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d2;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d2, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d2;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_waypointNumber;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_waypointNumber = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_waypointNumber),
    &c9_thisId);
  sf_mex_destroy(&c9_waypointNumber);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i5;
  real_T c9_b_inData[2];
  int32_T c9_i6;
  real_T c9_u[2];
  const mxArray *c9_y = NULL;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i5 = 0; c9_i5 < 2; c9_i5++) {
    c9_b_inData[c9_i5] = (*(real_T (*)[2])c9_inData)[c9_i5];
  }

  for (c9_i6 = 0; c9_i6 < 2; c9_i6++) {
    c9_u[c9_i6] = c9_b_inData[c9_i6];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static const mxArray *c9_e_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i7;
  int32_T c9_i8;
  int32_T c9_i9;
  real_T c9_b_inData[250];
  int32_T c9_i10;
  int32_T c9_i11;
  int32_T c9_i12;
  real_T c9_u[250];
  const mxArray *c9_y = NULL;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_i7 = 0;
  for (c9_i8 = 0; c9_i8 < 50; c9_i8++) {
    for (c9_i9 = 0; c9_i9 < 5; c9_i9++) {
      c9_b_inData[c9_i9 + c9_i7] = (*(real_T (*)[250])c9_inData)[c9_i9 + c9_i7];
    }

    c9_i7 += 5;
  }

  c9_i10 = 0;
  for (c9_i11 = 0; c9_i11 < 50; c9_i11++) {
    for (c9_i12 = 0; c9_i12 < 5; c9_i12++) {
      c9_u[c9_i12 + c9_i10] = c9_b_inData[c9_i12 + c9_i10];
    }

    c9_i10 += 5;
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 5, 50), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

const mxArray *sf_c9_ARBlocks_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo;
  c9_ResolvedFunctionInfo c9_info[26];
  const mxArray *c9_m0 = NULL;
  int32_T c9_i13;
  c9_ResolvedFunctionInfo *c9_r0;
  c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  c9_info_helper(c9_info);
  sf_mex_assign(&c9_m0, sf_mex_createstruct("nameCaptureInfo", 1, 26), FALSE);
  for (c9_i13 = 0; c9_i13 < 26; c9_i13++) {
    c9_r0 = &c9_info[c9_i13];
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->context)), "context", "nameCaptureInfo",
                    c9_i13);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c9_r0->name)), "name", "nameCaptureInfo", c9_i13);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c9_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c9_i13);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->resolved)), "resolved", "nameCaptureInfo",
                    c9_i13);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c9_i13);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c9_i13);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c9_i13);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c9_i13);
  }

  sf_mex_assign(&c9_nameCaptureInfo, c9_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c9_nameCaptureInfo);
  return c9_nameCaptureInfo;
}

static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[26])
{
  c9_info[0].context = "";
  c9_info[0].name = "norm";
  c9_info[0].dominantType = "double";
  c9_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c9_info[0].fileTimeLo = 1336522094U;
  c9_info[0].fileTimeHi = 0U;
  c9_info[0].mFileTimeLo = 0U;
  c9_info[0].mFileTimeHi = 0U;
  c9_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c9_info[1].name = "eml_index_class";
  c9_info[1].dominantType = "";
  c9_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[1].fileTimeLo = 1323170578U;
  c9_info[1].fileTimeHi = 0U;
  c9_info[1].mFileTimeLo = 0U;
  c9_info[1].mFileTimeHi = 0U;
  c9_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c9_info[2].name = "eml_xnrm2";
  c9_info[2].dominantType = "double";
  c9_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c9_info[2].fileTimeLo = 1299076776U;
  c9_info[2].fileTimeHi = 0U;
  c9_info[2].mFileTimeLo = 0U;
  c9_info[2].mFileTimeHi = 0U;
  c9_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c9_info[3].name = "eml_blas_inline";
  c9_info[3].dominantType = "";
  c9_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c9_info[3].fileTimeLo = 1299076768U;
  c9_info[3].fileTimeHi = 0U;
  c9_info[3].mFileTimeLo = 0U;
  c9_info[3].mFileTimeHi = 0U;
  c9_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c9_info[4].name = "eml_index_class";
  c9_info[4].dominantType = "";
  c9_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[4].fileTimeLo = 1323170578U;
  c9_info[4].fileTimeHi = 0U;
  c9_info[4].mFileTimeLo = 0U;
  c9_info[4].mFileTimeHi = 0U;
  c9_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c9_info[5].name = "eml_refblas_xnrm2";
  c9_info[5].dominantType = "double";
  c9_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[5].fileTimeLo = 1299076784U;
  c9_info[5].fileTimeHi = 0U;
  c9_info[5].mFileTimeLo = 0U;
  c9_info[5].mFileTimeHi = 0U;
  c9_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[6].name = "realmin";
  c9_info[6].dominantType = "char";
  c9_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c9_info[6].fileTimeLo = 1307651242U;
  c9_info[6].fileTimeHi = 0U;
  c9_info[6].mFileTimeLo = 0U;
  c9_info[6].mFileTimeHi = 0U;
  c9_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c9_info[7].name = "eml_realmin";
  c9_info[7].dominantType = "char";
  c9_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c9_info[7].fileTimeLo = 1307651244U;
  c9_info[7].fileTimeHi = 0U;
  c9_info[7].mFileTimeLo = 0U;
  c9_info[7].mFileTimeHi = 0U;
  c9_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c9_info[8].name = "eml_float_model";
  c9_info[8].dominantType = "char";
  c9_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c9_info[8].fileTimeLo = 1326727996U;
  c9_info[8].fileTimeHi = 0U;
  c9_info[8].mFileTimeLo = 0U;
  c9_info[8].mFileTimeHi = 0U;
  c9_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[9].name = "eml_index_class";
  c9_info[9].dominantType = "";
  c9_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[9].fileTimeLo = 1323170578U;
  c9_info[9].fileTimeHi = 0U;
  c9_info[9].mFileTimeLo = 0U;
  c9_info[9].mFileTimeHi = 0U;
  c9_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[10].name = "eml_index_minus";
  c9_info[10].dominantType = "double";
  c9_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c9_info[10].fileTimeLo = 1286818778U;
  c9_info[10].fileTimeHi = 0U;
  c9_info[10].mFileTimeLo = 0U;
  c9_info[10].mFileTimeHi = 0U;
  c9_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c9_info[11].name = "eml_index_class";
  c9_info[11].dominantType = "";
  c9_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[11].fileTimeLo = 1323170578U;
  c9_info[11].fileTimeHi = 0U;
  c9_info[11].mFileTimeLo = 0U;
  c9_info[11].mFileTimeHi = 0U;
  c9_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[12].name = "eml_index_times";
  c9_info[12].dominantType = "coder.internal.indexInt";
  c9_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c9_info[12].fileTimeLo = 1286818780U;
  c9_info[12].fileTimeHi = 0U;
  c9_info[12].mFileTimeLo = 0U;
  c9_info[12].mFileTimeHi = 0U;
  c9_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c9_info[13].name = "eml_index_class";
  c9_info[13].dominantType = "";
  c9_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[13].fileTimeLo = 1323170578U;
  c9_info[13].fileTimeHi = 0U;
  c9_info[13].mFileTimeLo = 0U;
  c9_info[13].mFileTimeHi = 0U;
  c9_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[14].name = "eml_index_plus";
  c9_info[14].dominantType = "coder.internal.indexInt";
  c9_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c9_info[14].fileTimeLo = 1286818778U;
  c9_info[14].fileTimeHi = 0U;
  c9_info[14].mFileTimeLo = 0U;
  c9_info[14].mFileTimeHi = 0U;
  c9_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c9_info[15].name = "eml_index_class";
  c9_info[15].dominantType = "";
  c9_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[15].fileTimeLo = 1323170578U;
  c9_info[15].fileTimeHi = 0U;
  c9_info[15].mFileTimeLo = 0U;
  c9_info[15].mFileTimeHi = 0U;
  c9_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[16].name = "eml_int_forloop_overflow_check";
  c9_info[16].dominantType = "";
  c9_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c9_info[16].fileTimeLo = 1346510340U;
  c9_info[16].fileTimeHi = 0U;
  c9_info[16].mFileTimeLo = 0U;
  c9_info[16].mFileTimeHi = 0U;
  c9_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c9_info[17].name = "intmax";
  c9_info[17].dominantType = "char";
  c9_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c9_info[17].fileTimeLo = 1311255316U;
  c9_info[17].fileTimeHi = 0U;
  c9_info[17].mFileTimeLo = 0U;
  c9_info[17].mFileTimeHi = 0U;
  c9_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c9_info[18].name = "abs";
  c9_info[18].dominantType = "double";
  c9_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c9_info[18].fileTimeLo = 1343830366U;
  c9_info[18].fileTimeHi = 0U;
  c9_info[18].mFileTimeLo = 0U;
  c9_info[18].mFileTimeHi = 0U;
  c9_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c9_info[19].name = "eml_scalar_abs";
  c9_info[19].dominantType = "double";
  c9_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c9_info[19].fileTimeLo = 1286818712U;
  c9_info[19].fileTimeHi = 0U;
  c9_info[19].mFileTimeLo = 0U;
  c9_info[19].mFileTimeHi = 0U;
  c9_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c9_info[20].name = "abs";
  c9_info[20].dominantType = "double";
  c9_info[20].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c9_info[20].fileTimeLo = 1343830366U;
  c9_info[20].fileTimeHi = 0U;
  c9_info[20].mFileTimeLo = 0U;
  c9_info[20].mFileTimeHi = 0U;
  c9_info[21].context = "";
  c9_info[21].name = "mtimes";
  c9_info[21].dominantType = "double";
  c9_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[21].fileTimeLo = 1289519692U;
  c9_info[21].fileTimeHi = 0U;
  c9_info[21].mFileTimeLo = 0U;
  c9_info[21].mFileTimeHi = 0U;
  c9_info[22].context = "";
  c9_info[22].name = "mrdivide";
  c9_info[22].dominantType = "double";
  c9_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c9_info[22].fileTimeLo = 1357951548U;
  c9_info[22].fileTimeHi = 0U;
  c9_info[22].mFileTimeLo = 1319729966U;
  c9_info[22].mFileTimeHi = 0U;
  c9_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c9_info[23].name = "rdivide";
  c9_info[23].dominantType = "double";
  c9_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[23].fileTimeLo = 1346510388U;
  c9_info[23].fileTimeHi = 0U;
  c9_info[23].mFileTimeLo = 0U;
  c9_info[23].mFileTimeHi = 0U;
  c9_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[24].name = "eml_scalexp_compatible";
  c9_info[24].dominantType = "double";
  c9_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c9_info[24].fileTimeLo = 1286818796U;
  c9_info[24].fileTimeHi = 0U;
  c9_info[24].mFileTimeLo = 0U;
  c9_info[24].mFileTimeHi = 0U;
  c9_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[25].name = "eml_div";
  c9_info[25].dominantType = "double";
  c9_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c9_info[25].fileTimeLo = 1313347810U;
  c9_info[25].fileTimeHi = 0U;
  c9_info[25].mFileTimeLo = 0U;
  c9_info[25].mFileTimeHi = 0U;
}

static const mxArray *c9_f_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static int32_T c9_g_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i14;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i14, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i14;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)chartInstanceVoid;
  c9_b_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_sfEvent),
    &c9_thisId);
  sf_mex_destroy(&c9_b_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static uint8_T c9_h_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_b_is_active_c9_ARBlocks, const char_T *c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_b_is_active_c9_ARBlocks), &c9_thisId);
  sf_mex_destroy(&c9_b_is_active_c9_ARBlocks);
  return c9_y;
}

static uint8_T c9_i_emlrt_marshallIn(SFc9_ARBlocksInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void init_dsm_address_info(SFc9_ARBlocksInstanceStruct *chartInstance)
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

void sf_c9_ARBlocks_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2164988162U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3600427683U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1730584148U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(304208633U);
}

mxArray *sf_c9_ARBlocks_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("RSHwbXMzwFWSDt4Y8KqiaH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(50);
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
      pr[0] = (double)(2);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c9_ARBlocks_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c9_ARBlocks(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[14],T\"XeRef\",},{M[1],M[15],T\"YeRef\",},{M[1],M[11],T\"hRef\",},{M[1],M[10],T\"psiRef\",},{M[1],M[20],T\"waypointNumber\",},{M[4],M[0],T\"t0\",S'l','i','p'{{M1x2[401 403],M[0],}}},{M[4],M[0],T\"wpointer\",S'l','i','p'{{M1x2[304 312],M[0],}}},{M[8],M[0],T\"is_active_c9_ARBlocks\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_ARBlocks_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_ARBlocksInstanceStruct *chartInstance;
    chartInstance = (SFc9_ARBlocksInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ARBlocksMachineNumber_,
           9,
           1,
           1,
           10,
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
          _SFD_SET_DATA_PROPS(0,2,0,1,"psiRef");
          _SFD_SET_DATA_PROPS(1,2,0,1,"hRef");
          _SFD_SET_DATA_PROPS(2,1,1,0,"waypoint");
          _SFD_SET_DATA_PROPS(3,1,1,0,"psi");
          _SFD_SET_DATA_PROPS(4,1,1,0,"Pned");
          _SFD_SET_DATA_PROPS(5,1,1,0,"h");
          _SFD_SET_DATA_PROPS(6,2,0,1,"XeRef");
          _SFD_SET_DATA_PROPS(7,2,0,1,"YeRef");
          _SFD_SET_DATA_PROPS(8,1,1,0,"time");
          _SFD_SET_DATA_PROPS(9,2,0,1,"waypointNumber");
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
        _SFD_CV_INIT_EML(0,1,1,7,0,0,0,0,0,3,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1439);
        _SFD_CV_INIT_EML_IF(0,1,0,436,456,-1,478);
        _SFD_CV_INIT_EML_IF(0,1,1,480,494,-1,510);
        _SFD_CV_INIT_EML_IF(0,1,2,705,861,-1,1262);
        _SFD_CV_INIT_EML_IF(0,1,3,875,898,-1,1240);
        _SFD_CV_INIT_EML_IF(0,1,4,916,927,959,1209);
        _SFD_CV_INIT_EML_IF(0,1,5,976,1014,-1,1197);
        _SFD_CV_INIT_EML_IF(0,1,6,1049,1071,-1,1164);

        {
          static int condStart[] = { 710, 775, 817 };

          static int condEnd[] = { 759, 812, 861 };

          static int pfixExpr[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,710,861,3,0,&(condStart[0]),&(condEnd[0]),
                                5,&(pfixExpr[0]));
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
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)c9_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)c9_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 50;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)c9_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)c9_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)c9_c_sf_marshallIn);

        {
          real_T *c9_psiRef;
          real_T *c9_hRef;
          real_T *c9_psi;
          real_T *c9_h;
          real_T *c9_XeRef;
          real_T *c9_YeRef;
          real_T *c9_time;
          real_T *c9_waypointNumber;
          real_T (*c9_waypoint)[250];
          real_T (*c9_Pned)[2];
          c9_waypointNumber = (real_T *)ssGetOutputPortSignal(chartInstance->S,
            5);
          c9_time = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c9_YeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c9_XeRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c9_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c9_Pned = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
          c9_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c9_waypoint = (real_T (*)[250])ssGetInputPortSignal(chartInstance->S,
            0);
          c9_hRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c9_psiRef = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c9_psiRef);
          _SFD_SET_DATA_VALUE_PTR(1U, c9_hRef);
          _SFD_SET_DATA_VALUE_PTR(2U, *c9_waypoint);
          _SFD_SET_DATA_VALUE_PTR(3U, c9_psi);
          _SFD_SET_DATA_VALUE_PTR(4U, *c9_Pned);
          _SFD_SET_DATA_VALUE_PTR(5U, c9_h);
          _SFD_SET_DATA_VALUE_PTR(6U, c9_XeRef);
          _SFD_SET_DATA_VALUE_PTR(7U, c9_YeRef);
          _SFD_SET_DATA_VALUE_PTR(8U, c9_time);
          _SFD_SET_DATA_VALUE_PTR(9U, c9_waypointNumber);
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
  return "jB85aeS841k8sV862S25fF";
}

static void sf_opaque_initialize_c9_ARBlocks(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc9_ARBlocksInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*) chartInstanceVar);
  initialize_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c9_ARBlocks(void *chartInstanceVar)
{
  enable_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c9_ARBlocks(void *chartInstanceVar)
{
  disable_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c9_ARBlocks(void *chartInstanceVar)
{
  sf_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_ARBlocks(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_ARBlocks();/* state var info */
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

extern void sf_internal_set_sim_state_c9_ARBlocks(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_ARBlocks();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_ARBlocks(SimStruct* S)
{
  return sf_internal_get_sim_state_c9_ARBlocks(S);
}

static void sf_opaque_set_sim_state_c9_ARBlocks(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c9_ARBlocks(S, st);
}

static void sf_opaque_terminate_c9_ARBlocks(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_ARBlocksInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ARBlocks_optimization_info();
    }

    finalize_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_ARBlocks((SFc9_ARBlocksInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_ARBlocks(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c9_ARBlocks((SFc9_ARBlocksInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c9_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ARBlocks_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,9,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,9,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,9);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,9,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,9,5);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=5; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3623788708U));
  ssSetChecksum1(S,(3420202032U));
  ssSetChecksum2(S,(1256665259U));
  ssSetChecksum3(S,(834598304U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c9_ARBlocks(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_ARBlocks(SimStruct *S)
{
  SFc9_ARBlocksInstanceStruct *chartInstance;
  chartInstance = (SFc9_ARBlocksInstanceStruct *)utMalloc(sizeof
    (SFc9_ARBlocksInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc9_ARBlocksInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c9_ARBlocks;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c9_ARBlocks;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c9_ARBlocks;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c9_ARBlocks;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c9_ARBlocks;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c9_ARBlocks;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c9_ARBlocks;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c9_ARBlocks;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_ARBlocks;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_ARBlocks;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c9_ARBlocks;
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

void c9_ARBlocks_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_ARBlocks(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_ARBlocks(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_ARBlocks(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_ARBlocks_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
