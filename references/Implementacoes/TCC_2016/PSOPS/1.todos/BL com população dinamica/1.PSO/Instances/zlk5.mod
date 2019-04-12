############################################################################
#
# Zilinskas problem - f_19(x) (De Joung function with different bounds)
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
param n := 3;


# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    -exp(-3*(x[1]-0.3689)^2-10*(x[2]-0.117)^2-30*(x[3]-0.2673)^2)-
    1.2*exp(-0.1*(x[1]-0.4699)^2-10*(x[2]-0.4387)^2-35*(x[3]-0.747)^2)-
    3*exp(-3*(x[1]-0.1091)^2-10*(x[2]-0.8732)^2-30*(x[3]-0.5547)^2)-
    3.2*exp(-0.1*(x[1]-0.03815)^2-10*(x[2]-0.5743)^2-35*(x[3]-0.8828)^2);

subject to bounds {i in 1..n}:
    0 <= x[i] <= 1;
    

#printf "A global minimizers at (0.09,0.56,0.85) with fx=-3.86\n";
