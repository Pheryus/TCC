#!/usr/bin/gnuplot
set terminal epslatex
set output "simbolic.tex"
set xlabel "nº mensagens"
set ylabel "tempo de execução(s)"

set logscale x 2

set key at 400,760

set grid ytics lc rgb "#bbbbbb" lw 1 lt 0

plot "simbolic.data" \
       every ::1::8   using 1:2 title "Execução Simbólica"     with linespoints lt 1,
    
set output
