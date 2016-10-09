set terminal pdfcairo
set xrange [0 : 1]
set yrange[-5 : 5]
set xzeroaxis
set style data lines
set grid
set xtics auto
set ytics auto
set mxtics
set mytics

set title "Малые поперечные колебания струны с закрепленными концами"
set xlabel "x"
set ylabel "u(x, t)"

plot_cont = "files/cont_out.txt"
plot_discr = "files/discr_out.txt"
title_cont = "Решение непрерывной модели"
title_discr = "Решение дискретной модели"

set output "files/out.pdf"

	plot plot_cont u 1:270 title title_cont lc rgb "red" , plot_discr u 1:270 title title_discr lc rgb "blue"

unset out
