############################################################################
#
# Aluffi-Pentini's problem
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
    0.25*x[1]^4-0.5*x[1]^2+0.1*x[1]+0.5*x[2]^2;

subject to bounds {i in 1..2}:
    -10 <= x[i] <= 10;

#printf "Two local minima, one of them is global with fx=-0.3523, located at (-1.0465,0)\n";
