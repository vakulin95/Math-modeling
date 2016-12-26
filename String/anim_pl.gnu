set term gif \
    animate \
    optimize \
    delay 1 \
    size 1600, 900 \
    background "white" \
    crop \
    font "Times-Roman,16"
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

set output "files/animate_out.gif"

do for [i = 0:999]{
    plot plot_cont u 1:i title title_cont lc rgb "red" , plot_discr u 1:i title title_discr lc rgb "blue"
}

unset out
