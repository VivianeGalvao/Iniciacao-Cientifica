############################################################################
#
# Strongin problem - f_5(x)
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
    2-cos(x[1])-cos(2*x[1]);

subject to bounds {i in 1..n}:
    -1.5 <= x[i] <= 4.5;

#printf "A global minimizer at 0 with fx=0\n";
