set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida2_gnu.eps'
set key right bottom
#set xrange [1:1927.1138976118368]
set xrange [1:2]
set yrange [0.55:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 1 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 2 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'N4' lw 10 lt 3 , 'out_N5_saida.gnu.dat' u ($1):($2)  title 'N5' lw 10 lt 4 , 'out_N6_saida.gnu.dat' u ($1):($2)  title 'N6' lw 10 lt 5 , 'out_N7_saida.gnu.dat' u ($1):($2)  title 'N7' lw 10 lt 6 , 'out_N8_saida.gnu.dat' u ($1):($2)  title 'N8' lw 10 lt 7 , 'out_N9_saida.gnu.dat' u ($1):($2)  title 'N9' lw 10 lt 8
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:19]
set yrange [0.5:1.005]
set xtics ('N9' 2, 'N2' 4, 'N6' 6, 'N3' 8, 'N8' 10, 'N1' 12, 'N5' 14, 'N7' 16, 'N4' 18)
plot 'out_saida.gnu.dat' usi (2):9 title 'N9' w boxes lt 8, 'out_saida.gnu.dat' usi (4):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (6):6 title 'N6' w boxes lt 5, 'out_saida.gnu.dat' usi (8):3 title 'N3' w boxes lt 2, 'out_saida.gnu.dat' usi (10):8 title 'N8' w boxes lt 7, 'out_saida.gnu.dat' usi (12):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (14):5 title 'N5' w boxes lt 4, 'out_saida.gnu.dat' usi (16):7 title 'N7' w boxes lt 6, 'out_saida.gnu.dat' usi (18):4 title 'N4' w boxes lt 3
