set terminal png
set output "read.png"

unset key

set xrange [-30:500]
set xtics 64
set boxwidth 10
plot 'foo.dat' u 1:3:2:6:5 with candlesticks
