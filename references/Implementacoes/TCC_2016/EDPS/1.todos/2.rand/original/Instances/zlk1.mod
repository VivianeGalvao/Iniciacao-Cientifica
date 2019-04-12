############################################################################
#
# Zilinskas problem - f_8(x)
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
    sin(x[1])+sin(2*x[1]/3);

subject to bounds {i in 1..n}:
    3.1 <= x[i] <= 20.4;

#printf "A global minimizer at 17.09 with fx=-1.91\n";
