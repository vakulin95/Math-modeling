set terminal pdfcairo
set grid
set xtics auto
set ytics auto
set mxtics
set mytics
set style data lines
set key outside bottom right box

plot_cont = "files/cont_out.txt"

title = "u(x)"

set output "files/String_cont.pdf"

	set title "Решение непрерывной модели"
	set xlabel "x"
	set ylabel "u"
	plot plot_cont u 1:2 title title lc rgb "red"

unset out

set terminal qt
