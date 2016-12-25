set term pngcairo enhanced size 2048,1536 font "CMU Serif, 12"

set out "files/pl_out.png"

set title "Percollation theory model" font "CMU Serif, 20"

unset key

set size square

set xrange [-1:]
set yrange [-1:]

set grid
set palette model RGB
set palette defined

plot "files/result_out.dat" matrix with image
