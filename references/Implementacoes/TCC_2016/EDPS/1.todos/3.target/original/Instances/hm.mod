############################################################################
#
# Hump problem (different version of cp3.mod)
# as described in
#   A.-R. Hedar and M. Fukushima, "Heuristic pattern search and its
#   hybridization with simulated annealing for nonlinear global optimization",
#   Optimization Methods and Software, vol 19, n3-4, 291-308, 2004.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 01 October 2005
############################################################################

# variables
var x{1..2};

# objective function, minimization problem
minimize fx:
    1.0316285+4*x[1]^2-2.1*x[1]^4+x[1]^6/3+x[1]*x[2]-4*x[2]^2+4*x[2]^4;

subject to bounds {i in 1..2}:
    -5 <= x[i] <= 5;

#printf "Global minimizers at (0.0898, -0.7126), (-0.0898, 0.7126) with fx=0\n";
