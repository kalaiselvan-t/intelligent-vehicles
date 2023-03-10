//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// primitives.cpp
//
// Code generation for function 'primitives'
//

// Include files
#include "primitives.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

double j_opt(double t, double v0, double a0, double sf, double vf, double af,
             double T)
{
  double b_out1_tmp;
  double out1_tmp;
  double t2;
  double t3;
  double t4;
  double t4_tmp;
  // J_OPT
  //     OUT1 = J_OPT(t,V0,A0,SF,VF,AF,T)
  //     This function was generated by the Symbolic Math Toolbox version 9.2.
  //     10-Dec-2022 17:23:14
  t2 = T * T;
  t3 = af * t2;
  t4_tmp = a0 * t2;
  t4 = t4_tmp * 3.0;
  out1_tmp = T * v0;
  b_out1_tmp = T * vf;
  return (1.0 / rt_powd_snf(T, 3.0) *
              ((((sf * -20.0 + t4) - t3) + out1_tmp * 12.0) +
               b_out1_tmp * 8.0) *
              -3.0 -
          1.0 / rt_powd_snf(T, 5.0) * (t * t) *
              ((((sf * -12.0 - t3) + out1_tmp * 6.0) + b_out1_tmp * 6.0) +
               t4_tmp) *
              30.0) +
         t / (t2 * t2) *
             ((((sf * -30.0 - t3 * 2.0) + t4) + out1_tmp * 16.0) +
              b_out1_tmp * 14.0) *
             12.0;
}

