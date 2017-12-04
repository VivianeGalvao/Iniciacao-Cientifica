############################################################################
#
# Shekel 10 problem
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
param a{1..n,1..4};
param c{1..n};

# variables
var x{1..4};


# objective function, minimization problem
minimize fx:
    -sum {i in 1..n} (1/(sum {j in 1..4} (x[j]-a[i,j])^2+c[i]));

subject to bounds {i in 1..4}:
    0 <= x[i] <= 10;

data;

param a: 1 2 3 4 :=
1   4   4   4   4
2   1   1   1   1
3   8   8   8   8
4   6   6   6   6
5   3   7   3   7
6   2   9   2   9
7   5   5   3   3
8   8   1   8   1
9   6   2   6   2
10  7   3.6 7   3.6;

param c :=
1   0.1
2   0.2
3   0.2
4   0.4
5   0.4
6   0.6
7   0.3
8   0.7
9   0.5
10  0.5;

#printf "Global minimizer at (4,4,4,4) with fx=-10.5319\n";
