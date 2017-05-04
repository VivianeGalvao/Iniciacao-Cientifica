############################################################################
#
# Miele and Cantrell problem
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
    (exp(x[1])-x[2])^4+100*(x[2]-x[3])^6+(tan(x[3]-x[4]))^4+x[1]^8;

subject to bounds {i in 1..4}:
    -1 <= x[i] <= 1;
    
#printf "Global minimizer at (0,1,1,1) with fx=0\n";
