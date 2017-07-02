############################################################################
#
# Zakharov problem
# as described in
#   A.-R. Hedar and M. Fukushima, "Heuristic pattern search and its
#   hybridization with simulated annealing for nonlinear global optimization",
#   Optimization Methods and Software, vol 19, n3-4, 291-308, 2004.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 01 October 2005
############################################################################

#parameters
param n:=10;

# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    sum {j in 1..n} (x[j]^2)+(sum {j in 1..n} (0.5*j*x[j]))^2+(sum {j in 1..n} (0.5*j*x[j]))^4;

subject to bounds {i in 1..n}:
    -5 <= x[i] <= 10;

#printf "Global minimizer at origin with fx=0\n";
