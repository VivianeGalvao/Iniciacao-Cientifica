############################################################################
#
# Ingber and Rosen f0 test problem (Corana function)
# as described in
#   L. Ingber and B. Rosen, "Genetic algorithms and very fast simulated
#   reannealing: a comparison", Mathematical and Computer Modelling 16(11) 1992, 87-100.
#
# Coded for AMPL by: aivaz@dps.uminho.pt
# Minho University, Portugal
# 28 September 2005
############################################################################

# parameters
param n := 4;
param c := 0.15;
param s {i in 1..n} := 0.2;
param t {i in 1..n} := 0.05;
param d {1..n};


# variables
var x{1..n};
var sgnx {i in 1..n} = if x[i] < 0 then -1 else if x[i]>0 then 1 else 0;
var z {i in 1..n} = round(abs(x[i]/s[i])+0.49999)*sgnx[i]*s[i];
var sgnz {i in 1..n} = if z[i] < 0 then -1 else if z[i]>0 then 1 else 0;


# objective function, minimization problem
minimize fx:
    sum {i in 1..n} (if abs(x[i]-z[i])<t[i] then (t[i]*sgnz[i]+z[i])^2*c*d[i] else d[i]*x[i]^2);

subject to bounds {i in 1..n}:
    -1000 <= x[i] <= 1000;

data;

param d :=
1   1.0
2   1000.0
3   10.0
4   100.0;
    
#printf "Global minima at the origin with fx=0\n";
