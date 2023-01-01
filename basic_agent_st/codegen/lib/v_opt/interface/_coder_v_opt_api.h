//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_v_opt_api.h
//
// Code generation for function 'v_opt'
//

#ifndef _CODER_V_OPT_API_H
#define _CODER_V_OPT_API_H

// Include files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
real_T v_opt(real_T t, real_T v0, real_T a0, real_T sf, real_T vf, real_T af,
             real_T T);

void v_opt_api(const mxArray *const prhs[7], const mxArray **plhs);

void v_opt_atexit();

void v_opt_initialize();

void v_opt_terminate();

void v_opt_xil_shutdown();

void v_opt_xil_terminate();

#endif
// End of code generation (_coder_v_opt_api.h)
