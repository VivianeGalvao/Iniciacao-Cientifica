############################################################################
#
# Branin problem
# as described in
#   M.M.  Ali,  C.  Khompatraporn  and  Z.B.  Zabinsky,   "A numerical
#   evaluation of several stochastic algorithms on selected continuous
#   global optimization test problems", Journal of Global Optimization
#   (2005) 31:635-672
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 14 September 2005
############################################################################

# parameters
param pi := 4*atan(1);
param a := 1;
param b := 5.1/(4*pi^2);
param c := 5/pi;
param d := 6;
param g := 10;
param h := 1/(8*pi);

# variables
var x{1..2};

# objective function, minimization problem
minimize fx:
    a*(x[2]-b*x[1]^2+c*x[1]-d)^2+g*(1-h)*cos(x[1])+g;

subject to bound1:
    -5 <= x[1] <= 10;

subject to bound2:
    0 <= x[2] <= 15;

#printf "Three global minima at (%f,12.275), (%f, 2.475), (%f,2.475) with fx=%f\n", -pi, pi, 3*pi, 5/(4*pi);
