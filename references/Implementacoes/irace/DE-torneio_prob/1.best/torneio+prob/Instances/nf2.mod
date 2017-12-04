############################################################################
#
# Neumaier 2 problem
# as described in
#   M.M.  Ali,  C.  Khompatraporn  and  Z.B.  Zabinsky,   "A numerical
#   evaluation of several stochastic algorithms on selected continuous
#   global optimization test problems", Journal of Global Optimization
#   (2005) 31:635-672
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 19 September 2005
############################################################################

# parameters
param n := 4;
param b {1..n};


# variables
var x{1..n};

# objective function, minimize problem
minimize fx:
    sum {k in 1..n} (b[k]- sum {i in 1..n} (x[i]^k))^2;

subject to bounds {i in 1..n}:
    0 <= x[i] <= n;


data;

param b :=  1   8   2   18  3   44  4   114;


#printf "Global minimizer at (1,2,2,3) with fx=0\n";
