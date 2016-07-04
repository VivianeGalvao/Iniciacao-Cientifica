set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida.gnu.eps'
set key right bottom
#set xrange [1:4.716124834630453E28]
set xrange[1:3000]
set yrange [0:1.01]
plot 'out_N_1_saida.gnu.dat' u ($1):($2)  title 'N_1' lw 10 lt 0 , 'out_N_10_saida.gnu.dat' u ($1):($2)  title 'N_10' lw 10 lt 1 , 'out_N_2_saida.gnu.dat' u ($1):($2)  title 'N_2' lw 10 lt 2 , 'out_N_3_saida.gnu.dat' u ($1):($2)  title 'N_3' lw 10 lt 3 , 'out_N_4_saida.gnu.dat' u ($1):($2)  title 'N_4' lw 10 lt 4 , 'out_N_5_saida.gnu.dat' u ($1):($2)  title 'N_5' lw 10 lt 5 , 'out_N_6_saida.gnu.dat' u ($1):($2)  title 'N_6' lw 10 lt 6 , 'out_N_7_saida.gnu.dat' u ($1):($2)  title 'N_7' lw 10 lt 7 , 'out_N_8_saida.gnu.dat' u ($1):($2)  title 'N_8' lw 10 lt 8 , 'out_N_9_saida.gnu.dat' u ($1):($2)  title 'N_9' lw 10 lt 9
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
set xtics ('N_1' 2, 'N_10' 4, 'N_9' 6, 'N_8' 8, 'N_7' 10, 'N_6' 12, 'N_5' 14, 'N_4' 16, 'N_3' 18, 'N_2' 20)
plot 'out_saida.gnu.dat' usi (2):1 title 'N_1' w boxes lt 0, 'out_saida.gnu.dat' usi (4):2 title 'N_10' w boxes lt 1, 'out_saida.gnu.dat' usi (6):10 title 'N_9' w boxes lt 9, 'out_saida.gnu.dat' usi (8):9 title 'N_8' w boxes lt 8, 'out_saida.gnu.dat' usi (10):8 title 'N_7' w boxes lt 7, 'out_saida.gnu.dat' usi (12):7 title 'N_6' w boxes lt 6, 'out_saida.gnu.dat' usi (14):6 title 'N_5' w boxes lt 5, 'out_saida.gnu.dat' usi (16):5 title 'N_4' w boxes lt 4, 'out_saida.gnu.dat' usi (18):4 title 'N_3' w boxes lt 3, 'out_saida.gnu.dat' usi (20):3 title 'N_2' w boxes lt 2
