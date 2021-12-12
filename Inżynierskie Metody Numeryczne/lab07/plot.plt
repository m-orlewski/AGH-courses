set term jpeg
set size square
set view map
set contour base
set palette defined (-1 "blue", 0 "white", 1 "red")

set title "v Q=-1000"
set out "wykresy/v_1.jpg"
splot "wyniki/v_1.dat" u 1:2:3 w pm3d

set title "u Q=-1000"
set out "wykresy/u_1.jpg"
splot "wyniki/u_1.dat" u 1:2:3 w pm3d


set title "v Q=-4000"
set out "wykresy/v_2.jpg"
splot "wyniki/v_2.dat" u 1:2:3 w pm3d


set title "u Q=-4000"
set out "wykresy/u_2.jpg"
splot "wyniki/u_2.dat" u 1:2:3 w pm3d


set title "v Q=4000"
set out "wykresy/v_3.jpg"
splot "wyniki/v_3.dat" u 1:2:3 w pm3d


set title "u Q=4000"
set out "wykresy/u_3.jpg"
splot "wyniki/u_3.dat" u 1:2:3 w pm3d

unset surface
set contours
set cntrparam levels 200
unset key


set title "psi Q=-1000"
set out "wykresy/psi_1.jpg"
splot "wyniki/psi_1.dat" u 1:2:3 w l

set title "dzeta Q=-1000"
set out "wykresy/dzeta_1.jpg"
splot "wyniki/dzeta_1.dat" u 1:2:3 w l


set title "psi Q=-4000"
set out "wykresy/psi_2.jpg"
splot "wyniki/psi_2.dat" u 1:2:3 w l


set title "dzeta Q=-4000"
set out "wykresy/dzeta_2.jpg"
splot "wyniki/dzeta_2.dat" u 1:2:3 w l

set title "psi Q=4000"
set out "wykresy/psi_3.jpg"
splot "wyniki/psi_3.dat" u 1:2:3 w l


set title "dzeta Q=4000"
set out "wykresy/dzeta_3.jpg"
splot "wyniki/dzeta_3.dat" u 1:2:3 w l