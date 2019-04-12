############################################################################
#
# Suharev problem - f_13(x)
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
    x[1]^4+4*x[1]^3+4*x[1]^2+x[2]^2;

subject to bound1:
    -3 <= x[1] <= 1;
    
subject to bound2:
    -2 <= x[2] <= 2;

#printf "Two global minimizers at (0,0), (-2,0) with fx=0\n";
