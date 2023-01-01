//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// pass_primitive.h
//
// Code generation for function 'pass_primitive'
//

#ifndef PASS_PRIMITIVE_H
#define PASS_PRIMITIVE_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void pass_primitive(double v0, double a0, double sf, double vfmin,
                           double vfmax, double Tmin, double Tmax,
                           double coeffsT2[6], double *v2, double *T2,
                           double coeffsT1[6], double *v1, double *T1);

extern void pass_primitive_initialize();

extern void pass_primitive_terminate();

#endif
// End of code generation (pass_primitive.h)
