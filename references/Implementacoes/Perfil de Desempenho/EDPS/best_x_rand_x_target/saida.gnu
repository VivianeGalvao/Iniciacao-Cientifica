set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida.gnu.eps'
set key right bottom
set xrange [1:3.4189394478947897E9]
set yrange [0:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 1 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 2 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'N4' lw 10 lt 3 , 'out_N5_saida.gnu.dat' u ($1):($2)  title 'N5' lw 10 lt 4 , 'out_N6_saida.gnu.dat' u ($1):($2)  title 'N6' lw 10 lt 5
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:13]
set yrange [0.5:1.005]
set xtics ('N1' 2, 'N4' 4, 'N6' 6, 'N5' 8, 'N2' 10, 'N3' 12)
plot 'out_saida.gnu.dat' usi (2):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (4):4 title 'N4' w boxes lt 3, 'out_saida.gnu.dat' usi (6):6 title 'N6' w boxes lt 5, 'out_saida.gnu.dat' usi (8):5 title 'N5' w boxes lt 4, 'out_saida.gnu.dat' usi (10):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (12):3 title 'N3' w boxes lt 2
