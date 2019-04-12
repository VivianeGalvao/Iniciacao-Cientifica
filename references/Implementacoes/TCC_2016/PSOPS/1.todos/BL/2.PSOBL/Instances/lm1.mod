############################################################################
#
# Levy and Montalvo 1 problem
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
param n := 3;
param pi := 4*atan(1);

# variables
var x{1..n};
var y{i in 1..n} = 1+0.25*(x[i]+1);


# objective function, minimization problem
minimize fx:
    (pi/n)*(10*sin(pi*y[1])^2+ (sum {i in 1..n-1} ((y[i]-1)^2*(1+10*sin(pi*y[i+1])^2)))+(y[n]-1)^2);

subject to bounds {i in 1..n}:
    -10 <= x[i] <= 10;


#printf "Global minimizer at (-1,-1, ...,-1) with fx=0\n";
