############################################################################
#
# Zilinskas, Zilinskas and Shaltyanis problem - f_11(x)
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
    (x[1]+sin(x[1]))*exp(-x[1]^2);

subject to bounds {i in 1..n}:
    -10 <= x[i] <= 10;

#printf "A global minimizer at -0.68 with fx=-0.82\n";
