############################################################################
#
# McCormick problem
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
    sin(x[1]+x[2])+(x[1]-x[2])^2-1.5*x[1]+2.5*x[2]+1;

subject to bound1:
    -1.5 <= x[1] <= 4;
    
subject to bound2:
    -3 <= x[2] <= 3;

#printf "Global minimizer at (-0.547, -1.547) with fx=-1.9133\n";
