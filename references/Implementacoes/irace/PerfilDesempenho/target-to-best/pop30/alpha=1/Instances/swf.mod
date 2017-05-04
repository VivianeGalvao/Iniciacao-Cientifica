############################################################################
#
# Schwefel problem
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
param n := 10;

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    -sum {i in 1..n} (x[i]*sin(sqrt(abs(x[i])+0.000001)));

subject to bounds {i in 1..n}:
    -500 <= x[i] <= 500;


#printf "Global minimizer at (%.4f, ..., %.4f) with fx=%.4f\n", 420.97, 420.97, -418.9829*n;
