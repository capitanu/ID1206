# GNUplot script for plotting data in files "optimal.dat" and "random.dat"

   set terminal png
   set output "comparison.png"

   set title "Page replacement"

   set key right center

   set xlabel "frames in memory"
   set ylabel "hit ratio"

   set xrange [0:100]
   set yrange [0:1]

   plot "optimal.dat" u 1:2 w linespoints title "optimal", \
   "random.dat" u 1:2 w linespoints title "random", \
      "lru.dat" u 1:2 w linespoints title "lru", \
         "clock.dat" u 1:2 w linespoints title "clock"

