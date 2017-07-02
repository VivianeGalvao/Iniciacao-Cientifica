############################################################################
#
# Helical Valley problem
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

# variables
var x{1..3};
var theta = if x[1]==0 then 0 else (if x[1]>0 then atan(x[2]/x[1])/(2*pi) else atan(x[2]/x[1])/(2*pi)+0.5);

# objective function, minimization problem
minimize fx:
    100*((x[2]-10*theta)^2+(sqrt(x[1]^2+x[2]^2)-1)^2)+x[3]^2;

subject to bounds {i in 1..3}:
    -10 <= x[i] <= 10;

#printf "Global minimizer at (1,0,0) with fx=0\n";
