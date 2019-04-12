############################################################################
#
# Zilinskas problem - f_16(x)
# as described in
#   E. Kiseleva and T. Stepanchuk, "On the efficiency of a global
#   non-differentiable optimization algorithm based on the method of optimal
#   set partitioning", Journal of Global Optimization 25: 209-235, 2003.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 01 October 2005
############################################################################

# parameters
param n := 2;
param a:=1;
param b:=5.1/(4*3.14159^2);
param c:=5/3.14159;
param d:=6;
param l:=10;
param f:=1/(8*3.14159);

# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    a*(x[2]-b*x[1]^2+c*x[1]-d)^2+l*(1-f)*cos(x[1])+l;

subject to bound1:
    -5 <= x[1] <= 10;
    
subject to bound2:
    0 <= x[2] <= 15;

#printf "A global minimizers at (9.42,2.47) with fx=0.4\n";
