############################################################################
#
# Bohachevsky 1 problem
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

# parameters
param pi := 4*atan(1);

# variables
var x{1..2};

# objective function, minimization problem
minimize fx:
    x[1]^2+2*x[2]^2-0.3*cos(3*pi*x[1])-0.4*cos(4*pi*x[2])+0.7;

subject to bounds {i in 1..2}:
    -50 <= x[i] <= 50;

#printf "Unknown number of local minima and a global minima at the origin with fx=0\n";
