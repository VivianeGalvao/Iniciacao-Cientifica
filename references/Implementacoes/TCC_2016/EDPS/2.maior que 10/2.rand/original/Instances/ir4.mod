############################################################################
#
# Ingber and Rosen f4 test problem
# as described in
#   L. Ingber and B. Rosen, "Genetic algorithms and very fast simulated
#   reannealing: a comparison", Mathematical and Computer Modelling 16(11) 1992, 87-100.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 28 September 2005
############################################################################

# parameters
param n := 30;

# variables
var x{1..n};

#option randseed '';

# objective function, minimization problem
minimize fx:
    sum {i in 1..n} (x[i]^4)+Uniform01();

subject to bounds {i in 1..n}:
    -1.28 <= x[i] <= 1.28;

    
#printf "Global minima at origin with fx=0 (stochastic problem)\n";
