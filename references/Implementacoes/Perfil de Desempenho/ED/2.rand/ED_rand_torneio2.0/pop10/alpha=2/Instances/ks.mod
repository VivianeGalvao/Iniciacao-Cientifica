############################################################################
#
# Authors choice problem - f_3(x)
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
    abs(x[1])+abs(x[1]-1)-1;

subject to bounds {i in 1..n}:
    -2 <= x[i] <= 2;

#printf "A global minimizer at -2 with fx=0\n";
