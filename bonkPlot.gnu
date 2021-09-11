set key off
set xlabel "Position"
set ylabel "Time"
plot for [col=2:14] 'bonks.dat' using col:1 with lines, 'bonks.dat' u 7:1 w l lw 5