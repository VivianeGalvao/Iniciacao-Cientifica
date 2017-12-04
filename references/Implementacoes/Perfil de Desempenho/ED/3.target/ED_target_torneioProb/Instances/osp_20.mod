############################################################################
#
# Odd Square problem
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
param n := 20;
param pi := 4*atan(1);
param b {1..n};

# variables
var x{1..n};
var d = sqrt(sum {i in 1..n} ((x[i]-b[i])^2));
var D = sqrt(n)*(max {i in 1..n} (abs(x[i]-b[i])));

# objective function, minimization problem
minimize fx:
    -(1.0+0.2*d/(D+0.1))*cos(D*pi)*exp(-D/2*pi);

subject to bounds {i in 1..n}:
    -15 <= x[i] <= 15;

data;

param b :=
1   1
2   1.3
3   0.8
4   -0.4
5   -1.3
6   1.6
7   -2
8   -6
9   0.5
10  1.4
11  1
12  1.3
13  0.8 
14  -4
15  -1.3
16  1.6
17  -0.2
18  -0.6
19  0.5
20  1.4; 


#printf "Global minimizer at ~\n";
#printf "(";
#printf {i in 1..n-1}: "%.1f,", b[i];
#printf "%.1f)\nwith fx=-1.143833\n", b[n];
