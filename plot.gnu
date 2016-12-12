set terminal png size 900, 900
set xtics auto
set ytics auto
set mxtics
set mytics
set style line 1 lc rgb 'red' pt 7 ps 0.3

plot_file = "output.dat"

set output "pl_out.png"

    set title ""
	set xlabel "r"
	set ylabel "X(r)"
    plot plot_file u 1:2 ls 1 title ""

unset out
