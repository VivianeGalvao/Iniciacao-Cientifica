############################################################################
#
# Hosaki problem
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
    (1-8*x[1]+7*x[1]^2-7/3*x[1]^3+0.25*x[1]^4)*x[2]^2*exp(-x[2]);

subject to bound1:
    0 <= x[1] <= 5;
    
subject to bound2:
    0 <= x[2] <= 6;

#printf "Global minimizer at (4,2) with fx=-2.3458\n";
