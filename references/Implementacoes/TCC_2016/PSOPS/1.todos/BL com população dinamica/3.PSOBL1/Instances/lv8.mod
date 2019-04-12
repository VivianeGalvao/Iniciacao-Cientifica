############################################################################
#
# Levy n.8 problem (very similar with lm1.mod)
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
param n := 3;
param pi := 4*atan(1);

# variables
var x{1..n};
var y{i in 1..n} =1+0.25*(x[i]-1);


# objective function, minimization problem
minimize fx:
    sin(pi*y[1])^2+(sum {i in 1..n-1} ((y[i]-1)^2*(1+10*sin(pi*y[i+1])^2)))+(y[n]-1)^2;

subject to bounds {i in 1..n}:
    -10 <= x[i] <= 10;


#printf "Global minimizer at (1,1,1) with fx=0\n";
