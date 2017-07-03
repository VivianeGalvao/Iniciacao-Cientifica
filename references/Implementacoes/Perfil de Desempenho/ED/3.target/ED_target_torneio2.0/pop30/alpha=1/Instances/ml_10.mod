############################################################################
#
# Modified Langerman problem
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
param a {1..5,1..n};
param c {1..5};

# variables
var x{1..n};
var d{j in 1..5} = sum {i in 1..n} (x[i]-a[j,i])^2;

# objective function, minimization problem
minimize fx:
    -sum {j in 1..5} (c[j]*cos(d[j]/pi)*exp(-pi*d[j]));

subject to bounds {i in 1..n}:
    0 <= x[i] <= 10;

data;

param a: 1 2 3 4 5 6 7 8 9 10:=
1   9.681   0.667   4.783   9.095   3.517   9.325   6.544   0.211   5.122   2.020
2   9.400   2.041   3.788   7.931   2.882   2.672   3.568   1.284   7.033   7.374
3   8.025   9.152   5.114   7.621   4.564   4.711   2.996   6.126   0.734   4.982
4   2.196   0.415   5.649   6.979   9.510   9.166   6.304   6.054   9.377   1.426
5   8.074   8.777   3.467   1.867   6.708   6.349   4.534   0.276   7.633   1.567;

param c :=
1   0.806   
2   0.517
3   0.100
4   0.908
5   0.965;

#printf "Global minimizer at (8.074,8.777,3.467,1.867,6.708) with fx=-0.965\n";
