set term gif \
    animate \
    optimize \
    delay 7 \
    size 1600, 900 \
    background "white" \
    crop \
    font "Times-Roman,16"
set xrange [0 : 100]
set yrange[0 : 400]
set xzeroaxis
set style data lines
set grid
set xtics auto
set ytics auto
set mxtics
set mytics

set title "Зависимость численности популяции от времени"
set xlabel "t"
set ylabel "N_1, N_2"

title1 = "N_1(t)"
title2 = "N_2(t)"

set output "files/animate_out.gif"

do for [j = 0:149]{
    plot_file = sprintf("files/data/%d_out.dat", j)
    plot plot_file u 1:2 title title1 lc rgb "red", plot_file u 1:3 title title2 lc rgb "blue"
}

unset out
