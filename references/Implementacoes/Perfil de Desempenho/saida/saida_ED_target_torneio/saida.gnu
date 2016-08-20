set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida.gnu.eps'
set key right bottom
set logscale x 10
#set xrange [1:7.1846701983368172E18]
set xrange [1:100]
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
set xtics ('N8' 2, 'N9' 4, 'N10' 6, 'N7' 8, 'N6' 10, 'N5' 12, 'N4' 14, 'N3' 16, 'N2' 18, 'N1' 20)
plot 'out_saida.gnu.dat' usi (2):9 title 'N8' w boxes lt 8, 'out_saida.gnu.dat' usi (4):10 title 'N9' w boxes lt 9, 'out_saida.gnu.dat' usi (6):2 title 'N10' w boxes lt 1, 'out_saida.gnu.dat' usi (8):8 title 'N7' w boxes lt 7, 'out_saida.gnu.dat' usi (10):7 title 'N6' w boxes lt 6, 'out_saida.gnu.dat' usi (12):6 title 'N5' w boxes lt 5, 'out_saida.gnu.dat' usi (14):5 title 'N4' w boxes lt 4, 'out_saida.gnu.dat' usi (16):4 title 'N3' w boxes lt 3, 'out_saida.gnu.dat' usi (18):3 title 'N2' w boxes lt 2, 'out_saida.gnu.dat' usi (20):1 title 'N1' w boxes lt 0
