function out1 = final_opt_time_pass(v0,a0,sf,vf)
%FINAL_OPT_TIME_PASS
%    OUT1 = FINAL_OPT_TIME_PASS(V0,A0,SF,VF)

%    This function was generated by the Symbolic Math Toolbox version 9.2.
%    30-Dec-2022 19:00:01

out1 = (sf.*3.0e+1)./(v0.*7.0+vf.*8.0+sqrt(a0.*sf.*6.0e+1+v0.*vf.*1.12e+2+v0.^2.*4.9e+1+vf.^2.*6.4e+1));