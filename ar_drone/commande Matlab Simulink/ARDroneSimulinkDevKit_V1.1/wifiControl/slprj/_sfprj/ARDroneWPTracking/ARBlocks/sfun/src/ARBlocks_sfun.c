/* Include files */

#include "ARBlocks_sfun.h"
#include "ARBlocks_sfun_debug_macros.h"
#include "c1_ARBlocks.h"
#include "c2_ARBlocks.h"
#include "c3_ARBlocks.h"
#include "c4_ARBlocks.h"
#include "c6_ARBlocks.h"
#include "c7_ARBlocks.h"
#include "c9_ARBlocks.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _ARBlocksMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void ARBlocks_initializer(void)
{
}

void ARBlocks_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_ARBlocks_method_dispatcher(SimStruct *simstructPtr, unsigned int
  chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_ARBlocks_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_ARBlocks_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_ARBlocks_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_ARBlocks_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_ARBlocks_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_ARBlocks_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==9) {
    c9_ARBlocks_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_ARBlocks_process_testpoint_info_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char machineName[128];
  if (nrhs < 3 || !mxIsChar(prhs[0]) || !mxIsChar(prhs[1]))
    return 0;

  /* Possible call to get testpoint info. */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_testpoint_info"))
    return 0;
  mxGetString(prhs[1], machineName, sizeof(machineName)/sizeof(char));
  machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
  if (!strcmp(machineName, "ARBlocks")) {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
    switch (chartFileNumber) {
     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }

    return 1;
  }

  return 0;

#else

  return 0;

#endif

}

unsigned int sf_ARBlocks_process_check_sum_call( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>2 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"library")) {
      char machineName[100];
      mxGetString(prhs[2], machineName,sizeof(machineName)/sizeof(char));
      machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
      if (!strcmp(machineName,"ARBlocks")) {
        if (nrhs==3) {
          ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1414191184U);
          ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1308551938U);
          ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4185943651U);
          ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4200209973U);
        } else if (nrhs==4) {
          unsigned int chartFileNumber;
          chartFileNumber = (unsigned int)mxGetScalar(prhs[3]);
          switch (chartFileNumber) {
           case 1:
            {
              extern void sf_c1_ARBlocks_get_check_sum(mxArray *plhs[]);
              sf_c1_ARBlocks_get_check_sum(plhs);
              break;
            }

           case 2:
            {
              extern void sf_c2_ARBlocks_get_check_sum(mxArray *plhs[]);
              sf_c2_ARBlocks_get_check_sum(plhs);
              break;
            }

           case 3:
            {
              extern void sf_c3_ARBlocks_get_check_sum(mxArray *plhs[]);
              sf_c3_ARBlocks_get_check_sum(plhs);
              break;
            }

           case 4:
            {
              extern void sf_c4_ARBlocks_get_check_sum(mxArray *plhs[]);
              sf_c4_ARBlocks_get_check_sum(plhs);
              break;
            }

           case 6:
            {
              extern void sf_c6_ARBlocks_get_check_sum(mxArray *plhs[]);
              sf_c6_ARBlocks_get_check_sum(plhs);
              break;
            }

           case 7:
            {
              extern void sf_c7_ARBlocks_get_check_sum(mxArray *plhs[]);
              sf_c7_ARBlocks_get_check_sum(plhs);
              break;
            }

           case 9:
            {
              extern void sf_c9_ARBlocks_get_check_sum(mxArray *plhs[]);
              sf_c9_ARBlocks_get_check_sum(plhs);
              break;
            }

           default:
            ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
          }
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  } else {
    return 0;
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_ARBlocks_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "7QWtKIBzkt7jsSGFHoJkDC") == 0) {
          extern mxArray *sf_c1_ARBlocks_get_autoinheritance_info(void);
          plhs[0] = sf_c1_ARBlocks_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "hXQ3tMHDYVYgkO36bYP10B") == 0) {
          extern mxArray *sf_c2_ARBlocks_get_autoinheritance_info(void);
          plhs[0] = sf_c2_ARBlocks_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "MEuQ528xsfhgc96kOJA9RG") == 0) {
          extern mxArray *sf_c3_ARBlocks_get_autoinheritance_info(void);
          plhs[0] = sf_c3_ARBlocks_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "ZJyrVj5Pg2Ig5hWLC19MJB") == 0) {
          extern mxArray *sf_c4_ARBlocks_get_autoinheritance_info(void);
          plhs[0] = sf_c4_ARBlocks_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "5E0ZMt4gT0b9vhD6qTo22D") == 0) {
          extern mxArray *sf_c6_ARBlocks_get_autoinheritance_info(void);
          plhs[0] = sf_c6_ARBlocks_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "n3ysHM0dNoSRYcTh4b5Av") == 0) {
          extern mxArray *sf_c7_ARBlocks_get_autoinheritance_info(void);
          plhs[0] = sf_c7_ARBlocks_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 9:
      {
        if (strcmp(aiChksum, "RSHwbXMzwFWSDt4Y8KqiaH") == 0) {
          extern mxArray *sf_c9_ARBlocks_get_autoinheritance_info(void);
          plhs[0] = sf_c9_ARBlocks_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_ARBlocks_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_ARBlocks_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_ARBlocks_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_ARBlocks_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_ARBlocks_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_ARBlocks_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_ARBlocks_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_ARBlocks_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_ARBlocks_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray *sf_c6_ARBlocks_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_ARBlocks_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray *sf_c7_ARBlocks_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_ARBlocks_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 9:
      {
        extern const mxArray *sf_c9_ARBlocks_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c9_ARBlocks_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_ARBlocks_third_party_uses_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "1iQHuDZd1agg9VKAsv8VCH") == 0) {
          extern mxArray *sf_c1_ARBlocks_third_party_uses_info(void);
          plhs[0] = sf_c1_ARBlocks_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "rgIVgRGm8Ynj6sqtqIDVkE") == 0) {
          extern mxArray *sf_c2_ARBlocks_third_party_uses_info(void);
          plhs[0] = sf_c2_ARBlocks_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "EBwi7wwKh6dNpnh8BJBG9G") == 0) {
          extern mxArray *sf_c3_ARBlocks_third_party_uses_info(void);
          plhs[0] = sf_c3_ARBlocks_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "6CKhXn4ud8A3MOS9pXY3mD") == 0) {
          extern mxArray *sf_c4_ARBlocks_third_party_uses_info(void);
          plhs[0] = sf_c4_ARBlocks_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "mMZCgJvKgNjN0xJS5cBmMB") == 0) {
          extern mxArray *sf_c6_ARBlocks_third_party_uses_info(void);
          plhs[0] = sf_c6_ARBlocks_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "elDaS3BbswouiyYknRHCHH") == 0) {
          extern mxArray *sf_c7_ARBlocks_third_party_uses_info(void);
          plhs[0] = sf_c7_ARBlocks_third_party_uses_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "jB85aeS841k8sV862S25fF") == 0) {
          extern mxArray *sf_c9_ARBlocks_third_party_uses_info(void);
          plhs[0] = sf_c9_ARBlocks_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void ARBlocks_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _ARBlocksMachineNumber_ = sf_debug_initialize_machine(debugInstance,"ARBlocks",
    "sfun",1,7,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_ARBlocksMachineNumber_,0,
    0);
  sf_debug_set_machine_data_thresholds(debugInstance,_ARBlocksMachineNumber_,0);
}

void ARBlocks_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_ARBlocks_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("ARBlocks",
      "ARDroneWPTracking");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_ARBlocks_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
