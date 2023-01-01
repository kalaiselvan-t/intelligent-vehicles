//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// v_opt.h
//
// Code generation for function 'v_opt'
//

#ifndef V_OPT_H
#define V_OPT_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern double v_opt(double t, double v0, double a0, double sf, double vf,
                    double af, double T);

extern void v_opt_initialize();

extern void v_opt_terminate();

#endif
// End of code generation (v_opt.h)
