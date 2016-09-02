set logscale x
set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
#set output 'saida.gnu.eps'
set output 'saida3log_gnu.eps'
set key right bottom
#set xrange [1:45938.67905313977]
set xrange [1:20]
#set yrange [0:1.01]
set yrange [0.6:1.01]
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
set xtics ('N7' 2, 'N1' 4, 'N4' 6, 'N6' 8, 'N2' 10, 'N3' 12, 'N8' 14, 'N5' 16, 'N9' 18)
plot 'out_saida.gnu.dat' usi (2):7 title 'N7' w boxes lt 6, 'out_saida.gnu.dat' usi (4):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (6):4 title 'N4' w boxes lt 3, 'out_saida.gnu.dat' usi (8):6 title 'N6' w boxes lt 5, 'out_saida.gnu.dat' usi (10):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (12):3 title 'N3' w boxes lt 2, 'out_saida.gnu.dat' usi (14):8 title 'N8' w boxes lt 7, 'out_saida.gnu.dat' usi (16):5 title 'N5' w boxes lt 4, 'out_saida.gnu.dat' usi (18):9 title 'N9' w boxes lt 8
