set term gif \
    animate \
    optimize \
    delay 7 \
    size 1600, 900 \
    background "white" \
    crop \
    font "Times-Roman,16"
set xrange [0 : 300]
set yrange [0 : 900]
set xzeroaxis
set style data lines
set grid
set xtics auto
set ytics auto
set mxtics
set mytics

set title "Фазовый портрет динамики численности популяций"
set xlabel "N_1(t)"
set ylabel "N_2(t)"

title1 = "Изменение N_1(0)"
title2 = "Изменение N_2(0)"
title3 = "Изменение N_1(0) и N_2(0)"
title4 = ""

set output "files/animate_phase_out.gif"

do for [i = 0:149]{
    plot sprintf("files/data/1_%d_out.dat", i) u 2:3 title title1 lc rgb "red",\
    sprintf("files/data/2_%d_out.dat", i) u 2:3 title title4 lc rgb "red",\
    sprintf("files/data/3_%d_out.dat", i) u 2:3 title title2 lc rgb "blue",\
    sprintf("files/data/4_%d_out.dat", i) u 2:3 title title4 lc rgb "blue",\
    sprintf("files/data/5_%d_out.dat", i) u 2:3 title title3 lc rgb "black",\
    sprintf("files/data/6_%d_out.dat", i) u 2:3 title title4 lc rgb "black",\
    "files/data/line1_out.dat" u 1:2 title title4 lc rgb "yellow",\
    "files/data/line2_out.dat" u 1:2 title title4 lc rgb "yellow"
}

unset out
