############################################################################
#
# Schaffer 1 problem
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
    0.5+((sin(sqrt(x[1]^2+x[2]^2 + 1e-20)))^2-0.5)/(1+0.001*(x[1]^2+x[2]^2))^2;

subject to bounds {i in 1..2}:
    -100 <= x[i] <= 100;

#printf "Global minimizer at (0,0) with fx=0\n";
