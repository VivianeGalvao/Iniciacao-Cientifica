############################################################################
#
# Sinusoidal problem
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
param n := 10;
param A := 2.5;
param B := 5;
param z := 30;

# variables
var x{1..n};


# objective function, minimization problem
minimize fx:
    -(A*prod {i in 1..n} (sin((x[i]-z)*pi/180))+prod {i in 1..n} (sin(B*(x[i]-z)*pi/180)));

subject to bounds {i in 1..n}:
    0 <= x[i] <= 180;


#printf "Global minimizer at (%.4f, ..., %.4f) with fx=%.4f\n", 90+z, 90+z, -(A+1);