void pass_primitive(double v0, double a0, double sf, double vfmin, double vfmax,
                    double Tmin, double Tmax, double coeffsT2[6], double *v2,
                    double *T2, double coeffsT1[6], double *v1, double *T1)
{
  double Tstar;
  double Tvmax;
  double vfminStar;
  //
  //            Agent Logic
  //          Pass Primitive
  //               2022
  //
  if (a0 >= 0.0) {
    // FINAL_OPT_TIME_PASS
    //     OUT1 = FINAL_OPT_TIME_PASS(V0,A0,SF,VF)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    vfminStar = a0 * sf * 60.0;
    Tstar = v0 * v0 * 49.0;
    Tvmax = sf * 30.0 /
            ((v0 * 7.0 + vfmax * 8.0) +
             std::sqrt(((vfminStar + v0 * vfmax * 112.0) + Tstar) +
                       vfmax * vfmax * 64.0));
    // FINAL_OPT_TIME_PASS
    //     OUT1 = FINAL_OPT_TIME_PASS(V0,A0,SF,VF)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    Tstar = sf * 30.0 /
            ((v0 * 7.0 + vfmin * 8.0) +
             std::sqrt(((vfminStar + v0 * vfmin * 112.0) + Tstar) +
                       vfmin * vfmin * 64.0));
  } else {
    // TIME_MIN_VEL
    //     OUT1 = TIME_MIN_VEL(A0,SF)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    Tstar = -(3.872983346207417 * std::sqrt(-a0 * sf)) / a0;
    // FINAL_OPT_VEL_PASS
    //     FINAL_OPT_VEL_PASS_VAR = FINAL_OPT_VEL_PASS(V0,A0,SF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    vfminStar =
        ((sf * -15.0 + Tstar * v0 * 7.0) + Tstar * Tstar * a0) * -0.125 / Tstar;
    if ((vfminStar < vfmin) && (vfminStar < vfmax)) {
      // FINAL_OPT_TIME_PASS
      //     OUT1 = FINAL_OPT_TIME_PASS(V0,A0,SF,VF)
      //     This function was generated by the Symbolic Math Toolbox
      //     version 9.2. 10-Dec-2022 17:23:16
      Tvmax =
          sf * 30.0 /
          ((v0 * 7.0 + vfmax * 8.0) +
           std::sqrt(((a0 * sf * 60.0 + v0 * vfmax * 112.0) + v0 * v0 * 49.0) +
                     vfmax * vfmax * 64.0));
      // FINAL_OPT_TIME_PASS
      //     OUT1 = FINAL_OPT_TIME_PASS(V0,A0,SF,VF)
      //     This function was generated by the Symbolic Math Toolbox
      //     version 9.2. 10-Dec-2022 17:23:16
      Tstar =
          sf * 30.0 /
          ((v0 * 7.0 + vfmin * 8.0) +
           std::sqrt(((a0 * sf * 60.0 + v0 * vfmin * 112.0) + v0 * v0 * 49.0) +
                     vfmin * vfmin * 64.0));
    } else if ((vfmin < vfminStar) && (vfminStar < vfmax)) {
      // FINAL_OPT_TIME_PASS
      //     OUT1 = FINAL_OPT_TIME_PASS(V0,A0,SF,VF)
      //     This function was generated by the Symbolic Math Toolbox
      //     version 9.2. 10-Dec-2022 17:23:16
      Tvmax =
          sf * 30.0 /
          ((v0 * 7.0 + vfmax * 8.0) +
           std::sqrt(((a0 * sf * 60.0 + v0 * vfmax * 112.0) + v0 * v0 * 49.0) +
                     vfmax * vfmax * 64.0));
    } else {
      Tvmax = 0.0;
      Tstar = 0.0;
    }
  }
  if ((Tmin == 0.0) && (Tmax == 0.0)) {
    *T1 = Tvmax;
    *T2 = Tstar;
  } else {
    *T1 = std::fmax(Tvmax, Tmin);
    *T2 = std::fmin(Tstar, Tmax);
  }
  if ((Tvmax != 0.0) && (Tvmax <= Tstar) && (*T1 <= *T2)) {
    double b_v2_tmp;
    double c_v2_tmp;
    double coeffsT1_tmp;
    double t3;
    double t4;
    double v2_tmp;
    // FINAL_OPT_VEL_PASS
    //     FINAL_OPT_VEL_PASS_VAR = FINAL_OPT_VEL_PASS(V0,A0,SF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    vfminStar = *T1 * *T1;
    Tstar = *T1 * v0;
    Tvmax = vfminStar * a0;
    *v1 = ((sf * -15.0 + Tstar * 7.0) + Tvmax) * -0.125 / *T1;
    // FINAL_OPT_VEL_PASS
    //     FINAL_OPT_VEL_PASS_VAR = FINAL_OPT_VEL_PASS(V0,A0,SF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    v2_tmp = *T2 * *T2;
    b_v2_tmp = *T2 * v0;
    c_v2_tmp = v2_tmp * a0;
    *v2 = ((sf * -15.0 + b_v2_tmp * 7.0) + c_v2_tmp) * -0.125 / *T2;
    // COEF_LIST
    //     COEF_LIST_VAR = COEF_LIST(V0,A0,SF,VF,AF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:14
    t3 = 0.0 * vfminStar;
    t4 = Tvmax * 3.0;
    coeffsT1[0] = 0.0;
    coeffsT1[1] = v0;
    coeffsT1[2] = a0;
    coeffsT1_tmp = *T1 * *v1;
    coeffsT1[3] =
        1.0 / rt_powd_snf(*T1, 3.0) *
        ((((sf * -20.0 + t4) - t3) + Tstar * 12.0) + coeffsT1_tmp * 8.0) * -3.0;
    coeffsT1[4] = 1.0 / (vfminStar * vfminStar) *
                  ((((sf * -30.0 - t3 * 2.0) + t4) + Tstar * 16.0) +
                   coeffsT1_tmp * 14.0) *
                  12.0;
    coeffsT1[5] =
        1.0 / rt_powd_snf(*T1, 5.0) *
        ((((sf * -12.0 - t3) + Tstar * 6.0) + coeffsT1_tmp * 6.0) + Tvmax) *
        -60.0;
    // COEF_LIST
    //     COEF_LIST_VAR = COEF_LIST(V0,A0,SF,VF,AF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:14
    t3 = 0.0 * v2_tmp;
    t4 = c_v2_tmp * 3.0;
    coeffsT2[0] = 0.0;
    coeffsT2[1] = v0;
    coeffsT2[2] = a0;
    vfminStar = *T2 * *v2;
    coeffsT2[3] =
        1.0 / rt_powd_snf(*T2, 3.0) *
        ((((sf * -20.0 + t4) - t3) + b_v2_tmp * 12.0) + vfminStar * 8.0) * -3.0;
    coeffsT2[4] = 1.0 / (v2_tmp * v2_tmp) *
                  ((((sf * -30.0 - t3 * 2.0) + t4) + b_v2_tmp * 16.0) +
                   vfminStar * 14.0) *
                  12.0;
    coeffsT2[5] =
        1.0 / rt_powd_snf(*T2, 5.0) *
        ((((sf * -12.0 - t3) + b_v2_tmp * 6.0) + vfminStar * 6.0) + c_v2_tmp) *
        -60.0;
  } else {
    for (int i{0}; i < 6; i++) {
      coeffsT1[i] = 0.0;
      coeffsT2[i] = 0.0;
    }
    *T1 = 0.0;
    *T2 = 0.0;
    *v1 = 0.0;
    *v2 = 0.0;
  }
}

