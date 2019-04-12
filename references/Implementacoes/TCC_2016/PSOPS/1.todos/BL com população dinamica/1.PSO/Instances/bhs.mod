############################################################################
#
# Batyshev, Himmelblau, Suharev problem - f_15(x)
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

# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    -(1+8*x[1]-7*x[1]^2+7*x[1]^3/3-x[1]^4/4)*x[2]^2*exp(-x[2]);

subject to bound1:
    0 <= x[1] <= 4.2;
    
subject to bound2:
    0 <= x[2] <= 6.4;

#printf "Two global minimizers at (3.83,1.70) with fx=-3.29\n";
