############################################################################
#
# Dekkers and Aarts problem
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
    10^5*x[1]^2+x[2]^2-(x[1]^2+x[2]^2)^2+10^-5*(x[1]^2+x[2]^2)^4;

subject to bounds {i in 1..2}:
    -20 <= x[i] <= 20;

#printf "Origin is local minimizer. Two global minimizers at (0,15) and (0,-15)\nwith fx=-24777\n";
