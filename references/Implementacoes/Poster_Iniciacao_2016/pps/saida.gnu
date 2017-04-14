set logscale x
set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida.gnu.eps'
set key right bottom
set xrange [1:199713.59999999998]
set yrange [0:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N10_saida.gnu.dat' u ($1):($2)  title 'N10' lw 10 lt 1 lc rgb 'purple', 'out_N11_saida.gnu.dat' u ($1):($2)  title 'N11' lw 10 lt 2 lc rgb 'gold', 'out_N12_saida.gnu.dat' u ($1):($2)  title 'N12' lw 10 lt 3 lc rgb 'red', 'out_N13_saida.gnu.dat' u ($1):($2)  title 'N13' lw 10 lt 4 lc rgb 'brown', 'out_N14_saida.gnu.dat' u ($1):($2)  title 'N14' lw 10 lt 5 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 6 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 7 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'N4' lw 10 lt 8 , 'out_N5_saida.gnu.dat' u ($1):($2)  title 'N5' lw 10 lt 9 , 'out_N6_saida.gnu.dat' u ($1):($2)  title 'N6' lw 10 lt 10 , 'out_N7_saida.gnu.dat' u ($1):($2)  title 'N7' lw 10 lt 11 , 'out_N8_saida.gnu.dat' u ($1):($2)  title 'N8' lw 10 lt 12 , 'out_N9_saida.gnu.dat' u ($1):($2)  title 'N9' lw 10 lt 13
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:29]
set yrange [0.5:1.005]
set xtics ('N4' 2, 'N3' 4, 'N10' 6, 'N7' 8, 'N2' 10, 'N11' 12, 'N8' 14, 'N9' 16, 'N6' 18, 'N5' 20, 'N13' 22, 'N12' 24, 'N14' 26, 'N1' 28)
plot 'out_saida.gnu.dat' usi (2):9 title 'N4' w boxes lt 8, 'out_saida.gnu.dat' usi (4):8 title 'N3' w boxes lt 7, 'out_saida.gnu.dat' usi (6):2 title 'N10' w boxes lt 1, 'out_saida.gnu.dat' usi (8):12 title 'N7' w boxes lt 11, 'out_saida.gnu.dat' usi (10):7 title 'N2' w boxes lt 6, 'out_saida.gnu.dat' usi (12):3 title 'N11' w boxes lt 2, 'out_saida.gnu.dat' usi (14):13 title 'N8' w boxes lt 12, 'out_saida.gnu.dat' usi (16):14 title 'N9' w boxes lt 13, 'out_saida.gnu.dat' usi (18):11 title 'N6' w boxes lt 10, 'out_saida.gnu.dat' usi (20):10 title 'N5' w boxes lt 9, 'out_saida.gnu.dat' usi (22):5 title 'N13' w boxes lt 4, 'out_saida.gnu.dat' usi (24):4 title 'N12' w boxes lt 3, 'out_saida.gnu.dat' usi (26):6 title 'N14' w boxes lt 5, 'out_saida.gnu.dat' usi (28):1 title 'N1' w boxes lt 0
