set title "duration of FMM"
set logscale
set xlabel "N"
set ylabel "duration (sec)"
plot "result.dat" using 1:2 with lines title "Square"
replot "result.dat" using 1:3 with lines title "Sqrt"
replot "result.dat" using 1:4 with lines title "Log"
replot "result.dat" using 1:5 with lines title "Linear"
set terminal png
set out "duration.png"
replot