############################################################################
#
# Levy and Montalvo 2 problem
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

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    0.1*(10*sin(3*pi*x[1])^2+ (sum {i in 1..n-1} ((x[i]-1)^2*(1+sin(3*pi*x[i+1])^2)))+(x[n]-1)^2*(1+sin(2*pi*x[n])));

subject to bounds {i in 1..n}:
    -5 <= x[i] <= 5;


#printf "Global minimizer at (1,1, ...,1) with fx=0\n";
