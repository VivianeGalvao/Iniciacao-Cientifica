############################################################################
#
# Himmelblau problem - f_7(x)
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
    (1-x[1])^2*(x[1]+1)^4*(x[1]-2)^3*x[1];

subject to bounds {i in 1..n}:
    -2 <= x[i] <= 2;

#printf "Two global minimizers at 0.41 and 4.9 with fx=-2.27\n";
