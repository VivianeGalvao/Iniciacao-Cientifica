############################################################################
#
# Hartmmann 3 problem
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
param p {1..3,1..4};
param a {1..3,1..4};
param c {1..4};

# variables
var x{1..3};

# objective function, minimization problem
minimize fx:
    -sum {i in 1..4} (c[i]*exp(-(sum {j in 1..3} (a[j,i]*(x[j]-p[j,i])^2))));

subject to bounds {i in 1..3}:
    0 <= x[i] <= 1;

data;

param p(tr): 1 2 3 :=
1 0.3689    0.117   0.2673
2 0.4699    0.4387  0.747
3 0.1091    0.8732  0.5547
4 0.03815   0.5743  0.8828;

param a(tr): 1 2 3 :=
1 3     10  30
2 0.1   10  35
3 3     10  30
4 0.1   10  35;

param c :=
1   1
2   1.2
3   3
4   3.2;

#printf "Four local minima and a global minimizer at (0.114614, 0.555649, 0.852547)\n";
#printf "with fx=-3.862782\n";
