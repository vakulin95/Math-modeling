set terminal pdfcairo
set grid
set xtics auto
set ytics auto
set mxtics
set mytics
set style data lines
set key outside bottom right box

plot_ex = "files/output_exact1.dat"
plot_exf = "files/output_exact0.dat"
plot_st = "files/output_stable.dat"
plot_ust = "files/output_unstable1.dat"
plot_ustf = "files/output_unstable0.dat"

title1 = "{/Symbol f}(t)"
title2 = "d{/Symbol f}(t)"
title3 = "d{/Symbol f}({/Symbol f})"

set output "files/MM_ex.pdf"

	set title "Точное решение"
	set xlabel "t"
	set ylabel "{/Symbol f},d{/Symbol f}"
	plot plot_ex u 1:2 title title1 lc rgb "blue", plot_exf u 1:2 title "" lc rgb "blue", plot_ex u 1:3 title title2 lc rgb "red", plot_exf u 1:3 title "" lc rgb "red"
	set xlabel "{/Symbol f}"
	set ylabel "d{/Symbol f}"
	plot plot_ex u 2:3 title title3 lc rgb "blue", plot_exf u 2:3 title "" lc rgb "blue"

unset out

set output "files/MM_st.pdf"

	set title "Случай устойчивого равновесия"
	set xlabel "t"
	set ylabel "{/Symbol f},d{/Symbol f}"
	plot plot_st u 1:2 title title1 lc rgb "blue", plot_st u 1:3 title title2 lc rgb "red"
	set xlabel "{/Symbol f}"
	set ylabel "d{/Symbol f}"
	plot plot_st u 2:3 title title3 lc rgb "blue"

unset out

set output "files/MM_ust.pdf"

	set title "Случай неустойчивого равновесия"
	set xlabel "t"
	set ylabel "{/Symbol f},d{/Symbol f}"
	plot plot_ust u 1:2 title title1 lc rgb "blue", plot_ust u 1:3 title title2 lc rgb "red"
	set xlabel "{/Symbol f}"
	set ylabel "d{/Symbol f}"
	plot plot_ust u 2:3 title title3 lc rgb "blue"

unset out

set xrange [-10:10]
set yrange [-10:10]
set output "files/MM_phase.pdf"

	set title "Фазовый портрет"
	set xlabel "{/Symbol f}"
	set ylabel "d{/Symbol f}"
	plot plot_ex u 2:3 title "exact" lc rgb "red", plot_exf u 2:3 title "" lc rgb "red", plot_st u 2:3 title "stable" lc rgb "blue", plot_ust u 2:3 title "unstable" lc rgb "green", plot_ustf u 2:3 title "" lc rgb "green"

unset out
set xrange [*:*]
set yrange [*:*]
