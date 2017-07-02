############################################################################
#
# Ingber and Rosen f3 test problem
# as described in
#   L. Ingber and B. Rosen, "Genetic algorithms and very fast simulated
#   reannealing: a comparison", Mathematical and Computer Modelling 16(11) 1992, 87-100.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 28 September 2005
############################################################################

# parameters
param n := 5;

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    30.0 + sum {i in 1..n} round(x[i]-0.49999); # round bellow

subject to bounds {i in 1..n}:
    -5.12 <= x[i] <= 5.12;

    
#printf "Global minima at (1,1) with fx=0\n";
