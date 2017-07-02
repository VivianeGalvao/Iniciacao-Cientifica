############################################################################
#
# Ingber and Rosen f2 test problem
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

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    100*(x[1]^2-x[2])^2+(1-x[1])^2;

subject to bounds {i in 1..n}:
    -2.048 <= x[i] <= 2.048;

#printf "Global minima at (1,1) with fx=0\n";
