############################################################################
#
# Rastrigin problem
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

# parameters
param n  := 10;
param pi := 4*atan(1);

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    10*n+sum {i in 1..n} (x[i]^2-10*cos(2*pi*x[i]));

subject to bounds {i in 1..n}:
    -5.12 <= x[i] <= 5.12;

#printf "Global minimizer at (0,0, ...,0) with fx=0\n";
