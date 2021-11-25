set term jpeg size 800,800
set size square
set out "wykresy/V1.jpg"
set view map
splot "wyniki/V_k_1.dat" u 1:2:3 w pm3d

set out "wykresy/V2.jpg"
splot "wyniki/V_k_2.dat" u 1:2:3 w pm3d

set out "wykresy/V4.jpg"
splot "wyniki/V_k_4.dat" u 1:2:3 w pm3d

set out "wykresy/V8.jpg"
splot "wyniki/V_k_8.dat" u 1:2:3 w pm3d

set out "wykresy/V16.jpg"
splot "wyniki/V_k_16.dat" u 1:2:3 w pm3d
