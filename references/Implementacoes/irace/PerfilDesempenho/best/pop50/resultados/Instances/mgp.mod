############################################################################
#
# Multi-Gaussian problem
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
param n := 10;
param pi := 4*atan(1);
param a {1..5};
param b {1..5};
param c {1..5};
param d {1..5};

# variables
var x{1..2};

# objective function, maximization problem
maximize fx:
    sum {i in 1..5} (a[i]*exp(-((x[1]-b[i])^2+(x[2]-c[i])^2)/d[i]^2));

subject to bounds {i in 1..2}:
    -2 <= x[i] <= 2;

data;

param a :=  1   0.5 2   1.2 3   1.0 4   1.0     5   1.2;

param b :=  1   0.0 2   1.0 3   0.0 4   -0.5    5   0.0;

param c :=  1   0.0 2   0.0 3   -0.5    4   0.0 5   1.0;

param d :=  1   0.1 2   0.5 3   0.5 4   0.5 5   0.5;


#printf "Global minimizer at (-0.01356,-0.01356) with fx=1.29695\n";
