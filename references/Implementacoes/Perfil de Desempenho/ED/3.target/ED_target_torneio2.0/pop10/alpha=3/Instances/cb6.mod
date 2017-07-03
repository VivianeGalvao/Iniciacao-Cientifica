############################################################################
#
# Camel Back - 6 Hump problem
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
    4*x[1]^2-2.1*x[1]^4+1/3*x[1]^6+x[1]*x[2]-4*x[2]^2+4*x[2]^4;

subject to bounds {i in 1..2}:
    -5 <= x[i] <= 5;

#printf "This function is symmetric about the origin and has three conjugate pairs\n";
#printf "of local minima with fx=-1.0316,-0.2154,2.1042. Two global minima at\n";
#printf "(0.089842,-0.712656) and (-0.089842,0.712656) with fx=-1.0316\n";