void pass_primitive_j0(double v0, double a0, double sf, double vfmin,
                       double vfmax, double coefsj0[6], double *vfj0,
                       double *tfj0)
{
  double b_vfj0_tmp;
  double c_vfj0_tmp;
  double t2;
  double t9;
  double tfj0_list_idx_0;
  double vfj0_tmp;
  //
  //           Agent Logic
  //          Pass Primitive
  //               2022
  //
  // FINAL_OPT_TIME_J0_PASS
  //     FINAL_OPT_TIME_J0_PASS_VAR = FINAL_OPT_TIME_J0_PASS(V0,A0,SF)
  //     This function was generated by the Symbolic Math Toolbox version 9.2.
  //     10-Dec-2022 17:23:17
  t2 = v0 * 5.0;
  t9 = 2.23606797749979 * std::sqrt(a0 * sf * 8.0 + t2 * v0);
  tfj0_list_idx_0 = sf * 10.0 / (t2 + t9);
  *tfj0 = sf * 10.0 / (t2 - t9);
  // FINAL_OPT_VEL_J0_PASS
  //     FINAL_OPT_VEL_J0_PASS_VAR = FINAL_OPT_VEL_J0_PASS(V0,A0,J0,SF,AF,T)
  //     This function was generated by the Symbolic Math Toolbox version 9.2.
  //     10-Dec-2022 17:23:16
  t2 = tfj0_list_idx_0 * tfj0_list_idx_0;
  t9 = tfj0_list_idx_0 * v0;
  vfj0_tmp = t9 * 12.0;
  b_vfj0_tmp = 1.0 / rt_powd_snf(tfj0_list_idx_0, 3.0);
  c_vfj0_tmp = a0 * t2;
  *vfj0 = t2 *
          (0.0 - b_vfj0_tmp *
                     (((sf * 20.0 - vfj0_tmp) - c_vfj0_tmp * 3.0) + 0.0 * t2) *
                     3.0) *
          -0.041666666666666664;
  if ((vfmin < *vfj0) && (vfmax > *vfj0)) {
    double coefsj0_tmp;
    double t3;
    double t4;
    *tfj0 = tfj0_list_idx_0;
    // COEF_LIST
    //     COEF_LIST_VAR = COEF_LIST(V0,A0,SF,VF,AF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:14
    t3 = 0.0 * t2;
    t4 = c_vfj0_tmp * 3.0;
    coefsj0[0] = 0.0;
    coefsj0[1] = v0;
    coefsj0[2] = a0;
    coefsj0_tmp = tfj0_list_idx_0 * *vfj0;
    coefsj0[3] = b_vfj0_tmp *
                 ((((sf * -20.0 + t4) - t3) + vfj0_tmp) + coefsj0_tmp * 8.0) *
                 -3.0;
    coefsj0[4] =
        1.0 / (t2 * t2) *
        ((((sf * -30.0 - t3 * 2.0) + t4) + t9 * 16.0) + coefsj0_tmp * 14.0) *
        12.0;
    coefsj0[5] =
        1.0 / rt_powd_snf(tfj0_list_idx_0, 5.0) *
        ((((sf * -12.0 - t3) + t9 * 6.0) + coefsj0_tmp * 6.0) + c_vfj0_tmp) *
        -60.0;
  } else {
    // FINAL_OPT_VEL_J0_PASS
    //     FINAL_OPT_VEL_J0_PASS_VAR = FINAL_OPT_VEL_J0_PASS(V0,A0,J0,SF,AF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    t2 = *tfj0 * *tfj0;
    t9 = *tfj0 * v0;
    vfj0_tmp = t9 * 12.0;
    b_vfj0_tmp = 1.0 / rt_powd_snf(*tfj0, 3.0);
    c_vfj0_tmp = a0 * t2;
    *vfj0 =
        t2 *
        (0.0 - b_vfj0_tmp *
                   (((sf * 20.0 - vfj0_tmp) - c_vfj0_tmp * 3.0) + 0.0 * t2) *
                   3.0) *
        -0.041666666666666664;
    if ((vfmin < *vfj0) && (vfmax > *vfj0)) {
      double coefsj0_tmp;
      double t3;
      double t4;
      // COEF_LIST
      //     COEF_LIST_VAR = COEF_LIST(V0,A0,SF,VF,AF,T)
      //     This function was generated by the Symbolic Math Toolbox
      //     version 9.2. 10-Dec-2022 17:23:14
      t3 = 0.0 * t2;
      t4 = c_vfj0_tmp * 3.0;
      coefsj0[0] = 0.0;
      coefsj0[1] = v0;
      coefsj0[2] = a0;
      coefsj0_tmp = *tfj0 * *vfj0;
      coefsj0[3] = b_vfj0_tmp *
                   ((((sf * -20.0 + t4) - t3) + vfj0_tmp) + coefsj0_tmp * 8.0) *
                   -3.0;
      coefsj0[4] =
          1.0 / (t2 * t2) *
          ((((sf * -30.0 - t3 * 2.0) + t4) + t9 * 16.0) + coefsj0_tmp * 14.0) *
          12.0;
      coefsj0[5] =
          1.0 / rt_powd_snf(*tfj0, 5.0) *
          ((((sf * -12.0 - t3) + t9 * 6.0) + coefsj0_tmp * 6.0) + c_vfj0_tmp) *
          -60.0;
    } else {
      for (int i{0}; i < 6; i++) {
        coefsj0[i] = 0.0;
      }
      *tfj0 = 0.0;
      *vfj0 = 0.0;
    }
  }
}

