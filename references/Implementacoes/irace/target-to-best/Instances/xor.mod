############################################################################
#
# XOR problem
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
param n := 9;

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    (1+exp(-x[7]/(1+exp(-x[1]-x[2]-x[3]))-x[8]/(1+exp(-x[3]-x[4]-x[6]))-x[9]))^-2
    +(1+exp(-x[7]/(1+exp(-x[5]))-x[8]/(1+exp(-x[6]))-x[9]))^-2
    +(1-(1+exp(-x[7]/(1+exp(-x[1]-x[5]))-x[8]/(1+exp(-x[3]-x[6]))-x[9]))^-1)^2
    +(1-(1+exp(-x[7]/(1+exp(-x[2]-x[5]))-x[8]/(1+exp(-x[4]-x[6]))-x[9]))^-1)^2;

subject to bounds {i in 1..n}:
    -1 <= x[i] <= 1;



