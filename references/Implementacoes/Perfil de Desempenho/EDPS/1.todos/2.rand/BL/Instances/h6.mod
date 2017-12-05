############################################################################
#
# Hartmmann 6 problem
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
param p {1..6,1..4};
param a {1..6,1..4};
param c {1..4};

# variables
var x{1..6};

# objective function, minimization problem
minimize fx:
    -sum {i in 1..4} (c[i]*exp(-(sum {j in 1..6} (a[j,i]*(x[j]-p[j,i])^2))));

subject to bounds {i in 1..6}:
    0 <= x[i] <= 1;

data;

param p(tr): 1 2 3 4 5 6 :=
1 0.1312    0.1696  0.5569  0.0124  0.8283  0.5886
2 0.2329    0.4135  0.8307  0.3736  0.1004  0.9991
3 0.2348    0.1451  0.3522  0.2883  0.3047  0.6650
4 0.4047    0.8828  0.8732  0.5743  0.1091  0.0381;

param a(tr): 1 2 3 4 5 6 :=
1 10    3   17    3.5 1.7 8
2 0.05  10  17    0.1 8   14
3 3     3.5 1.7   10  17  8
4 17    8   0.05  10  0.1 14;

param c :=
1   1
2   1.2
3   3
4   3.2;

#printf "Four local minima and a global minimizer at\n";
#printf "(0.201690, 0.150011, 0.476874, 0.275332, 0.311652, 0.657301)\nwith fx=-3.322368\n";