void primitives_initialize()
{
}

void primitives_terminate()
{
}

double s_opt(double t, double v0, double a0, double sf, double vf, double af,
             double T)
{
  double b_out1_tmp;
  double out1_tmp;
  double t2;
  double t3;
  double t4;
  double t4_tmp;
  // S_OPT
  //     OUT1 = S_OPT(t,V0,A0,SF,VF,AF,T)
  //     This function was generated by the Symbolic Math Toolbox version 9.2.
  //     10-Dec-2022 17:23:13
  t2 = T * T;
  t3 = af * t2;
  t4_tmp = a0 * t2;
  t4 = t4_tmp * 3.0;
  out1_tmp = T * v0;
  b_out1_tmp = T * vf;
  return (((t * v0 + a0 * (t * t) / 2.0) -
           1.0 / rt_powd_snf(T, 5.0) * rt_powd_snf(t, 5.0) *
               ((((sf * -12.0 - t3) + out1_tmp * 6.0) + b_out1_tmp * 6.0) +
                t4_tmp) /
               2.0) -
          1.0 / rt_powd_snf(T, 3.0) * rt_powd_snf(t, 3.0) *
              ((((sf * -20.0 + t4) - t3) + out1_tmp * 12.0) +
               b_out1_tmp * 8.0) /
              2.0) +
         rt_powd_snf(t, 4.0) / (t2 * t2) *
             ((((sf * -30.0 - t3 * 2.0) + t4) + out1_tmp * 16.0) +
              b_out1_tmp * 14.0) /
             2.0;
}

