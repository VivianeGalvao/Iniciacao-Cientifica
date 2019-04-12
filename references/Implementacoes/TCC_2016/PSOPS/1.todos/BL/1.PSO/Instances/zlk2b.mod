############################################################################
#
# Zilinskas problem - f_9(x)
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
param n := 1;
param pi := 4*atan(1);

# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    2*(x[1]-0.75)^2+sin(8*pi*x[1]-pi/2)-0.125;

subject to bounds {i in 1..n}:
    -2 <= x[i] <= 2;

#printf "A global minimizer at 0.75 with fx=-1.12\n";
