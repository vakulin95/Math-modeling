set term gif \
    animate \
    optimize \
    delay 10 \
    size 1600, 900 \
    background "white" \
    crop \
    font "Times-Roman,16"
set xrange [7 : 8]
set yrange [7 : 8]
set xzeroaxis
set style data lines
set grid
set xtics auto
set ytics auto
set mxtics
set mytics

set title "Фазовый портрет динамики численности популяций"
set xlabel "X_1(t) - жертвы"
set ylabel "X_2(t) - хищники"

plot_line = "files/data/lines_out.dat"

title1 = "Изменение X_1(0) и X_2(0)"

set output "files/animate_phase_out.gif"

do for [i = 0:299]{
    plot sprintf("files/data/1_%d_out.dat", i) u 2:3 title title1 lc rgb "red",\
    plot_line u 1:2 title "" lc rgb "blue" lt 0, plot_line u 1:3 title "" lc rgb "blue" lt 0
}

unset out
