set terminal png size 900, 900

set xtics auto
set ytics auto
set ztics auto

set mxtics
set mytics
set mztics

set grid
set style line 1 lc rgb 'red' pt 7 ps 0.2

plot_file = "files/out.dat"

set output "files/pl_out.png"

    set title "Lorenz attractor"
	set xlabel "X"
	set ylabel "Y"
    set view 80, 30

    splot plot_file u 1:2:3 ls 1 title "" #with lines

unset out
