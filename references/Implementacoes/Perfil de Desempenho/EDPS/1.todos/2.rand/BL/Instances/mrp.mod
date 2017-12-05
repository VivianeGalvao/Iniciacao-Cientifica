############################################################################
#
# Modified Rosenbrock problem
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


# variables
var x{1..2};


# objective function, minimization problem
minimize fx:
    100*(x[2]-x[1]^2)^2+(6.4*(x[2]-0.5)^2-x[1]-0.6)^2;

subject to bounds {i in 1..2}:
    -5 <= x[i] <= 5;


#printf "Global minimizer at (0.3412, 0.1164) and (1,1) with fx=0\n";
