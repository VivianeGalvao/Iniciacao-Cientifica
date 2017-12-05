set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida2_gnu.eps'
set key right bottom
set xrange [1:20]
set yrange [0:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N10_saida.gnu.dat' u ($1):($2)  title 'N10' lw 10 lt 1 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 2 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 3 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'N4' lw 10 lt 4 , 'out_N5_saida.gnu.dat' u ($1):($2)  title 'N5' lw 10 lt 5 , 'out_N6_saida.gnu.dat' u ($1):($2)  title 'N6' lw 10 lt 6 , 'out_N7_saida.gnu.dat' u ($1):($2)  title 'N7' lw 10 lt 7 , 'out_N8_saida.gnu.dat' u ($1):($2)  title 'N8' lw 10 lt 8 , 'out_N9_saida.gnu.dat' u ($1):($2)  title 'N9' lw 10 lt 9
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:21]
set yrange [0.5:1.005]
set xtics ('N10' 2, 'N9' 4, 'N8' 6, 'N1' 8, 'N7' 10, 'N6' 12, 'N5' 14, 'N2' 16, 'N4' 18, 'N3' 20)
plot 'out_saida.gnu.dat' usi (2):2 title 'N10' w boxes lt 1, 'out_saida.gnu.dat' usi (4):10 title 'N9' w boxes lt 9, 'out_saida.gnu.dat' usi (6):9 title 'N8' w boxes lt 8, 'out_saida.gnu.dat' usi (8):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (10):8 title 'N7' w boxes lt 7, 'out_saida.gnu.dat' usi (12):7 title 'N6' w boxes lt 6, 'out_saida.gnu.dat' usi (14):6 title 'N5' w boxes lt 5, 'out_saida.gnu.dat' usi (16):3 title 'N2' w boxes lt 2, 'out_saida.gnu.dat' usi (18):5 title 'N4' w boxes lt 4, 'out_saida.gnu.dat' usi (20):4 title 'N3' w boxes lt 3
