#!/usr/bin/gnuplot
set terminal epslatex
set output "auditoria.tex"

set xlabel "nº mensagens"
set ylabel "tempo de execução(s)"


set key at 350,760

set grid ytics lc rgb "#bbbbbb" lw 1 lt 0

plot "auditoria.data" \
       every ::1::8   using 1:2 title "Auditoria"     with linespoints lt 1,
    
set output
