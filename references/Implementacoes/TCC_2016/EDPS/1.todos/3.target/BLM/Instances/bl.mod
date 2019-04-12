############################################################################
#
# Becher and Lago problem
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

# variables
var x{1..2};

# objective function, minimization problem
minimize fx:
    (abs(x[1])-5)^2+(abs(x[2])-5)^2;

subject to bounds {i in 1..2}:
    -10 <= x[i] <= 10;


#printf "Four minima located at (+-5,+-5) with fx=0\n";
