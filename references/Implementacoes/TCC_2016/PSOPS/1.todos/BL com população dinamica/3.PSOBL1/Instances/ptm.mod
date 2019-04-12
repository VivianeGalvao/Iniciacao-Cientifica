############################################################################
#
# Price's Transistor Modelling problem
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
param pi := 4*atan(1);
param g {1..5,1..4};

# variables
var x{1..9};
var alpha{k in 1..4} = (1-x[1]*x[2])*x[3]*(exp(x[5]*(g[1,k]-g[3,k]*x[7]*10^-3-g[5,k]*x[8]*10^-3))-1)-g[5,k]+g[4,k]*x[2];
var beta{k in 1..4} = (1-x[1]*x[2])*x[4]*(exp(x[6]*(g[1,k]-g[2,k]-g[3,k]*x[7]*10^-3+g[4,k]*x[9]*10^-3))-1)-g[5,k]*x[1]+g[4,k];
var gamma = x[1]*x[3]-x[2]*x[4];


# objective function, minimization problem
minimize fx:
    gamma^2+sum {k in 1..4} (alpha[k]^2+beta[k]^2);

subject to bounds {i in 1..9}:
    -10 <= x[i] <= 10;


data;

param g: 1 2 3 4:=
1   0.485       0.752       0.869       0.982
2   0.369       1.254       0.703       1.455
3   5.2095      10.0677     22.9274     20.2153
4   23.3037     101.779     111.461     191.267
5   28.5132     111.8467    134.3884    211.4823;



#printf "Global minimizer near (0.9,0.45,1,2,8,8,5,1,2) with fx=0\n";
