set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida2_gnu.eps'
set key right bottom
#set xrange [1:9.759262082109034]
set xrange [1:2]
set yrange [0:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 1
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:5]
set yrange [0.5:1.005]
set xtics ('N2' 2, 'N1' 4)
plot 'out_saida.gnu.dat' usi (2):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (4):1 title 'N1' w boxes lt 0
