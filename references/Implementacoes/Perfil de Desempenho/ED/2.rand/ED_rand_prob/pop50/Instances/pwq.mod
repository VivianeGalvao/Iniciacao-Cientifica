############################################################################
#
# Powell's Quadratic problem
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
var x{1..4};


# objective function, minimization problem
minimize fx:
    (x[1]+10*x[1])^2+5*(x[3]-x[4])^2+(x[2]-2*x[3])^4+10*(x[1]-x[4])^4;

subject to bounds {i in 1..4}:
    -10 <= x[i] <= 10;


#printf "Global minimizer at (0,0,0,0) with fx=0\n";
