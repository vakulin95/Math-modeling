set term gif \
    animate \
    optimize \
    delay 10 \
    size 900, 700 \
    background "white" \
    crop \
    font "Times-Roman,10"
set xrange [0 : 3]
set yrange[-5 : 5]
set xzeroaxis
set style data lines
set grid
set xtics auto
set ytics auto
set mxtics
set mytics
set title "Решение непрерывной модели"
set xlabel "x"
set ylabel "u"

title = "Амплитуда u(x, t)"

set output "animate_cont.gif"

do for [i = 0:299]{
    plot_cont = sprintf("files/data/cont_out%d.txt", i)
    plot plot_cont u 1:2 title title lc rgb "red"
}

unset out
