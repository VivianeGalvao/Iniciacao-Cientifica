############################################################################
#
# Easom problem
# as described in
#   M.M.  Ali,  C.  Khompatraporn  and  Z.B.  Zabinsky,   "A numerical
#   evaluation of several stochastic algorithms on selected continuous
#   global optimization test problems", Journal of Global Optimization
#   (2005) 31:635-672
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 14 September 2005
############################################################################

# parameters
param pi := 4*atan(1);

# variables
var x{1..2};

# objective function, minimization problem
minimize fx:
    -cos(x[1])*cos(x[2])*exp(-(x[1]-pi)^2-(x[2]-pi)^2);

subject to bounds {i in 1..2}:
    -10 <= x[i] <= 10;

#printf "Minimum value at (pi,pi) with fx=-1\n";
