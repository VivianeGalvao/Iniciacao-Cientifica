set logscale x
set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida4_gnu.eps'
set key right bottom
#set xrange [1:199713.59999999998]
set xrange [1:1000]
set yrange [0.6:1.01]
#plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'PSWARM' lw 10 lt 0 lc rgb 'purple', 'out_N2_saida.gnu.dat' u ($1):($2)  title 'PSO' lw 10 lt 1 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'PSO+PS' lw 10 lt 2 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'PSO+PS*' lw 10 lt 3 , 'out_N5_saida.gnu.dat' u ($1):($2)  title 'PSWARM*' lw 10 lt 4 #, 'out_N6_saida.gnu.dat' u ($1):($2)  title 'ED/rand+PS*' lw 10 lt 5 , 'out_N7_saida.gnu.dat' u ($1):($2)  title 'ED/best+PS*' lw 10 lt 6 , 'out_N8_saida.gnu.dat' u ($1):($2)  title 'ED/target-to-best+PS*' lw 10 lt 7
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'PSWARM' lw 10 lt 0 lc rgb 'blue', 'out_N6_saida.gnu.dat' u ($1):($2)  title 'ED/rand+PS*' lw 10 lt 5 , 'out_N7_saida.gnu.dat' u ($1):($2)  title 'ED/best+PS*' lw 10 lt 6 , 'out_N8_saida.gnu.dat' u ($1):($2)  title 'ED/target-to-best+PS*' lw 10 lt 7
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:17]
set yrange [0.5:1.005]
#set xtics ('N4' 2, 'N3' 4, 'N2' 6, 'N5' 8, 'N7' 10, 'N6' 12, 'N8' 14, 'N1' 16)
set xtics ('N4' 2, 'N3' 4, 'N2' 6, 'N5' 8, 'N1' 16)
plot 'out_saida.gnu.dat' usi (2):4 title 'N4' w boxes lt 3, 'out_saida.gnu.dat' usi (4):3 title 'N3' w boxes lt 2, 'out_saida.gnu.dat' usi (6):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (8):5 title 'N5' w boxes lt 4, 'out_saida.gnu.dat' usi (10):7 title 'N7' w boxes lt 6, 'out_saida.gnu.dat' usi (12):6 title 'N6' w boxes lt 5, 'out_saida.gnu.dat' usi (14):8 title 'N8' w boxes lt 7, 'out_saida.gnu.dat' usi (16):1 title 'N1' w boxes lt 0
