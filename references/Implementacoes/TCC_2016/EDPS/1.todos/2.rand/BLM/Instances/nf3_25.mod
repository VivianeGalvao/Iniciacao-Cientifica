############################################################################
#
# Neumaier 3 problem
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
param n := 25;

# variables
var x{1..n};

# objective function, minimize problem
minimize fx:
    sum {i in 1..n} (x[i]-1)^2 - sum {i in 2..n} (x[i]*x[i-1]) ;

subject to bounds {i in 1..n}:
    -n^2 <= x[i] <= n^2;



#printf "Global minimizer at\n";
#printf "(";
#printf {i in 1..n-1}: "%.1f,", i*(n+1-i);
#printf "%.1f)\nwith fx=%.1f\n", n*(n+1-n), -n*(n+4)*(n-1)/6;
