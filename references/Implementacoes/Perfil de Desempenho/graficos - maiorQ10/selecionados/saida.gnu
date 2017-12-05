set size 1,1
#set size 0.3,1
set style data lines
#unset key
set key right bottom
set key font ",20"
set logscale x
#set ylabel '{/Symbol r}({/Symbol t})'
set xlabel 'log({/Symbol t})' font ",15"
#set xlabel '{/Symbol t}'
set term postscript eps enhanced color font ",15"
#set output 'saida.gnu.eps'
set output 'saida2.eps'
#set xrange [1:1054.3486182627585]
set xrange [1.03:100]
#set xrange [1:1.03]
#set xtics 1.03
#set yrange [0:1.01]
set yrange [0:1.01]
unset ytics
plot   'out_N10_saida.gnu.dat' u ($1):($2)  title 'PSO' lw 5 lt 3, 'out_N12_saida.gnu.dat' u ($1):($2)  title 'PSO+PS*' lw 5 lt 5 , 'out_N13_saida.gnu.dat' u ($1):($2)  title 'PSWARM' lw 5 lt 6 , 'out_N14_saida.gnu.dat' u ($1):($2)  title 'PSWARM*' lw 5 lt 7 , 'out_N6_saida.gnu.dat' u ($1):($2)  title 'DE2+PS*' lw 5 lt 0,  'out_N8_saida.gnu.dat' u ($1):($2)  title 'DE3+PS' lw 5 lt 1 , 'out_N9_saida.gnu.dat' u ($1):($2)  title 'DE3+PS*' lw 5 lt 2





#set xtics ('N1' 2, 'N2' 4, 'N4' 6, 'N3' 8, 'N11' 10, 'N5' 12, 'N7' 14, jjjj'N10' 16, 'N6' 18, 'N9' 20, 'N8' 22, 'N12' 24, 'N13' 26, 'N14' 28)
#plot 'out_saida.gnu.dat' usi (2):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (4):7 title 'N2' w boxes lt 6, 'out_saida.gnu.dat' usi (6):9 title 'N4' w boxes lt 8, #'out_saida.gnu.dat' usi (8):8 title 'N3' w boxes lt 7, 'out_saida.gnu.dat' usi (10):3 title 'N11' w boxes lt 2, 'out_saida.gnu.dat' usi (12):10 title 'N5' w boxes lt 9, #'out_saida.gnu.dat' usi (14):12 title 'N7' w boxes lt 11, 'out_saida.gnu.dat' usi (16):2 title 'N10' w boxes lt 1, 'out_saida.gnu.dat' usi (18):11 title 'N6' w boxes lt #10, 'out_saida.gnu.dat' usi (20):14 title 'N9' w boxes lt 13, 'out_saida.gnu.dat' usi (22):13 title 'N8' w boxes lt 12, 'out_saida.gnu.dat' usi (24):4 title 'N12' w boxes #lt 3, 'out_saida.gnu.dat' usi (26):5 title 'N13' w boxes lt 4, 'out_saida.gnu.dat' usi (28):6 title 'N14' w boxes lt 5
