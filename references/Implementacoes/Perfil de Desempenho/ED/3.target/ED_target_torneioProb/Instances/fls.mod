############################################################################
#
# Floudas problem - f_17(x)
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
    cos(x[1])*sin(x[2])-x[1]/(x[2]^2+1);

subject to bound1:
    -1 <= x[1] <= 2;
    
subject to bound2:
    -1 <= x[2] <= 1;

#printf "A global minimizers at (1.9999,0.1054) with fx=-2.02181\n";
