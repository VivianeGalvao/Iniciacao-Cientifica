############################################################################
#
# Suharev problem - f_6(x)
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

# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    if(x[1]==0) then 1 else sin(1/x[1]);

subject to bounds {i in 1..n}:
    0 <= x[i] <= 1;

#printf "Three global minimizers at 0.058, 0.091, 0.213 with fx=-0.999\n";
