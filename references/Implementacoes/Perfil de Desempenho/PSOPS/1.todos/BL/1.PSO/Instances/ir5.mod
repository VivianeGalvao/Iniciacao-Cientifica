############################################################################
#
# Ingber and Rosen f5 test problem
# as described in
#   L. Ingber and B. Rosen, "Genetic algorithms and very fast simulated
#   reannealing: a comparison", Mathematical and Computer Modelling 16(11) 1992, 87-100.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 28 September 2005
############################################################################

# parameters
param n := 2;
param m := 25;
param a{1..n,1..m};

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    1/(500+sum {j in 1..m} (1/(j+sum {i in 1..n} ((x[i]-a[i,j])^6))));

subject to bounds {i in 1..n}:
    -65.536 <= x[i] <= 65.536;

data;

param a(tr): 1 2 :=
1   -32 -32
2   -16 -32
3   0   -32
4   16  -32
5   32  -32
6   -32 -16
7   -16 -16
8   0   -16
9   16  -16
10  32  -16
11  -32 0
12  -16 0
13  0   0
14  16  0
15  32  0
16  -32 16
17  -16 16
18  0   16
19  16  16
20  32  16
21  -32 32
22  -16 32
23  0   32
24  16  32
25  32  32;
    
#printf "Unknown global minima\n";
