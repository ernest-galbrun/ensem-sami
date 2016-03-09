#ifndef __c3_ARBlocks_h__
#define __c3_ARBlocks_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc3_ARBlocksInstanceStruct
#define typedef_SFc3_ARBlocksInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_ARBlocks;
  uint8_T c3_frame[496];
  boolean_T c3_frame_not_empty;
  uint8_T c3_lastFrame[496];
  boolean_T c3_lastFrame_not_empty;
  real_T c3_count;
  boolean_T c3_count_not_empty;
  real_T c3_countHeader;
  boolean_T c3_countHeader_not_empty;
  real_T c3_countBuffer;
  boolean_T c3_countBuffer_not_empty;
  uint8_T c3_buffer[1024];
  boolean_T c3_buffer_not_empty;
} SFc3_ARBlocksInstanceStruct;

#endif                                 /*typedef_SFc3_ARBlocksInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_ARBlocks_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_ARBlocks_get_check_sum(mxArray *plhs[]);
extern void c3_ARBlocks_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
