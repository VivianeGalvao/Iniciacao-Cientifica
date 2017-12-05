############################################################################
#
# Exponential problem
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
param n := 10;

# variables
var x{1..n};

# objective function, maximization problem
maximize fx:
    exp(-0.5*(sum {i in 1..n} (x[i]^2)));

subject to bounds {i in 1..n}:
    -1 <= x[i] <= 1;

#printf "Global minimizer at origin with fx=1\n";
