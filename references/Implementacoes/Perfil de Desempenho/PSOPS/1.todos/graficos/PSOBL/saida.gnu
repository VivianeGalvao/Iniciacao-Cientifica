set logscale x
set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida2.eps'
set key right bottom
#set xrange [1:50931.86076592525]
set xrange [1:10]
set yrange [0:1.01]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'PSO' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'PSO+BP' lw 10 lt 1 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'PSO+BPM' lw 10 lt 2
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Área'
set xlabel 'Algoritmo'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:7]
set yrange [0.5:1.005]
set xtics ('PSO' 2, 'PSO+BPM' 4, 'PSO+BP' 6)
plot 'out_saida.gnu.dat' usi (2):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (4):3 title 'N3' w boxes lt 2, 'out_saida.gnu.dat' usi (6):2 title 'N2' w boxes lt 1