void stop_primitive(double v0, double a0, double sf, double coefs[6],
                    double *maxsf, double *tf)
{
  //
  //           Agent Logic
  //          Stop Primitive
  //               2022
  //
  if (v0 > 0.0) {
    double coefs_tmp;
    double t2;
    double t3;
    double t4;
    double t4_tmp;
    *maxsf = sf;
    t2 = 4.0 * (v0 * v0);
    if (t2 + 5.0 * a0 * sf < 0.0) {
      *maxsf = -(t2 / (5.0 * a0));
      *tf = 5.0 * *maxsf / v0;
    } else {
      // FINAL_OPT_TIME_STOP
      //     OUT1 = FINAL_OPT_TIME_STOP(V0,A0,SF)
      //     This function was generated by the Symbolic Math Toolbox
      //     version 9.2. 10-Dec-2022 17:23:15
      *tf = sf * 10.0 / (v0 * 2.0 + std::sqrt(a0 * sf * 5.0 + t2));
    }
    // COEF_LIST
    //     COEF_LIST_VAR = COEF_LIST(V0,A0,SF,VF,AF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:14
    t2 = *tf * *tf;
    t3 = 0.0 * t2;
    t4_tmp = a0 * t2;
    t4 = t4_tmp * 3.0;
    coefs[0] = 0.0;
    coefs[1] = v0;
    coefs[2] = a0;
    coefs_tmp = *tf * v0;
    coefs[3] =
        1.0 / rt_powd_snf(*tf, 3.0) *
        ((((*maxsf * -20.0 + t4) - t3) + coefs_tmp * 12.0) + *tf * 0.0 * 8.0) *
        -3.0;
    coefs[4] = 1.0 / (t2 * t2) *
               ((((*maxsf * -30.0 - t3 * 2.0) + t4) + coefs_tmp * 16.0) +
                *tf * 0.0 * 14.0) *
               12.0;
    coefs[5] = 1.0 / rt_powd_snf(*tf, 5.0) *
               ((((*maxsf * -12.0 - t3) + coefs_tmp * 6.0) + *tf * 0.0 * 6.0) +
                t4_tmp) *
               -60.0;
  } else {
    *maxsf = 0.0;
    *tf = 0.0;
    for (int i{0}; i < 6; i++) {
      coefs[i] = 0.0;
    }
  }
}

void stop_primitive_j0(double v0, double a0, double coefsj0[6], double *sfj0,
                       double *tfj0)
{
  //
  //            Agent Logic
  //          Stop Primitive
  //               2022
  //
  if ((v0 > 0.0) && (a0 < 0.0)) {
    double b_sfj0_tmp;
    double c_sfj0_tmp;
    double d_sfj0_tmp;
    double sfj0_tmp;
    double sfj0_tmp_tmp;
    double t2_tmp;
    double t3;
    double t4;
    // FINAL_OPT_TIME_STOP_J0
    //     OUT1 = FINAL_OPT_TIME_STOP_J0(V0,A0)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    *tfj0 = v0 * -2.0 / a0;
    // FINAL_OPT_POS_J0
    //     FINAL_OPT_POS_J0_VAR = FINAL_OPT_POS_J0(V0,A0,J0,VF,AF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:16
    t2_tmp = *tfj0 * *tfj0;
    t3 = rt_powd_snf(*tfj0, 3.0);
    sfj0_tmp_tmp = *tfj0 * v0;
    sfj0_tmp = sfj0_tmp_tmp * 12.0;
    b_sfj0_tmp = *tfj0 * 0.0 * 8.0;
    c_sfj0_tmp = 1.0 / t3;
    d_sfj0_tmp = a0 * t2_tmp;
    *sfj0 =
        t3 *
        (c_sfj0_tmp *
         (((sfj0_tmp + b_sfj0_tmp) + d_sfj0_tmp * 3.0) - 0.0 * t2_tmp) * 3.0) /
        60.0;
    // COEF_LIST
    //     COEF_LIST_VAR = COEF_LIST(V0,A0,SF,VF,AF,T)
    //     This function was generated by the Symbolic Math Toolbox version 9.2.
    //     10-Dec-2022 17:23:14
    t3 = 0.0 * t2_tmp;
    t4 = d_sfj0_tmp * 3.0;
    coefsj0[0] = 0.0;
    coefsj0[1] = v0;
    coefsj0[2] = a0;
    coefsj0[3] = c_sfj0_tmp *
                 ((((*sfj0 * -20.0 + t4) - t3) + sfj0_tmp) + b_sfj0_tmp) * -3.0;
    coefsj0[4] = 1.0 / (t2_tmp * t2_tmp) *
                 ((((*sfj0 * -30.0 - t3 * 2.0) + t4) + sfj0_tmp_tmp * 16.0) +
                  *tfj0 * 0.0 * 14.0) *
                 12.0;
    coefsj0[5] =
        1.0 / rt_powd_snf(*tfj0, 5.0) *
        ((((*sfj0 * -12.0 - t3) + sfj0_tmp_tmp * 6.0) + *tfj0 * 0.0 * 6.0) +
         d_sfj0_tmp) *
        -60.0;
  } else {
    *sfj0 = 0.0;
    *tfj0 = 0.0;
    for (int i{0}; i < 6; i++) {
      coefsj0[i] = 0.0;
    }
  }
}

// End of code generation (primitives.cpp)
