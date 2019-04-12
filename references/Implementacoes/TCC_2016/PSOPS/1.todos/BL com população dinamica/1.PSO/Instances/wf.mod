############################################################################
#
# Wood's problem
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
    100*(x[2]-x[1]^2)^2+(1-x[1])^2+90*(x[4]-x[3]^2)^2+(1-x[3])^2+
    10.1*((x[2]-1)^2+(x[4]-1)^2)+19.8*(x[2]-1)*(x[4]-1);

subject to bounds {i in 1..4}:
    -10 <= x[i] <= 10;


#printf "Global minimizer at (1,1,1,1) with fx=0\n";
