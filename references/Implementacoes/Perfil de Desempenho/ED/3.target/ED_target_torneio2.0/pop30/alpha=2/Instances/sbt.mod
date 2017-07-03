############################################################################
#
# Shubert problem
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
param n := 2;

# variables
var x{1..2};


# objective function, minimization problem
minimize fx:
    prod {i in 1..n} (sum {j in 1..5} (j*cos((j+1)*x[i]+j)));

subject to bounds {i in 1..2}:
    -10 <= x[i] <= 10;

#printf "18 Global minimizer with fx=-186.7309\n";
