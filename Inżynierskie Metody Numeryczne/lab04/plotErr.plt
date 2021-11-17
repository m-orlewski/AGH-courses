set term jpeg size 800,800
set size square
set out "Error_0_6.png"
set view map
set dgrid 99,149
splot "wyniki/global_0_6_err.dat" u 1:2:4 w pm3d