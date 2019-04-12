############################################################################
#
# Himmelblau problem - f_1(x)
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
    (x[1]^2-1)^2;

subject to bounds {i in 1..n}:
    -2 <= x[i] <= 2;

#printf "Two global minimizers at -1 and 1 with fx=0\n";
