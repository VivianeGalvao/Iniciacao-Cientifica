set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida4_gnu.eps'
set key right bottom
#set xrange [1:517541.73096245056]
set xrange [1:1.00002]
set yrange [0.3:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N10_saida.gnu.dat' u ($1):($2)  title 'N10' lw 10 lt 1 lc rgb 'blue', 'out_N11_saida.gnu.dat' u ($1):($2)  title 'N11' lw 10 lt 2 lc rgb 'pink', 'out_N12_saida.gnu.dat' u ($1):($2)  title 'N12' lw 10 lt 3 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 4 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 5 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'N4' lw 10 lt 6 , 'out_N5_saida.gnu.dat' u ($1):($2)  title 'N5' lw 10 lt 7 , 'out_N6_saida.gnu.dat' u ($1):($2)  title 'N6' lw 10 lt 8 , 'out_N7_saida.gnu.dat' u ($1):($2)  title 'N7' lw 10 lt 9 , 'out_N8_saida.gnu.dat' u ($1):($2)  title 'N8' lw 10 lt 10 , 'out_N9_saida.gnu.dat' u ($1):($2)  title 'N9' lw 10 lt 11
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:25]
set yrange [0.5:1.005]
set xtics ('N2' 2, 'N1' 4, 'N3' 6, 'N12' 8, 'N6' 10, 'N4' 12, 'N11' 14, 'N7' 16, 'N10' 18, 'N5' 20, 'N8' 22, 'N9' 24)
plot 'out_saida.gnu.dat' usi (2):5 title 'N2' w boxes lt 4, 'out_saida.gnu.dat' usi (4):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (6):6 title 'N3' w boxes lt 5, 'out_saida.gnu.dat' usi (8):4 title 'N12' w boxes lt 3, 'out_saida.gnu.dat' usi (10):9 title 'N6' w boxes lt 8, 'out_saida.gnu.dat' usi (12):7 title 'N4' w boxes lt 6, 'out_saida.gnu.dat' usi (14):3 title 'N11' w boxes lt 2, 'out_saida.gnu.dat' usi (16):10 title 'N7' w boxes lt 9, 'out_saida.gnu.dat' usi (18):2 title 'N10' w boxes lt 1, 'out_saida.gnu.dat' usi (20):8 title 'N5' w boxes lt 7, 'out_saida.gnu.dat' usi (22):11 title 'N8' w boxes lt 10, 'out_saida.gnu.dat' usi (24):12 title 'N9' w boxes lt 11
