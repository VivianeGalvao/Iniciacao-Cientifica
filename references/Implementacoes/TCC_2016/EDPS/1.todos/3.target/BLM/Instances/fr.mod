############################################################################
#
# Freudenstein-Roth problem
# as described in
#   K.E. Parsopoulos, V.P. Plagianakos, G.D. Magoulas and V.N. Vrahatis,
#   "Stretching technique for obtaining global minimizers through particle
#    swarm optimization", Proc. of the Particle Swarm Optimization Workshop,
#    Indianapolis (IN), USA, pp. 22-29, 2001
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 29 September 2005
############################################################################

# parameters
param n := 2;


# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    (-13+x[1]+((5-x[2])*x[2]-2)*x[2])^2+(-29+x[1]+((x[2]+1)*x[2]-14)*x[2])^2;

subject to bounds {i in 1..n}:
    -5 <= x[i] <= 5;


#printf "Global minimizer at (5,4) with fx=0\n";
