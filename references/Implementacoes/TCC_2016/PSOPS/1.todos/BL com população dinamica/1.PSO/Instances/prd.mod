############################################################################
#
# Periodic problem
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
    1+sin(x[1])^2+sin(x[2])^2-0.1*exp(-x[1]^2-x[2]^2);

subject to bounds {i in 1..2}:
    -10 <= x[i] <= 10;


#printf "Global minimizer at (0,0) with fx=0.9\n";
