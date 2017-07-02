############################################################################
#
# Suharev, Zilinskas - f_10(x)
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
    -sum {i in 1..5} (i*sin((i+1)*x[1]+i));

subject to bounds {i in 1..n}:
    -10 <= x[i] <= 10;

# reported, but not the global one !!
#printf "A global minimizer at -8.02 with fx=-9.47\n";
