############################################################################
#
# Salomon problem
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
param n  := 5;
param pi := 4*atan(1);

# variables
var x{1..n};
var norm_x = sqrt(sum {i in 1..n}(x[i]^2)+1e-20);


# objective function, minimization problem
minimize fx:
    1-cos(2*pi*norm_x)+0.1*norm_x;

subject to bounds {i in 1..n}:
    -100 <= x[i] <= 100;


#printf "Global minimizer at (0,0, ...,0) with fx=0\n";
