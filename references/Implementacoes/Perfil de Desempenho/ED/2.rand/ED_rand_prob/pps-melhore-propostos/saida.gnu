set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida2_gnu.eps'
set key right bottom
#set xrange [1:1.0099034429565307E7]
set xrange [1:10]
set yrange [0:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 1 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 2 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'N4' lw 10 lt 3
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:9]
set yrange [0.5:1.005]
set xtics ('N4' 2, 'N3' 4, 'N2' 6, 'N1' 8)
plot 'out_saida.gnu.dat' usi (2):4 title 'N4' w boxes lt 3, 'out_saida.gnu.dat' usi (4):3 title 'N3' w boxes lt 2, 'out_saida.gnu.dat' usi (6):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (8):1 title 'N1' w boxes lt 0
