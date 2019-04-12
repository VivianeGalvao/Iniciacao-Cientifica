############################################################################
#
# Meyer and Roth problem
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
param t {1..5};
param v {1..5};
param y {1..5};

# variables
var x{1..3};

# objective function, minimization problem
minimize fx:
    sum {i in 1..5} (if x[1]*t[i]+x[2]*v[i]==-1 then y[i]^2 else ((x[1]*x[3]*t[i])/(1+x[1]*t[i]+x[2]*v[i])-y[i])^2);

subject to bounds {i in 1..3}:
    -10 <= x[i] <= 10;

#let x[1] := 3.13;    # reported global solution as initial guess
#let x[2] := 15.16;   # This is not the global solution
#let x[3] := 0.78;

data;

param t :=  1   1.0 2   2.0 3   1.0 4   2.0 5   0.1;

param v :=  1   1.0 2   1.0 3   2.0 4   2.0 5   0.0;  

param y :=  1   0.126   2   0.219   3   0.076   4   0.126   5   0.186;

#printf "Least squares problem with a global minima of 0.4e-4 located at (3.13,15.16,0.78)\n";
#printf "This is not the global solution !!!\n";
