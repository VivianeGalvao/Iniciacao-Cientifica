############################################################################
#
# Griewank problem
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
param n := 10;
param pi := 4*atan(1);

# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    1+1/4000*(sum {i in 1..n} (x[i]^2))-prod {i in 1..n} (cos(x[i]/sqrt(i)));

subject to bounds {i in 1..n}:
    -600 <= x[i] <= 600;
    
#printf "Global minima at the origin with fx=0\n";
