############################################################################
#
# Storn Tchebychev problem
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
param n := 9;
param d := 72.661;
param m := 60;

# variables
var x{1..n};
var u = sum {i in 1..n} ( (1.2)^(n-i)*x[i]);
var v = sum {i in 1..n} ((-1.2)^(n-i)*x[i]);
var w {j in 0..m} = sum {i in 1..n} (((2*j)/m-1)^(n-i)*x[i]);

var p1 = if u<d then (u-d)^2 else 0;
var p2 = if v<d then (v-d)^2 else 0;
var pl{j in 0..m} = if w[j]>1 then (w[j]-1)^2 else (if w[j]<-1 then (w[j]+1)^2 else 0);
var p3= sum {j in 0..m} pl[j];


# objective function, minimization problem
minimize fx:
    p1+p2+p3;

subject to bounds {i in 1..n}:
    -256 <= x[i] <= 256;


#printf "Global minimizer at (128, 0, -256, 0, 160, 0, -32, 0, 1) with fx=0\nReported solution is not feasible with proposed bounds!!!!!\n";
#printf "Used bounds from [-256,256]^9\n";
