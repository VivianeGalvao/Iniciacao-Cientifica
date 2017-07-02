set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida2_gnu.eps'
set key right bottom
#set xrange [1:86708.72303015595]
set xrange [1:10]
set yrange [0.5:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N10_saida.gnu.dat' u ($1):($2)  title 'N10' lw 10 lt 1 lc rgb 'yellow', 'out_N11_saida.gnu.dat' u ($1):($2)  title 'N11' lw 10 lt 2 lc rgb 'orange', 'out_N12_saida.gnu.dat' u ($1):($2)  title 'N12' lw 10 lt 3 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 4 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 5 , 'out_N4_saida.gnu.dat' u ($1):($2)  title 'N4' lw 10 lt 6 , 'out_N5_saida.gnu.dat' u ($1):($2)  title 'N5' lw 10 lt 7 , 'out_N6_saida.gnu.dat' u ($1):($2)  title 'N6' lw 10 lt 8 , 'out_N7_saida.gnu.dat' u ($1):($2)  title 'N7' lw 10 lt 9 , 'out_N8_saida.gnu.dat' u ($1):($2)  title 'N8' lw 10 lt 10 , 'out_N9_saida.gnu.dat' u ($1):($2)  title 'N9' lw 10 lt 11
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
set xtics ('N10' 2, 'N1' 4, 'N11' 6, 'N4' 8, 'N12' 10, 'N7' 12, 'N5' 14, 'N8' 16, 'N2' 18, 'N6' 20, 'N9' 22, 'N3' 24)
plot 'out_saida.gnu.dat' usi (2):2 title 'N10' w boxes lt 1, 'out_saida.gnu.dat' usi (4):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (6):3 title 'N11' w boxes lt 2, 'out_saida.gnu.dat' usi (8):7 title 'N4' w boxes lt 6, 'out_saida.gnu.dat' usi (10):4 title 'N12' w boxes lt 3, 'out_saida.gnu.dat' usi (12):10 title 'N7' w boxes lt 9, 'out_saida.gnu.dat' usi (14):8 title 'N5' w boxes lt 7, 'out_saida.gnu.dat' usi (16):11 title 'N8' w boxes lt 10, 'out_saida.gnu.dat' usi (18):5 title 'N2' w boxes lt 4, 'out_saida.gnu.dat' usi (20):9 title 'N6' w boxes lt 8, 'out_saida.gnu.dat' usi (22):12 title 'N9' w boxes lt 11, 'out_saida.gnu.dat' usi (24):6 title 'N3' w boxes lt 5
