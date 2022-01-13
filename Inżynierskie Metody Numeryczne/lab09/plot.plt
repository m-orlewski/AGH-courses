set term jpeg
set size square
set view map


set out "wykresy/T_it_100.jpg"
set title "T (it=100)"
splot "wyniki/T_it_100.dat" u 1:2:3 w pm3d

set out "wykresy/T_it_200.jpg"
set title "T (it=200)"
splot "wyniki/T_it_200.dat" u 1:2:3 w pm3d

set out "wykresy/T_it_500.jpg"
set title "T (it=500)"
splot "wyniki/T_it_500.dat" u 1:2:3 w pm3d

set out "wykresy/T_it_1000.jpg"
set title "T (it=1000)"
splot "wyniki/T_it_1000.dat" u 1:2:3 w pm3d

set out "wykresy/T_it_2000.jpg"
set title "T (it=2000)"
splot "wyniki/T_it_2000.dat" u 1:2:3 w pm3d