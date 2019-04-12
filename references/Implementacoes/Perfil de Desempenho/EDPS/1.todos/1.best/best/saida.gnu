#set style data lines
#set ylabel '{/Symbol r}({/Symbol t})'
#set xlabel '{/Symbol t}'
#set term postscript eps enhanced color
#set output 'saida.gnu.eps'
#set key right bottom
#set xrange [1:6247.558201294028]
#set yrange [0:1.01]

set size 1,1
#set size 0.3,1
set style data lines
unset key
set key right bottom
set key font ",20"
set logscale x
#set ylabel '{/Symbol r}({/Symbol t})'
set xlabel 'log({/Symbol t})' font ",15"
#set xlabel '{/Symbol t}'
set term postscript eps enhanced color font ",15"
#set output 'saida.gnu.eps'
set output 'saida2.eps'
#set xrange [1:104119.00499999999]
set xrange [1.03:10]
#set xrange [1:1.03]
#set xtics 1.03
#set yrange [0:1.01]
set yrange [0:1.01]
unset ytics

plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'DE/best' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'DE/best+PS' lw 10 lt 1 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'DE/best+PS*' lw 10 lt 2

#set output 'saida.gnu_bar.eps'
#unset key
#set ylabel 'Area'
#set xlabel 'Algorithm'
#set autoscale
#unset logscale x
#set boxwidth 0.8
#set style fill solid border -1
#set xrange [1:7]
#set yrange [0.5:1.005]
#set xtics ('N2' 2, 'N1' 4, 'N3' 6)
#plot 'out_saida.gnu.dat' usi (2):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (4):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (6):3 title 'N3' w boxes lt 2
