//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_pass_primitive_api.h
//
// Code generation for function 'pass_primitive'
//

#ifndef _CODER_PASS_PRIMITIVE_API_H
#define _CODER_PASS_PRIMITIVE_API_H

// Include files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void pass_primitive(real_T v0, real_T a0, real_T sf, real_T vfmin, real_T vfmax,
                    real_T Tmin, real_T Tmax, real_T coeffsT2[6], real_T *v2,
                    real_T *T2, real_T coeffsT1[6], real_T *v1, real_T *T1);

void pass_primitive_api(const mxArray *const prhs[7], int32_T nlhs,
                        const mxArray *plhs[6]);

void pass_primitive_atexit();

void pass_primitive_initialize();

void pass_primitive_terminate();

void pass_primitive_xil_shutdown();

void pass_primitive_xil_terminate();

#endif
// End of code generation (_coder_pass_primitive_api.h)
