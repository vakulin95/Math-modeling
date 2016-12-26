set terminal pdfcairo font "Times-Roman,10"
set grid
set xtics auto
set ytics auto
set mxtics
set mytics
set style data lines
#set key outside bottom right box

plot_file = "files/data/data_out.dat"
plot_line = "files/data/lines_out.dat"

title1 = "X_1(t)"
title2 = "X_2(t)"
title3 = "X_2(X_1)"

set output "files/pl_out.pdf"
    #set xrange [0 : 100]
    #set yrange[0 : 400]
	set title "Зависимость численности популяции от времени"
	set xlabel "t"
	set ylabel "X_1, X_2"
	plot plot_file u 1:2 title title1 lc rgb "blue", plot_file u 1:3 title title2 lc rgb "red"

    #set xrange [0 : 300]
    #set yrange[0 : 100]
    set title "Фазовый портрет"
	set xlabel "X_1"
	set ylabel "X_2"
	plot plot_file u 2:3 title title3 lc rgb "blue", \
    plot_line u 1:2 title "" lc rgb "red", plot_line u 1:3 title "" lc rgb "green"

unset out
