############################################################################
#
# Epistatic Michalewicz problem
# as described in
#   M.M.  Ali,  C.  Khompatraporn  and  Z.B.  Zabinsky,   "A numerical
#   evaluation of several stochastic algorithms on selected continuous
#   global optimization test problems", Journal of Global Optimization
#   (2005) 31:635-672
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 14 September 2005
############################################################################

# parameters
param n := 5;
param m := 10;
param pi := 4*atan(1);
param theta := pi/6;

# variables
var x{1..n};
var y{i in 1..n} = (if i==n then x[i] else (if i mod 2 == 1 then (x[i]*cos(theta)-x[i+1]*sin(theta))
                                                            else x[i]*sin(theta)+x[i+1]*cos(theta)));

# objective function, minimization problem
minimize fx:
    -sum {i in 1..n} (sin(y[i])*(sin(i*y[i]^2/pi))^(2*m));

subject to bounds {i in 1..n}:
    0 <= x[i] <= pi;
    

#printf "Unknown number of local minima\nGlobal minimizer at (2.693, 0.259, 2.074, 1.023, 1.720)\n";
#printf "with fx=-4.687658\n";
