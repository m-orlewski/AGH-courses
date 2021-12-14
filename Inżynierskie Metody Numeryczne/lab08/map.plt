set term jpeg
set out "wykresy/calka.jpg"
plot "wyniki/c_D_0.dat" u 1:2 w l lw 1 t 'C-D=0.0',"wyniki/xsr_D_0.dat" u 1:2 w l lw 1 t 'Xsr-D=0.0', "wyniki/c_D_1.dat" u 1:2 w l lw 1 t 'C-D=1.0',"wyniki/xsr_D_1.dat" u 1:2 w l lw 1 t 'Xsr-D=1.0'

set size square
set view map
set palette defined (0 "white", 1 "blue")

set title "map1_1"
set out "wykresy/map1_1.jpg"
splot "wyniki/Tk1_D_1.dat" u 1:2:3 w pm3d

set title "map2_1"
set out "wykresy/map2_1.jpg"
splot "wyniki/Tk2_D_1.dat" u 1:2:3 w pm3d

set title "map3_1"
set out "wykresy/map3_1.jpg"
splot "wyniki/Tk3_D_1.dat" u 1:2:3 w pm3d

set title "map4_1"
set out "wykresy/map4_1.jpg"
splot "wyniki/Tk4_D_1.dat" u 1:2:3 w pm3d

set title "map5_1"
set out "wykresy/map5_1.jpg"
splot "wyniki/Tk5_D_1.dat" u 1:2:3 w pm3d

set title "Vx"
set out "wykresy/vx_D_0.jpg"
splot "wyniki/vx_D_0.dat" u 1:2:3 w pm3d

set title "Vy"
set out "wykresy/vy_D_0.jpg"
splot "wyniki/vy_D_0.dat" u 1:2:3 w pm3d

set title "Vx"
set out "wykresy/vx_D_1.jpg"
splot "wyniki/vx_D_1.dat" u 1:2:3 w pm3d

set title "Vy"
set out "wykresy/vy_D_1.jpg"
splot "wyniki/vy_D_1.dat" u 1:2:3 w pm3d
