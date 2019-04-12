############################################################################
#
# Kowalik problem
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
param a {1..11};
param b {1..11};

# variables
var x{1..4};

# objective function, minimization problem
minimize fx:
    sum {i in 1..11} ((a[i]-(x[1]*(1+x[2]*b[i]))/(1+x[3]*b[i]+x[4]*b[i]^2))^2);

subject to bounds {i in 1..4}:
    0 <= x[i] <= 0.42;

data;


param a :=
1   0.1957
2   0.1947
3   0.1735
4   0.16
5   0.0844
6   0.0627
7   0.0456
8   0.0342
9   0.0323
10  0.0235
11  0.0246;

param b :=
1   0.25
2   0.50
3   1.0
4   2.0
5   4.0
6   6.0
7   8.0
8   10.0
9   12.0
10  14.0
11  16.0;

#printf "Least squares problem with a global minima of 3.0748e-4 located at (0.192, 0.190, 0.123, 0.135)\n";
