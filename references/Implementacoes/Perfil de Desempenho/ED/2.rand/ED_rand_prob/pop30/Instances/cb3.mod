############################################################################
#
# Camel Back - 3 Hump problem
# as described in
#   M.M.  Ali,  C.  Khompatraporn  and  Z.B.  Zabinsky,   "A numerical
#   evaluation of several stochastic algorithms on selected continuous
#   global optimization test problems", Journal of Global Optimization
#   (2005) 31:635-672
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 14 September 2005
############################################################################

# variables
var x{1..2};

# objective function, minimization problem
minimize fx:
    2*x[1]^2-1.05*x[1]^4+1/6*x[1]^6+x[1]*x[2]+x[2]^2;

subject to bounds {i in 1..2}:
    -5 <= x[i] <= 5;

#printf "Three local minima, one of them is global located at (0,0) with fx=0\n";
