############################################################################
#
# Modified Griewank problem
# as described in
#   M. Locatelli, "A note on the Griewank test function", Journal of Global
#   Optimization 25: 169-174, 2003.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 28 September 2005
############################################################################

# parameters
param n := 20;
param pi := 4*atan(1);
param H {i in 1..n, j in 1..n} := (if i <= n/2 then 1 else (if j<=n/2 then 1/(sqrt(2)) else -1/(sqrt(2))));


# variables
var x{1..n};

# objective function, minimization problem
minimize fx:
    1/4000*(sum {i in 1..n} (x[i]^2))-sum {i in 1..n} (log(2+cos(sum {j in 1..n} (H[i,j]*x[j]))))+n*log(3);

subject to bounds {i in 1..n}:
    -10 <= x[i] <= 10;

    
#printf "Global minima at the origin with fx=0\n";
